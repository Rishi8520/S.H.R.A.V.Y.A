#ifndef SHRAVYA_CONFIG_H
#define SHRAVYA_CONFIG_H

/* System Configuration */
#define SHRAVYA_VERSION "2.0"
#define SYSTEM_CLOCK_FREQ_HZ 480000000 // 480MHz

/* ✅ PHASE 1: RDATA Configuration */
#define EEG_SAMPLE_RATE_HZ 2000         // 2kHz for rich EEG data
#define EEG_CHANNELS 2                  // Dual channel (left/right)
#define EEG_BUFFER_SIZE_SAMPLES 16384   // 8 seconds circular buffer at 2kHz
#define EEG_PROCESSING_WINDOW 4096      // 2 second processing window

/* ADS1263 RDATA Configuration */
#define ADS1263_RDATA_MODE_ENABLED 1    // Enable direct RDATA mode
#define ADS1263_RDATA_TIMEOUT_MS 10     // Max wait for RDATA
#define ADS1263_RETRY_COUNT 3           // Hardware retry attempts
#define ADS1263_SAMPLE_INTERVAL_US 500  // 500μs = 2000 SPS

/* Task Priorities (μT-Kernel 3.0) */
#define TASK_PRIORITY_EEG_ACQ 10        // Highest priority
#define TASK_PRIORITY_PREPROCESSING 15
#define TASK_PRIORITY_FEATURE_EXTRACT 20
#define TASK_PRIORITY_CLASSIFICATION 25
#define TASK_PRIORITY_HAPTIC 30
#define TASK_PRIORITY_COMMUNICATION 35

/* Hardware Pin Assignments Based on Board Image */
#define ADS1263_CS_PIN BSP_IO_PORT_04_PIN_13  // P413 - Your actual CS connection
#define ADS1263_SCK_PIN BSP_IO_PORT_04_PIN_12 // P412 - Your SCK connection
#define ADS1263_MOSI_PIN BSP_IO_PORT_04_PIN_11 // P411 - Your MOSI connection
#define ADS1263_MISO_PIN BSP_IO_PORT_04_PIN_10 // P410 - Your MISO connection
#define ADS1263_DRDY_PIN BSP_IO_PORT_00_PIN_04 // P004 - Pin A4 IRQ0

/* Vibration Motor Pins */
#define VIBRATION_MOTOR_LEFT_PIN BSP_IO_PORT_03_PIN_01
#define VIBRATION_MOTOR_RIGHT_PIN BSP_IO_PORT_03_PIN_02

#endif
