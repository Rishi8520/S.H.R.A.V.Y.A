#ifndef SEMAPHORE_GLOBALS_H
#define SEMAPHORE_GLOBALS_H

#include "mtk3_bsp2/include/tk/tkernel.h"

// Global semaphore declarations
extern ID eeg_data_semaphore;
extern ID preprocessing_semaphore;
extern ID feature_extraction_semaphore;
extern ID classification_semaphore;
extern ID haptic_semaphore;

// Initialize function
ER initialize_global_semaphores(void);

#endif
