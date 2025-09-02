#ifndef AUDIO_INTERFACE_H
#define AUDIO_INTERFACE_H

#include "hal_data.h"

fsp_err_t audio_interface_init(void);
fsp_err_t get_audio_statistics(uint32_t *voice_commands, float *noise_level, bool *is_listening);
void task_audio_interface_entry(INT stacd, void *exinf);

#endif
