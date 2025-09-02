#include "hal_data.h"
#include "eeg_types.h"
#include "cognitive_states.h"
#include "signal_processing.h"
#include "mtk3_bsp2/include/tk/tkernel.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Communication Configuration */
#define JSON_BUFFER_SIZE           2048    // JSON payload buffer
#define N8N_WEBHOOK_URL           "https://your-n8n-instance.com/webhook/shravya"
#define TRANSMISSION_INTERVAL_S    30      // 30 second intervals
#define MAX_RETRIES               3       // Network retry attempts
#define TIMEOUT_MS                5000    // 5 second timeout

/* Data Aggregation Window */
#define AGGREGATION_WINDOW_SIZE   6       // 6 samples (3 minutes at 30s intervals)
#define FEATURE_HISTORY_SIZE      10      // Keep 10 feature vectors

/* Communication State */
typedef struct {
    cognitive_classification_t classification_history[AGGREGATION_WINDOW_SIZE];
    feature_vector_t feature_history[FEATURE_HISTORY_SIZE];
    uint32_t history_index;
    uint32_t transmissions_sent;
    uint32_t transmission_errors;
    uint32_t last_transmission_time;
    bool connection_active;
    float data_quality_score;
} communication_state_t;

/* JSON Payload Structure */
typedef struct {
    char timestamp[32];
    char device_id[16];
    float session_duration_min;

    /* Aggregated Cognitive Data */
    struct {
        float avg_wellness_score;
        float dominant_state_confidence;
        char dominant_state_name[16];
        uint32_t intervention_count;
        float intervention_effectiveness;
        uint32_t state_transitions;
    } cognitive_summary;

    /* EEG Signal Quality */
    struct {
        float avg_snr_db;
        float signal_stability;
        uint32_t artifact_count;
        float electrode_quality;
    } signal_quality;

    /* Frequency Band Analysis */
    struct {
        float delta_avg;
        float theta_avg;
        float alpha_avg;
        float beta_avg;
        float gamma_avg;
        float alpha_beta_ratio;
        float spectral_entropy;
    } frequency_analysis;

    /* Behavioral Patterns */
    struct {
        float stress_episodes_per_hour;
        float focus_duration_avg_min;
        float anxiety_severity_avg;
        float fatigue_onset_hour;
        char primary_stressor[32];
    } behavioral_insights;

} n8n_payload_t;

/* Global Variables */
static communication_state_t comm_state;
static char json_buffer[JSON_BUFFER_SIZE];
static volatile bool communication_initialized = false;
static uint32_t session_start_time;

/* Private Function Prototypes */
static void aggregate_cognitive_data(n8n_payload_t *payload);
static void aggregate_signal_quality(n8n_payload_t *payload);
static void aggregate_frequency_data(n8n_payload_t *payload);
static void analyze_behavioral_patterns(n8n_payload_t *payload);
static void build_json_payload(const n8n_payload_t *payload, char *json_buffer, size_t buffer_size);
static fsp_err_t send_to_n8n_webhook(const char *json_data);
static void get_current_timestamp(char *timestamp, size_t size);
static float calculate_data_quality(void);
static const char* cognitive_state_to_string(cognitive_state_type_t state);

/**
 * @brief Initialize communication system
 */
fsp_err_t communication_init(void)
{
    /* Clear communication state */
    memset(&comm_state, 0, sizeof(comm_state));

    /* Initialize network interface (placeholder) */
    /* In production, this would initialize WiFi/Bluetooth/cellular */

    session_start_time = R_FSP_SystemClockHzGet() / 1000;
    comm_state.connection_active = true;  // Assume active for simulation
    communication_initialized = true;

    return FSP_SUCCESS;
}

/**
 * @brief Aggregate cognitive data from history
 */
static void aggregate_cognitive_data(n8n_payload_t *payload)
{
    float wellness_sum = 0.0f;
    uint32_t intervention_sum = 0;
    uint32_t valid_samples = 0;
    cognitive_state_type_t current_state = COGNITIVE_STATE_CALM;
    cognitive_state_type_t prev_state = COGNITIVE_STATE_CALM;
    uint32_t transitions = 0;

    /* Calculate averages from history */
    for (int i = 0; i < AGGREGATION_WINDOW_SIZE; i++) {
        cognitive_classification_t *sample = &comm_state.classification_history[i];

        if (sample->overall_wellness_score > 0) {  // Valid sample
            wellness_sum += sample->overall_wellness_score;

            if (sample->intervention_needed) {
                intervention_sum++;
            }

            /* Count state transitions */
            if (valid_samples > 0 && sample->dominant_state != prev_state) {
                transitions++;
            }

            prev_state = sample->dominant_state;
            current_state = sample->dominant_state;  // Latest state
            valid_samples++;
        }
    }

    /* Fill cognitive summary */
    payload->cognitive_summary.avg_wellness_score = (valid_samples > 0) ?
        wellness_sum / valid_samples : 0.0f;
    payload->cognitive_summary.intervention_count = intervention_sum;
    payload->cognitive_summary.state_transitions = transitions;
    strcpy(payload->cognitive_summary.dominant_state_name,
           cognitive_state_to_string(current_state));

    /* Get current state confidence */
    cognitive_classification_t current_result;
    if (get_classification_result(&current_result) == FSP_SUCCESS) {
        payload->cognitive_summary.dominant_state_confidence =
            current_result.confidence_scores[current_result.dominant_state];
    }

    /* Get haptic effectiveness */
    get_haptic_statistics(NULL, &payload->cognitive_summary.intervention_effectiveness, NULL);
}

/**
 * @brief Aggregate signal quality metrics
 */
static void aggregate_signal_quality(n8n_payload_t *payload)
{
    uint32_t total_samples, total_artifacts;
    bool processing_ready;

    /* Get processing statistics */
    signal_processing_get_stats(&total_samples, &total_artifacts, &processing_ready);

    /* Calculate averages from feature history */
    float snr_sum = 0.0f, stability_sum = 0.0f;
    uint32_t valid_features = 0;

    for (int i = 0; i < FEATURE_HISTORY_SIZE; i++) {
        feature_vector_t *features = &comm_state.feature_history[i];

        if (features->snr_estimate > 0) {  // Valid feature
            snr_sum += features->snr_estimate;
            stability_sum += features->signal_stability;
            valid_features++;
        }
    }

    payload->signal_quality.avg_snr_db = (valid_features > 0) ? snr_sum / valid_features : 0.0f;
    payload->signal_quality.signal_stability = (valid_features > 0) ?
        stability_sum / valid_features : 0.0f;
    payload->signal_quality.artifact_count = total_artifacts;
    payload->signal_quality.electrode_quality = comm_state.data_quality_score;
}

/**
 * @brief Aggregate frequency domain data
 */
static void aggregate_frequency_data(n8n_payload_t *payload)
{
    float delta_sum = 0.0f, theta_sum = 0.0f, alpha_sum = 0.0f;
    float beta_sum = 0.0f, gamma_sum = 0.0f, ratio_sum = 0.0f, entropy_sum = 0.0f;
    uint32_t valid_features = 0;

    for (int i = 0; i < FEATURE_HISTORY_SIZE; i++) {
        feature_vector_t *features = &comm_state.feature_history[i];

        if (features->delta_power > 0) {  // Valid feature
            delta_sum += features->delta_power;
            theta_sum += features->theta_power;
            alpha_sum += features->alpha_power;
            beta_sum += features->beta_power;
            gamma_sum += features->gamma_power;
            ratio_sum += features->alpha_beta_ratio;
            entropy_sum += features->spectral_entropy;
            valid_features++;
        }
    }

    if (valid_features > 0) {
        payload->frequency_analysis.delta_avg = delta_sum / valid_features;
        payload->frequency_analysis.theta_avg = theta_sum / valid_features;
        payload->frequency_analysis.alpha_avg = alpha_sum / valid_features;
        payload->frequency_analysis.beta_avg = beta_sum / valid_features;
        payload->frequency_analysis.gamma_avg = gamma_sum / valid_features;
        payload->frequency_analysis.alpha_beta_ratio = ratio_sum / valid_features;
        payload->frequency_analysis.spectral_entropy = entropy_sum / valid_features;
    }
}

/**
 * @brief Analyze behavioral patterns from data
 */
static void analyze_behavioral_patterns(n8n_payload_t *payload)
{
    uint32_t stress_episodes = 0;
    float focus_duration_sum = 0.0f;
    float anxiety_sum = 0.0f;
    uint32_t current_time = R_FSP_SystemClockHzGet() / 1000;
    float session_hours = (current_time - session_start_time) / 3600.0f;

    /* Analyze patterns from history */
    for (int i = 0; i < AGGREGATION_WINDOW_SIZE; i++) {
        cognitive_classification_t *sample = &comm_state.classification_history[i];

        /* Count stress episodes */
        if (sample->dominant_state == COGNITIVE_STATE_STRESS &&
            sample->confidence_scores[COGNITIVE_STATE_STRESS] > 0.7f) {
            stress_episodes++;
        }

        /* Calculate focus duration */
        if (sample->dominant_state == COGNITIVE_STATE_FOCUS) {
            focus_duration_sum += 0.5f;  // 30 second windows
        }

        /* Average anxiety severity */
        anxiety_sum += sample->confidence_scores[COGNITIVE_STATE_ANXIETY];
    }

    payload->behavioral_insights.stress_episodes_per_hour =
        (session_hours > 0) ? stress_episodes / session_hours : 0.0f;
    payload->behavioral_insights.focus_duration_avg_min = focus_duration_sum;
    payload->behavioral_insights.anxiety_severity_avg = anxiety_sum / AGGREGATION_WINDOW_SIZE;

    /* Determine primary stressor (simplified) */
    if (payload->behavioral_insights.stress_episodes_per_hour > 2.0f) {
        strcpy(payload->behavioral_insights.primary_stressor, "high_frequency_stress");
    } else if (payload->behavioral_insights.anxiety_severity_avg > 0.6f) {
        strcpy(payload->behavioral_insights.primary_stressor, "persistent_anxiety");
    } else if (payload->behavioral_insights.focus_duration_avg_min < 5.0f) {
        strcpy(payload->behavioral_insights.primary_stressor, "attention_deficits");
    } else {
        strcpy(payload->behavioral_insights.primary_stressor, "none_detected");
    }
}

/**
 * @brief Build JSON payload for n8n webhook
 */
static void build_json_payload(const n8n_payload_t *payload, char *json_buffer, size_t buffer_size)
{
    snprintf(json_buffer, buffer_size,
        "{\n"
        "  \"timestamp\": \"%s\",\n"
        "  \"device_id\": \"%s\",\n"
        "  \"session_duration_min\": %.1f,\n"
        "  \"cognitive_summary\": {\n"
        "    \"avg_wellness_score\": %.3f,\n"
        "    \"dominant_state\": \"%s\",\n"
        "    \"dominant_state_confidence\": %.3f,\n"
        "    \"intervention_count\": %u,\n"
        "    \"intervention_effectiveness\": %.3f,\n"
        "    \"state_transitions\": %u\n"
        "  },\n"
        "  \"signal_quality\": {\n"
        "    \"avg_snr_db\": %.1f,\n"
        "    \"signal_stability\": %.3f,\n"
        "    \"artifact_count\": %u,\n"
        "    \"electrode_quality\": %.3f\n"
        "  },\n"
        "  \"frequency_analysis\": {\n"
        "    \"delta_avg\": %.3f,\n"
        "    \"theta_avg\": %.3f,\n"
        "    \"alpha_avg\": %.3f,\n"
        "    \"beta_avg\": %.3f,\n"
        "    \"gamma_avg\": %.3f,\n"
        "    \"alpha_beta_ratio\": %.3f,\n"
        "    \"spectral_entropy\": %.3f\n"
        "  },\n"
        "  \"behavioral_insights\": {\n"
        "    \"stress_episodes_per_hour\": %.1f,\n"
        "    \"focus_duration_avg_min\": %.1f,\n"
        "    \"anxiety_severity_avg\": %.3f,\n"
        "    \"primary_stressor\": \"%s\"\n"
        "  }\n"
        "}",
        payload->timestamp,
        payload->device_id,
        payload->session_duration_min,
        payload->cognitive_summary.avg_wellness_score,
        payload->cognitive_summary.dominant_state_name,
        payload->cognitive_summary.dominant_state_confidence,
        payload->cognitive_summary.intervention_count,
        payload->cognitive_summary.intervention_effectiveness,
        payload->cognitive_summary.state_transitions,
        payload->signal_quality.avg_snr_db,
        payload->signal_quality.signal_stability,
        payload->signal_quality.artifact_count,
        payload->signal_quality.electrode_quality,
        payload->frequency_analysis.delta_avg,
        payload->frequency_analysis.theta_avg,
        payload->frequency_analysis.alpha_avg,
        payload->frequency_analysis.beta_avg,
        payload->frequency_analysis.gamma_avg,
        payload->frequency_analysis.alpha_beta_ratio,
        payload->frequency_analysis.spectral_entropy,
        payload->behavioral_insights.stress_episodes_per_hour,
        payload->behavioral_insights.focus_duration_avg_min,
        payload->behavioral_insights.anxiety_severity_avg,
        payload->behavioral_insights.primary_stressor
    );
}

/**
 * @brief Send data to n8n webhook (placeholder implementation)
 */
static fsp_err_t send_to_n8n_webhook(const char *json_data)
{
    /* Placeholder for actual HTTP/HTTPS transmission */
    /* In production, this would use WiFi/cellular module */

    /* Simulate network transmission */
    R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);

    /* For debugging - could be sent via UART to external gateway */
    printf("N8N Webhook Payload:\n%s\n", json_data);

    comm_state.transmissions_sent++;
    comm_state.last_transmission_time = R_FSP_SystemClockHzGet() / 1000;

    return FSP_SUCCESS;  // Simulate success
}

/**
 * @brief Get current timestamp in ISO 8601 format
 */
static void get_current_timestamp(char *timestamp, size_t size)
{
    uint32_t current_time = R_FSP_SystemClockHzGet() / 1000;
    snprintf(timestamp, size, "2025-09-02T%02u:%02u:%02uZ",
             (current_time / 3600) % 24,
             (current_time / 60) % 60,
             current_time % 60);
}

/**
 * @brief Convert cognitive state enum to string
 */
static const char* cognitive_state_to_string(cognitive_state_type_t state)
{
    switch (state) {
        case COGNITIVE_STATE_FOCUS: return "focus";
        case COGNITIVE_STATE_STRESS: return "stress";
        case COGNITIVE_STATE_ANXIETY: return "anxiety";
        case COGNITIVE_STATE_FATIGUE: return "fatigue";
        case COGNITIVE_STATE_CALM: return "calm";
        case COGNITIVE_STATE_BOREDOM: return "boredom";
        default: return "unknown";
    }
}

/**
 * @brief μT-Kernel Task: Communication (30-second intervals)
 * Priority: 35 (Lowest)
 */
void task_communication_entry(INT stacd, void *exinf)
{
    (void)stacd;
    (void)exinf;

    n8n_payload_t payload;
    cognitive_classification_t current_classification;
    feature_vector_t current_features;
    uint32_t current_time;

    /* Initialize communication system */
    if (communication_init() != FSP_SUCCESS) {
        while(1) tk_dly_tsk(1000);
    }

    while(1) {
        /* Wait for 30-second interval */
        tk_dly_tsk(TRANSMISSION_INTERVAL_S * 1000);

        /* Collect current data */
        if (get_classification_result(&current_classification) == FSP_SUCCESS) {
            /* Store in history */
            comm_state.classification_history[comm_state.history_index % AGGREGATION_WINDOW_SIZE] =
                current_classification;
        }

        if (get_feature_vector(&current_features) == FSP_SUCCESS) {
            /* Store in feature history */
            comm_state.feature_history[comm_state.history_index % FEATURE_HISTORY_SIZE] =
                current_features;
        }

        comm_state.history_index++;

        /* Build payload every 3 minutes (6 samples) */
        if ((comm_state.history_index % 6) == 0 && comm_state.history_index > 0) {
            /* Clear payload structure */
            memset(&payload, 0, sizeof(payload));

            /* Fill basic info */
            get_current_timestamp(payload.timestamp, sizeof(payload.timestamp));
            strcpy(payload.device_id, "SHRAVYA_001");

            current_time = R_FSP_SystemClockHzGet() / 1000;
            payload.session_duration_min = (current_time - session_start_time) / 60.0f;

            /* Aggregate all data categories */
            aggregate_cognitive_data(&payload);
            aggregate_signal_quality(&payload);
            aggregate_frequency_data(&payload);
            analyze_behavioral_patterns(&payload);

            /* Build JSON and send */
            build_json_payload(&payload, json_buffer, JSON_BUFFER_SIZE);

            /* Attempt transmission with retries */
            for (int retry = 0; retry < MAX_RETRIES; retry++) {
                if (send_to_n8n_webhook(json_buffer) == FSP_SUCCESS) {
                    break;  // Success
                }
                comm_state.transmission_errors++;
                tk_dly_tsk(1000);  // 1 second retry delay
            }

            /* Update data quality score */
            comm_state.data_quality_score = calculate_data_quality();
        }
    }
}

/**
 * @brief Calculate overall data quality score
 */
static float calculate_data_quality(void)
{
    float quality_score = 1.0f;

    /* Reduce quality for high error rates */
    if (comm_state.transmissions_sent > 0) {
        float error_rate = (float)comm_state.transmission_errors / comm_state.transmissions_sent;
        quality_score *= (1.0f - error_rate);
    }

    /* Reduce quality for poor signal */
    uint32_t total_samples, total_artifacts;
    bool processing_ready;
    signal_processing_get_stats(&total_samples, &total_artifacts, &processing_ready);

    if (total_samples > 0) {
        float artifact_rate = (float)total_artifacts / total_samples;
        quality_score *= (1.0f - artifact_rate);
    }

    return (quality_score < 0.0f) ? 0.0f : quality_score;
}

/**
 * @brief Get communication statistics
 */
fsp_err_t get_communication_stats(uint32_t *transmissions, uint32_t *errors, float *quality)
{
    if (transmissions) *transmissions = comm_state.transmissions_sent;
    if (errors) *errors = comm_state.transmission_errors;
    if (quality) *quality = comm_state.data_quality_score;

    return FSP_SUCCESS;
}
