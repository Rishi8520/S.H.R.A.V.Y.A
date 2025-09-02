/* eeg_types.h - EEG data structures and types */
#ifndef EEG_TYPES_H
#define EEG_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "shravya_config.h"  // Add this for buffer size constants

/* EEG Signal Quality Structure */
typedef struct {
    float impedance_left_kohms;
    float impedance_right_kohms;
    bool contact_quality_good;
    uint8_t signal_noise_level;
    float common_mode_voltage;
} eeg_signal_quality_t;

/* EEG Raw Data Structure */
typedef struct {
    int32_t left_channel;     // Left electrode raw ADC value
    int32_t right_channel;    // Right electrode raw ADC value
    int32_t drl_feedback;     // DRL circuit feedback
    uint32_t timestamp_us;    // Microsecond timestamp
    eeg_signal_quality_t quality;
} eeg_raw_sample_t;

/* EEG Circular Buffer */
typedef struct {
    eeg_raw_sample_t samples[EEG_BUFFER_SIZE_SAMPLES];
    uint32_t write_index;
    uint32_t read_index;
    bool buffer_full;
    void* buffer_mutex;       // μT-Kernel mutex
} eeg_circular_buffer_t;

/* Frequency Domain Features */
typedef struct {
    float delta_power;        // 0.5-4Hz (deep sleep, attention)
    float theta_power;        // 4-8Hz (drowsiness, meditation)
    float alpha_power;        // 8-13Hz (relaxed awareness)
    float beta_power;         // 13-30Hz (active concentration)
    float gamma_power;        // 30-45Hz (high-level cognition)
    float spectral_entropy;
    float peak_frequency;
    float band_power_ratios[4]; // Alpha/Beta, Theta/Alpha, etc.
} eeg_frequency_features_t;

/* Time Domain Features */
typedef struct {
    float hjorth_activity;    // Signal variance
    float hjorth_mobility;    // Mean frequency
    float hjorth_complexity;  // Bandwidth measure
    float zero_crossing_rate;
    float signal_energy;
    float fractal_dimension;
} eeg_time_features_t;

/* Cognitive States (6 states as per requirements) */
typedef enum {
    COGNITIVE_STATE_FOCUS = 0,
    COGNITIVE_STATE_STRESS,
    COGNITIVE_STATE_ANXIETY,
    COGNITIVE_STATE_FATIGUE,
    COGNITIVE_STATE_CALM,
    COGNITIVE_STATE_BOREDOM,
    COGNITIVE_STATE_COUNT
} cognitive_state_type_t;

/* Cognitive State Classification Result */
typedef struct {
    float confidence_scores[COGNITIVE_STATE_COUNT]; // 0.0 to 1.0
    cognitive_state_type_t dominant_state;
    float overall_wellness_score;
    uint32_t inference_time_ms;
    bool intervention_needed;
} cognitive_classification_t;

#endif /* EEG_TYPES_H */
