/* generated HAL source file - do not edit */
#include "hal_data.h"
ether_phy_instance_ctrl_t g_ether_phy0_ctrl;

const ether_phy_extended_cfg_t g_ether_phy0_extended_cfg =
{ .p_target_init = NULL, .p_target_link_partner_ability_get = NULL

};

const ether_phy_cfg_t g_ether_phy0_cfg =
{

.channel = 0,
  .phy_lsi_address = 0, .phy_reset_wait_time = 0x00020000, .mii_bit_access_wait_time = 8, .phy_lsi_type =
          ETHER_PHY_LSI_TYPE_KIT_COMPONENT,
  .flow_control = ETHER_PHY_FLOW_CONTROL_DISABLE, .mii_type = ETHER_PHY_MII_TYPE_RMII, .p_context = NULL, .p_extend =
          &g_ether_phy0_extended_cfg,

};
/* Instance structure to use this module. */
const ether_phy_instance_t g_ether_phy0 =
{ .p_ctrl = &g_ether_phy0_ctrl, .p_cfg = &g_ether_phy0_cfg, .p_api = &g_ether_phy_on_ether_phy };
dtc_instance_ctrl_t g_transfer2_ctrl;

#if (1 == 1)
transfer_info_t g_transfer2_info DTC_TRANSFER_INFO_ALIGNMENT =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = (uint16_t) 0,
  .length = (uint16_t) 0, };

#elif (1 > 1)
/* User is responsible to initialize the array. */
transfer_info_t g_transfer2_info[1] DTC_TRANSFER_INFO_ALIGNMENT;
#else
/* User must call api::reconfigure before enable DTC transfer. */
#endif

const dtc_extended_cfg_t g_transfer2_cfg_extend =
{ .activation_source = VECTOR_NUMBER_SPI0_RXI, };

const transfer_cfg_t g_transfer2_cfg =
{
#if (1 == 1)
  .p_info = &g_transfer2_info,
#elif (1 > 1)
    .p_info              = g_transfer2_info,
#else
    .p_info = NULL,
#endif
  .p_extend = &g_transfer2_cfg_extend, };

/* Instance structure to use this module. */
const transfer_instance_t g_transfer2 =
{ .p_ctrl = &g_transfer2_ctrl, .p_cfg = &g_transfer2_cfg, .p_api = &g_transfer_on_dtc };
dtc_instance_ctrl_t g_transfer1_ctrl;

#if (1 == 1)
transfer_info_t g_transfer1_info DTC_TRANSFER_INFO_ALIGNMENT =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = (uint16_t) 0,
  .length = (uint16_t) 0, };

#elif (1 > 1)
/* User is responsible to initialize the array. */
transfer_info_t g_transfer1_info[1] DTC_TRANSFER_INFO_ALIGNMENT;
#else
/* User must call api::reconfigure before enable DTC transfer. */
#endif

const dtc_extended_cfg_t g_transfer1_cfg_extend =
{ .activation_source = VECTOR_NUMBER_SPI0_TXI, };

const transfer_cfg_t g_transfer1_cfg =
{
#if (1 == 1)
  .p_info = &g_transfer1_info,
#elif (1 > 1)
    .p_info              = g_transfer1_info,
#else
    .p_info = NULL,
#endif
  .p_extend = &g_transfer1_cfg_extend, };

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{ .p_ctrl = &g_transfer1_ctrl, .p_cfg = &g_transfer1_cfg, .p_api = &g_transfer_on_dtc };
spi_b_instance_ctrl_t g_spi0_ctrl;

/** SPI extended configuration for SPI HAL driver */
const spi_b_extended_cfg_t g_spi0_ext_cfg =
{ .spi_clksyn = SPI_B_SSL_MODE_CLK_SYN,
  .spi_comm = SPI_B_COMMUNICATION_FULL_DUPLEX,
  .ssl_polarity = SPI_B_SSLP_LOW,
  .ssl_select = SPI_B_SSL_SELECT_SSL0,
  .mosi_idle = SPI_B_MOSI_IDLE_VALUE_FIXING_DISABLE,
  .parity = SPI_B_PARITY_MODE_DISABLE,
  .byte_swap = SPI_B_BYTE_SWAP_DISABLE,
  .clock_source = SPI_B_CLOCK_SOURCE_PCLK,
  .spck_div =
  {
  /* Actual calculated bitrate: 15000000. */.spbr = 3,
    .brdv = 0 },
  .spck_delay = SPI_B_DELAY_COUNT_1,
  .ssl_negation_delay = SPI_B_DELAY_COUNT_1,
  .next_access_delay = SPI_B_DELAY_COUNT_1,

};

/** SPI configuration for SPI HAL driver */
const spi_cfg_t g_spi0_cfg =
{ .channel = 0,

#if defined(VECTOR_NUMBER_SPI0_RXI)
    .rxi_irq             = VECTOR_NUMBER_SPI0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_TXI)
    .txi_irq             = VECTOR_NUMBER_SPI0_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_TEI)
    .tei_irq             = VECTOR_NUMBER_SPI0_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_ERI)
    .eri_irq             = VECTOR_NUMBER_SPI0_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif

  .rxi_ipl = (12),
  .txi_ipl = (12),
  .tei_ipl = (12),
  .eri_ipl = (12),

  .operating_mode = SPI_MODE_MASTER,

  .clk_phase = SPI_CLK_PHASE_EDGE_ODD,
  .clk_polarity = SPI_CLK_POLARITY_LOW,

  .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE,
  .bit_order = SPI_BIT_ORDER_MSB_FIRST,
  .p_transfer_tx = g_spi0_P_TRANSFER_TX,
  .p_transfer_rx = g_spi0_P_TRANSFER_RX,
  .p_callback = spi_callback,

  .p_context = NULL,
  .p_extend = (void*) &g_spi0_ext_cfg, };

/* Instance structure to use this module. */
const spi_instance_t g_spi0 =
{ .p_ctrl = &g_spi0_ctrl, .p_cfg = &g_spi0_cfg, .p_api = &g_spi_on_spi_b };
dtc_instance_ctrl_t g_transfer0_ctrl;

#if (1 == 1)
transfer_info_t g_transfer0_info DTC_TRANSFER_INFO_ALIGNMENT =
{ .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
  .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE,
  .transfer_settings_word_b.mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = (uint16_t) 0,
  .length = (uint16_t) 0, };

#elif (1 > 1)
/* User is responsible to initialize the array. */
transfer_info_t g_transfer0_info[1] DTC_TRANSFER_INFO_ALIGNMENT;
#else
/* User must call api::reconfigure before enable DTC transfer. */
#endif

const dtc_extended_cfg_t g_transfer0_cfg_extend =
{ .activation_source = VECTOR_NUMBER_SSI0_TXI, };

const transfer_cfg_t g_transfer0_cfg =
{
#if (1 == 1)
  .p_info = &g_transfer0_info,
#elif (1 > 1)
    .p_info              = g_transfer0_info,
#else
    .p_info = NULL,
#endif
  .p_extend = &g_transfer0_cfg_extend, };

/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{ .p_ctrl = &g_transfer0_ctrl, .p_cfg = &g_transfer0_cfg, .p_api = &g_transfer_on_dtc };
ssi_instance_ctrl_t g_i2s0_ctrl;

/** SSI instance configuration */
const ssi_extended_cfg_t g_i2s0_cfg_extend =
{ .audio_clock = (ssi_audio_clock_t) SSI_AUDIO_CLOCK_EXTERNAL, .bit_clock_div = SSI_CLOCK_DIV_1, };

/** I2S interface configuration */
const i2s_cfg_t g_i2s0_cfg =
{ .channel = 0, .pcm_width = I2S_PCM_WIDTH_16_BITS, .operating_mode = I2S_MODE_MASTER, .word_length =
          I2S_WORD_LENGTH_16_BITS,
  .ws_continue = I2S_WS_CONTINUE_OFF, .p_callback = NULL, .p_context = NULL, .p_extend = &g_i2s0_cfg_extend,
#if (2) != BSP_IRQ_DISABLED
  .txi_irq = VECTOR_NUMBER_SSI0_TXI,
#else
                .txi_irq                 = FSP_INVALID_VECTOR,
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
                .rxi_irq                 = VECTOR_NUMBER_SSI0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SSI0_INT)
                .int_irq                 = VECTOR_NUMBER_SSI0_INT,
#else
  .int_irq = FSP_INVALID_VECTOR,
#endif
  .txi_ipl = (2),
  .rxi_ipl = (BSP_IRQ_DISABLED), .idle_err_ipl = (2),
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer0)
                .p_transfer_tx       = NULL,
#else
  .p_transfer_tx = &g_transfer0,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
        };

/* Instance structure to use this module. */
const i2s_instance_t g_i2s0 =
{ .p_ctrl = &g_i2s0_ctrl, .p_cfg = &g_i2s0_cfg, .p_api = &g_i2s_on_ssi };
void g_hal_init(void)
{
    g_common_init ();
}
