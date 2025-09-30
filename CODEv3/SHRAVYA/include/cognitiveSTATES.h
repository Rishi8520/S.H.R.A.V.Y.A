#ifndef COGNITIVE_STATES_H
#define COGNITIVE_STATES_H

#include "eegTYPES.h"
#include "hal_data.h"
extern fsp_err_t trigger_drowsiness_alert(void);
extern fsp_err_t trigger_haptic_pattern(cognitive_state_type_t state);
#ifndef FATIGUE_THRESHOLD
#define FATIGUE_THRESHOLD 0.8f
#endif

#ifndef STRESS_THRESHOLD
#define STRESS_THRESHOLD 0.7f
#endif

#ifndef ANXIETY_THRESHOLD
#define ANXIETY_THRESHOLD 0.75f
#endif
/* Complete Feature Vector Structure */
typedef struct {
    /* Frequency Domain Features (10 features) */
    float delta_power;
    float theta_power;
    float alpha_power;
    float beta_power;
    float gamma_power;
    float alpha_beta_ratio;
    float theta_alpha_ratio;
    float spectral_entropy;
    float peak_frequency;
    float spectral_centroid;

    /* Time Domain Features (8 features) */
    float mean_amplitude;
    float rms_amplitude;
    float variance;
    float skewness;
    float kurtosis;
    float zero_crossing_rate;
    float hjorth_activity;
    float hjorth_mobility;

    /* Channel Coherence Features (4 features) */
    float cross_correlation;
    float coherence_alpha;
    float coherence_beta;
    float phase_lag_index;

    /* Signal Quality Features (2 features) */
    float snr_estimate;
    float signal_stability;
} feature_vector_t;

/* Function prototypes */
fsp_err_t cognitive_classifier_init(void);
fsp_err_t get_classification_result(cognitive_classification_t *result);
fsp_err_t get_feature_vector(feature_vector_t *features);
extern fsp_err_t trigger_haptic_pattern(cognitive_state_type_t state);
// Add these to cognitiveSTATES.h
extern feature_vector_t current_features;
extern void extract_frequency_features(const float *left_signal, const float *right_signal, int size);
extern void extract_time_domain_features(const float *left_signal, const float *right_signal, int size);
extern void extract_coherence_features(const float *left_signal, const float *right_signal, int size);
extern void extract_quality_features(const float *left_signal, const float *right_signal, int size);


#endif /* COGNITIVE_STATES_H */
