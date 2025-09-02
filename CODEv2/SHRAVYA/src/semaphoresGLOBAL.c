#include "semaphoresGLOBAL.h"

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

/* ✅ μT-Kernel 3.0 Task Attributes */
#ifndef TA_TFIFO
#define TA_TFIFO (0x00000000U)
#endif

/* ✅ μT-Kernel 3.0 Structure Types */
typedef struct {
    uint32_t sematr;    // Semaphore attributes
    int isemcnt;        // Initial semaphore count
    int maxsem;         // Maximum semaphore count
} T_CSEM;

/* ✅ μT-Kernel 3.0 Function Prototypes */
extern ID tk_cre_sem(T_CSEM *pk_csem);

// ✅ Global semaphore definitions - PRESERVED FOR TRON CONTEST
ID eeg_data_semaphore = 0;
ID preprocessing_semaphore = 0;
ID feature_extraction_semaphore = 0;
ID classification_semaphore = 0;
ID haptic_semaphore = 0;

/**
 * @brief Initialize global semaphores for SHRAVYA system
 * ✅ TRON Programming Contest 2025 Compliant
 */
ER initialize_global_semaphores(void)
{
    T_CSEM csem = {TA_TFIFO, 0, 1}; // Binary semaphore configuration

    /* ✅ Create all SHRAVYA inter-task semaphores */
    eeg_data_semaphore = tk_cre_sem(&csem);
    preprocessing_semaphore = tk_cre_sem(&csem);
    feature_extraction_semaphore = tk_cre_sem(&csem);
    classification_semaphore = tk_cre_sem(&csem);
    haptic_semaphore = tk_cre_sem(&csem);

    return E_OK;
}
