#ifndef COMMUNICATION_N8N_H
#define COMMUNICATION_N8N_H

#include "hal_data.h"

// μT-Kernel typedefs (if not already defined elsewhere)
#ifndef INT
typedef int INT;
#endif

typedef struct {
    char userid[32];
    char sessionid[32];
    char deviceid[32];
    char timestamp[32];

    struct {
        float focus;
        float stress;
        float anxiety;
        float fatigue;
        float calm;
        float flowstate;
    } cognitive_states;

    struct {
        float delta_power;
        float theta_power;
        float alpha_power;
        float beta_power;
        float gamma_power;
    } frequency_analysis;

    struct {
        float snr_db;
        bool artifact_detected;
    } signal_quality;

    uint32_t sampling_rate;
} n8n_eeg_payload_t;

// Function declarations
fsp_err_t communication_init(void);
fsp_err_t get_communication_stats(uint32_t *transmissions, uint32_t *errors, float *quality);
void task_communication_entry(INT stacd, void *exinf);

#endif /* COMMUNICATION_N8N_H */
