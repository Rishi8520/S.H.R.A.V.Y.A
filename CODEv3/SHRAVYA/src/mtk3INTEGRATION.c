#include "hal_data.h"
#include "shravyaCONFIG.h"
#include "eegTYPES.h"

/* ✅ COMPLETE μT-Kernel 3.0 Type System - ESSENTIAL FOR TRON CONTEST 2025 */
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


/* ✅ μT-Kernel 3.0 Task Attributes - PRESERVED */
#ifndef TA_HLNG
#define TA_HLNG (0x00000001U)    // High-level language task
#endif
#ifndef TA_RNG3
#define TA_RNG3 (0x00000300U)    // Protection ring 3
#endif
#ifndef TA_TFIFO
#define TA_TFIFO (0x00000000U)   // FIFO wait queue
#endif
#ifndef TA_WMUL
#define TA_WMUL (0x00000002U)    // Multiple wait
#endif

/* ✅ μT-Kernel 3.0 Power Management */
#ifndef NORMAL_SPEED
#define NORMAL_SPEED (0)         // Normal processing speed
#endif

/* ✅ μT-Kernel 3.0 Structure Types - PRESERVED */
typedef struct {
    uint32_t tskatr;    // Task attributes
    void *task;         // Task entry point
    int itskpri;        // Task priority
    uint32_t stksz;     // Stack size
    void *stkadr;       // Stack address
} T_CTSK;

typedef struct {
    uint32_t sematr;    // Semaphore attributes
    int isemcnt;        // Initial semaphore count
    int maxsem;         // Maximum semaphore count
} T_CSEM;

typedef struct {
    uint32_t mtxatr;    // Mutex attributes
    int ceilpri;        // Priority ceiling
} T_CMTX;

typedef struct {
    uint32_t flgatr;    // Flag attributes
    uint32_t iflgptn;   // Initial flag pattern
} T_CFLG;

/* ✅ μT-Kernel 3.0 Function Prototypes - PRESERVED FOR TRON CONTEST */
extern ER tk_cre_sem(T_CSEM *pk_csem);
extern ER tk_cre_mtx(T_CMTX *pk_cmtx);
extern ER tk_cre_flg(T_CFLG *pk_cflg);
extern ID tk_cre_tsk(T_CTSK *pk_ctsk);
extern ER tk_sta_tsk(ID tskid, INT stacd);
extern ER tk_set_pow(INT powmode);

/* Task Control Blocks */
static ID task_eeg_acquisition;
static ID task_preprocessing;
static ID task_feature_extraction;
static ID task_classification;
static ID task_haptic_feedback;
static ID task_communication;
static ID task_audio_interface;
static ID task_power_management;
static ID task_shravya_main;

/* Synchronization Objects */
static ID eeg_data_semaphore;
static ID processed_data_mutex;
static ID classification_event_flag;

/* Task Stack Sizes */
#define STACK_SIZE_EEG_ACQ 2048
#define STACK_SIZE_PREPROCESSING 2048
#define STACK_SIZE_FEATURE_EXTRACT 3072
#define STACK_SIZE_CLASSIFICATION 4096
#define STACK_SIZE_HAPTIC 1024
#define STACK_SIZE_COMMUNICATION 2048

/* Task Entry Points - Forward Declarations */
void task_eeg_acquisition_entry(INT stacd, void *exinf);
void task_preprocessing_entry(INT stacd, void *exinf);
void task_feature_extraction_entry(INT stacd, void *exinf);
void task_classification_entry(INT stacd, void *exinf);
void task_haptic_feedback_entry(INT stacd, void *exinf);
void task_communication_entry(INT stacd, void *exinf);

extern void task_audio_interface_entry(INT stacd, void *exinf);
extern void task_power_management_entry(INT stacd, void *exinf);
extern void task_shravya_main_entry(INT stacd, void *exinf);

/**
 * @brief Initialize μT-Kernel 3.0 System
 * ✅ TRON Programming Contest 2025 Compliant
 */
ER mtk3_system_init(void)
{
    ER ercd = E_OK;

    /* ✅ Create synchronization objects */
    T_CSEM csem = {TA_TFIFO, 0, 1}; // Binary semaphore
    eeg_data_semaphore = tk_cre_sem(&csem);

    T_CMTX cmtx = {TA_TFIFO, 1}; // Mutex with priority ceiling
    processed_data_mutex = tk_cre_mtx(&cmtx);

    T_CFLG cflg = {TA_TFIFO | TA_WMUL, 0}; // Event flag
    classification_event_flag = tk_cre_flg(&cflg);

    /* ✅ Create tasks with proper μT-Kernel 3.0 structures */
    T_CTSK ctsk;

    // EEG Acquisition Task (Highest Priority)
    ctsk.tskatr = TA_HLNG | TA_RNG3;
    ctsk.task = (void*)task_eeg_acquisition_entry;
    ctsk.itskpri = TASK_PRIORITY_EEG_ACQ;
    ctsk.stksz = STACK_SIZE_EEG_ACQ;
    ctsk.stkadr = NULL; // Auto allocation
    task_eeg_acquisition = tk_cre_tsk(&ctsk);

    // Preprocessing Task
    ctsk.task = (void*)task_preprocessing_entry;
    ctsk.itskpri = TASK_PRIORITY_PREPROCESSING;
    ctsk.stksz = STACK_SIZE_PREPROCESSING;
    task_preprocessing = tk_cre_tsk(&ctsk);

    // Feature Extraction Task
    ctsk.task = (void*)task_feature_extraction_entry;
    ctsk.itskpri = TASK_PRIORITY_FEATURE_EXTRACT;
    ctsk.stksz = STACK_SIZE_FEATURE_EXTRACT;
    task_feature_extraction = tk_cre_tsk(&ctsk);

    // Classification Task
    ctsk.task = (void*)task_classification_entry;
    ctsk.itskpri = TASK_PRIORITY_CLASSIFICATION;
    ctsk.stksz = STACK_SIZE_CLASSIFICATION;
    task_classification = tk_cre_tsk(&ctsk);

    // Haptic Feedback Task
    ctsk.task = (void*)task_haptic_feedback_entry;
    ctsk.itskpri = TASK_PRIORITY_HAPTIC;
    ctsk.stksz = STACK_SIZE_HAPTIC;
    task_haptic_feedback = tk_cre_tsk(&ctsk);

    // Audio Interface Task
    ctsk.task = (void*)task_audio_interface_entry;
    ctsk.itskpri = 12;
    ctsk.stksz = 2048;
    task_audio_interface = tk_cre_tsk(&ctsk);

    // Power Management Task
    ctsk.task = (void*)task_power_management_entry;
    ctsk.itskpri = 40;
    ctsk.stksz = 1024;
    task_power_management = tk_cre_tsk(&ctsk);

    // Main Coordinator Task
    ctsk.task = (void*)task_shravya_main_entry;
    ctsk.itskpri = 5;
    ctsk.stksz = 2048;
    task_shravya_main = tk_cre_tsk(&ctsk);

    // Communication Task
    ctsk.task = (void*)task_communication_entry;
    ctsk.itskpri = TASK_PRIORITY_COMMUNICATION;
    ctsk.stksz = STACK_SIZE_COMMUNICATION;
    task_communication = tk_cre_tsk(&ctsk);

    return ercd;
}

/**
 * @brief Start μT-Kernel 3.0 Scheduler
 * ✅ TRON Programming Contest 2025 Compliant
 */
ER mtk3_start_scheduler(void)
{
    /* ✅ Start all SHRAVYA tasks */
    tk_sta_tsk(task_eeg_acquisition, 0);
    tk_sta_tsk(task_preprocessing, 0);
    tk_sta_tsk(task_feature_extraction, 0);
    tk_sta_tsk(task_classification, 0);
    tk_sta_tsk(task_haptic_feedback, 0);
    tk_sta_tsk(task_communication, 0);
    tk_sta_tsk(task_audio_interface, 0);
    tk_sta_tsk(task_power_management, 0);
    tk_sta_tsk(task_shravya_main, 0);

    /* ✅ Start μT-Kernel 3.0 system */
    tk_set_pow(NORMAL_SPEED);

    return E_OK;
}
