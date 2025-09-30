#ifndef SEMAPHORES_GLOBAL_H
#define SEMAPHORES_GLOBAL_H

#include <stdint.h>

/* ✅ COMPLETE μT-Kernel 3.0 Type System - ESSENTIAL FOR TRON CONTEST */
#ifndef INT
typedef int INT;
#endif
#ifndef ER
typedef int ER;
#endif
#ifndef ID
typedef int ID;
#endif
#ifndef E_OK
#define E_OK (0)
#endif

/* ✅ Global SHRAVYA Semaphore Declarations - TRON Contest Architecture */
extern ID eeg_data_semaphore;
extern ID preprocessing_semaphore;
extern ID feature_extraction_semaphore;
extern ID classification_semaphore;
extern ID haptic_semaphore;
extern ID processed_semaphore;
extern ID features_ready_semaphore;    // Signal processing → Feature extraction
extern ID classification_ready_semaphore; // Feature extraction → AI classification
extern ID feedback_ready_semaphore;   // AI classification → Haptic + N8N

/* ✅ SHRAVYA System Initialization Function */
ER initialize_global_semaphores(void);

#endif /* SEMAPHORES_GLOBAL_H */
