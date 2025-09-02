#ifndef SHRAVYA_CONFIG_H
#define SHRAVYA_CONFIG_H

/* System Configuration */
#define SHRAVYA_VERSION                "2.0"
#define SYSTEM_CLOCK_FREQ_HZ           480000000  // 480MHz
#define EEG_SAMPLE_RATE_HZ             500        // 500Hz sampling

/* Task Priorities (μT-Kernel 3.0) */
#define TASK_PRIORITY_EEG_ACQ          10  // Highest priority
#define TASK_PRIORITY_PREPROCESSING    15
#define TASK_PRIORITY_FEATURE_EXTRACT  20
#define TASK_PRIORITY_CLASSIFICATION   25
#define TASK_PRIORITY_HAPTIC          30
#define TASK_PRIORITY_COMMUNICATION   35

/* Buffer Sizes */
#define EEG_BUFFER_SIZE_SAMPLES        2048  // 4 seconds at 500Hz
#define EEG_PROCESSING_WINDOW          1024  // 2 seconds overlap

/* Hardware Pin Assignments */
#define ADS1263_SPI_CHANNEL            0
#define ADS1263_CS_PIN                 BSP_IO_PORT_01_PIN_00
#define ADS1263_DRDY_PIN               BSP_IO_PORT_01_PIN_01
#define VIBRATION_MOTOR_LEFT_PIN       BSP_IO_PORT_02_PIN_00
#define VIBRATION_MOTOR_RIGHT_PIN      BSP_IO_PORT_02_PIN_01

/* EEG Signal Processing */
#define EEG_INPUT_RANGE_UV             100.0f    // ±100μV
#define EEG_NOISE_FLOOR_UV             1.0f      // <1μV RMS
#define COMMON_MODE_REJECTION_DB       80.0f     // >80dB at 50Hz

#endif /* SHRAVYA_CONFIG_H */
