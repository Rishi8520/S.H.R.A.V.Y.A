#ifndef COMMUNICATION_N8N_H
#define COMMUNICATION_N8N_H

#include "hal_data.h"

// μT-Kernel typedefs (if not already defined elsewhere)
#ifndef INT
typedef int INT;
#endif

// Function declarations
fsp_err_t communication_init(void);
fsp_err_t get_communication_stats(uint32_t *transmissions, uint32_t *errors, float *quality);
void task_communication_entry(INT stacd, void *exinf);

#endif /* COMMUNICATION_N8N_H */
