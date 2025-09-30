#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H

#include "hal_data.h"

fsp_err_t power_management_init(void);
fsp_err_t get_power_statistics(uint8_t *battery_soc, uint16_t *voltage_mv, bool *low_battery, float *power_mw);
void task_power_management_entry(INT stacd, void *exinf);

#endif
