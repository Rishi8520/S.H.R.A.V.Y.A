#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include "hal_data.h"

// System initialization functions
fsp_err_t communication_init(void);
fsp_err_t audio_interface_init(void);
fsp_err_t power_management_init(void);
fsp_err_t haptic_feedback_init(void);
fsp_err_t cognitive_classifier_init(void);

#endif
