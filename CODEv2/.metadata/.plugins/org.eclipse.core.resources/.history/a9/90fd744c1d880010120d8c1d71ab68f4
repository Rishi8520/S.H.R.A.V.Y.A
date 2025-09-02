#include "semaphore_globals.h"

// Global semaphore definitions
ID eeg_data_semaphore = 0;
ID preprocessing_semaphore = 0;
ID feature_extraction_semaphore = 0;
ID classification_semaphore = 0;
ID haptic_semaphore = 0;

ER initialize_global_semaphores(void)
{
    T_CSEM csem = {TA_TFIFO, 0, 1};

    eeg_data_semaphore = tk_cre_sem(&csem);
    preprocessing_semaphore = tk_cre_sem(&csem);
    feature_extraction_semaphore = tk_cre_sem(&csem);
    classification_semaphore = tk_cre_sem(&csem);
    haptic_semaphore = tk_cre_sem(&csem);

    return E_OK;
}
