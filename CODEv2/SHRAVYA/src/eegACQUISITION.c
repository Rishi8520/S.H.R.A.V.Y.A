/* eeg_acquisition.c - EEG signal acquisition from hardware */
#include "hal_data.h"
#include "eeg_types.h"
#include "shravya_config.h"

/* Include μT-Kernel 3.0 headers */
#include "mtk3_bsp2/include/tk/tkernel.h"

/* Global Variables */
static eeg_circular_buffer_t eeg_buffer;
static volatile bool acquisition_running = false;

/* External semaphore from mtk3_integration.c */
extern ID eeg_data_semaphore;
extern ID preprocessing_semaphore;

/* ADS1263 SPI Configuration */
#define ADS1263_CMD_RESET    0x06
#define ADS1263_CMD_START    0x08
#define ADS1263_CMD_STOP     0x0A
#define ADS1263_CMD_RDATA    0x12

/* Function prototypes */
static void ads1263_reset(void);
static void ads1263_configure_channels(void);
static void ads1263_set_sampling_rate(uint16_t sample_rate);
static fsp_err_t eeg_read_sample(eeg_raw_sample_t *sample);

/* Initialize EEG Acquisition Hardware */
fsp_err_t eeg_acquisition_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Configure ADS1263 registers */
    ads1263_reset();
    ads1263_configure_channels();
    ads1263_set_sampling_rate(EEG_SAMPLE_RATE_HZ);

    /* Initialize circular buffer */
    eeg_buffer.write_index = 0;
    eeg_buffer.read_index = 0;
    eeg_buffer.buffer_full = false;

    return FSP_SUCCESS;
}

/* ADS1263 Hardware Abstraction Functions */
static void ads1263_reset(void)
{
    uint8_t cmd = ADS1263_CMD_RESET;
    R_SPI_Write(&g_spi0_ctrl, &cmd, 1, SPI_BIT_WIDTH_8_BITS);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS); // 1ms delay
}

static void ads1263_configure_channels(void)
{
    // Configure differential input channels for left/right electrodes
    uint8_t config_data[] = {
        0x40, // INPMUX register - AIN0/AIN1 differential
        0x50, // PGA register - Gain = 32, PGA enabled
        0x15, // DATARATE register - 500 SPS
        0x00  // REF register - Internal reference
    };

    R_SPI_Write(&g_spi0_ctrl, config_data, sizeof(config_data), SPI_BIT_WIDTH_8_BITS);
}

static void ads1263_set_sampling_rate(uint16_t sample_rate)
{
    // Implementation for setting ADS1263 sampling rate
    (void)sample_rate; // Suppress unused parameter warning for now
}

static fsp_err_t eeg_read_sample(eeg_raw_sample_t *sample)
{
    uint8_t read_cmd = ADS1263_CMD_RDATA;
    uint8_t adc_data[6]; // 24-bit * 2 channels

    // Send read command
    R_SPI_Write(&g_spi0_ctrl, &read_cmd, 1, SPI_BIT_WIDTH_8_BITS);

    // Read ADC data
    R_SPI_Read(&g_spi0_ctrl, adc_data, sizeof(adc_data), SPI_BIT_WIDTH_8_BITS);

    // Convert to 32-bit signed values
    sample->left_channel = (int32_t)((adc_data[0] << 16) | (adc_data[1] << 8) | adc_data[2]);
    sample->right_channel = (int32_t)((adc_data[3] << 16) | (adc_data[4] << 8) | adc_data[5]);

    // Sign extend 24-bit to 32-bit
    if (sample->left_channel & 0x800000) sample->left_channel |= 0xFF000000;
    if (sample->right_channel & 0x800000) sample->right_channel |= 0xFF000000;

    // Add timestamp
    sample->timestamp_us = R_FSP_SystemClockHzGet() / 1000000; // Rough timestamp

    return FSP_SUCCESS;
}

/* μT-Kernel Task: EEG Acquisition */
void task_eeg_acquisition_entry(INT stacd, void *exinf)
{
    (void)stacd;
    (void)exinf;

    eeg_raw_sample_t sample;
    ER ercd;

    /* Initialize hardware */
    eeg_acquisition_init();

    /* Start continuous acquisition */
    acquisition_running = true;

    while (acquisition_running)
    {
        /* Wait for DRDY signal from ADS1263 */
        ercd = tk_wai_sem(eeg_data_semaphore, TMO_FEVR);
        if (ercd != E_OK) continue;

        /* Read EEG sample from ADS1263 */
        if (eeg_read_sample(&sample) == FSP_SUCCESS)
        {
            /* Store in circular buffer */
            eeg_buffer.samples[eeg_buffer.write_index] = sample;
            eeg_buffer.write_index = (eeg_buffer.write_index + 1) % EEG_BUFFER_SIZE_SAMPLES;

            if (eeg_buffer.write_index == eeg_buffer.read_index)
            {
                eeg_buffer.buffer_full = true;
                eeg_buffer.read_index = (eeg_buffer.read_index + 1) % EEG_BUFFER_SIZE_SAMPLES;
            }
        }

        /* Signal preprocessing task */
        tk_sig_sem(preprocessing_semaphore, 1);
    }
}

/* Timer Callback for 500Hz sampling */
void timer_eeg_callback(timer_callback_args_t *p_args)
{
    (void)p_args;

    /* Signal EEG acquisition task */
    tk_isig_sem(eeg_data_semaphore, 1);
}
