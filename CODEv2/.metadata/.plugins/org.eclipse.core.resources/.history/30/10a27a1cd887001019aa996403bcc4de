#ifndef HARDWARE_DRIVERS_H
#define HARDWARE_DRIVERS_H

/* Hardware driver function declarations */
fsp_err_t eeg_acquisition_init(void);
void timer_eeg_callback(timer_callback_args_t *p_args);

/* External semaphore declarations */
extern ID eeg_data_semaphore;
extern ID preprocessing_semaphore;
extern ID feature_extraction_semaphore;
extern ID classification_semaphore;
extern ID haptic_semaphore;

#endif /* HARDWARE_DRIVERS_H */
