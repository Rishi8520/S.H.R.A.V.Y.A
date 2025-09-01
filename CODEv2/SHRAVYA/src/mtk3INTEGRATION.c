/* mtk3_integration.c - μT-Kernel 3.0 system integration */
#include "hal_data.h"
#include "shravya_config.h"
#include "eeg_types.h"

/* Include μT-Kernel 3.0 headers */
#include "mtk3_bsp2/include/tk/tkernel.h"
#include "mtk3_bsp2/include/tk/device.h"

/* Task Control Blocks */
static ID task_eeg_acquisition;
static ID task_preprocessing;
static ID task_feature_extraction;
static ID task_classification;
static ID task_haptic_feedback;
static ID task_communication;

/* Synchronization Objects */
static ID eeg_data_semaphore;
static ID processed_data_mutex;
static ID classification_event_flag;

/* Task Stack Sizes */
#define STACK_SIZE_EEG_ACQ        2048
#define STACK_SIZE_PREPROCESSING  2048
#define STACK_SIZE_FEATURE_EXTRACT 3072
#define STACK_SIZE_CLASSIFICATION  4096
#define STACK_SIZE_HAPTIC         1024
#define STACK_SIZE_COMMUNICATION  2048

/* Task Entry Points - Forward Declarations */
void task_eeg_acquisition_entry(INT stacd, void *exinf);
void task_preprocessing_entry(INT stacd, void *exinf);
void task_feature_extraction_entry(INT stacd, void *exinf);
void task_classification_entry(INT stacd, void *exinf);
void task_haptic_feedback_entry(INT stacd, void *exinf);
void task_communication_entry(INT stacd, void *exinf);

/* Initialize μT-Kernel 3.0 System */
ER mtk3_system_init(void)
{
    ER ercd = E_OK;

    /* Create synchronization objects */
    T_CSEM csem = {TA_TFIFO, 0, 1}; // Binary semaphore
    eeg_data_semaphore = tk_cre_sem(&csem);

    T_CMTX cmtx = {TA_TFIFO, 1}; // Mutex with priority ceiling
    processed_data_mutex = tk_cre_mtx(&cmtx);

    T_CFLG cflg = {TA_TFIFO | TA_WMUL, 0}; // Event flag
    classification_event_flag = tk_cre_flg(&cflg);

    /* Create tasks */
    T_CTSK ctsk;

    // EEG Acquisition Task (Highest Priority)
    ctsk.tskatr = TA_HLNG | TA_RNG3;
    ctsk.task = task_eeg_acquisition_entry;
    ctsk.itskpri = TASK_PRIORITY_EEG_ACQ;
    ctsk.stksz = STACK_SIZE_EEG_ACQ;
    ctsk.stkadr = NULL; // Auto allocation
    task_eeg_acquisition = tk_cre_tsk(&ctsk);

    // Preprocessing Task
    ctsk.task = task_preprocessing_entry;
    ctsk.itskpri = TASK_PRIORITY_PREPROCESSING;
    ctsk.stksz = STACK_SIZE_PREPROCESSING;
    task_preprocessing = tk_cre_tsk(&ctsk);

    // Feature Extraction Task
    ctsk.task = task_feature_extraction_entry;
    ctsk.itskpri = TASK_PRIORITY_FEATURE_EXTRACT;
    ctsk.stksz = STACK_SIZE_FEATURE_EXTRACT;
    task_feature_extraction = tk_cre_tsk(&ctsk);

    // Classification Task
    ctsk.task = task_classification_entry;
    ctsk.itskpri = TASK_PRIORITY_CLASSIFICATION;
    ctsk.stksz = STACK_SIZE_CLASSIFICATION;
    task_classification = tk_cre_tsk(&ctsk);

    // Haptic Feedback Task
    ctsk.task = task_haptic_feedback_entry;
    ctsk.itskpri = TASK_PRIORITY_HAPTIC;
    ctsk.stksz = STACK_SIZE_HAPTIC;
    task_haptic_feedback = tk_cre_tsk(&ctsk);

    // Communication Task
    ctsk.task = task_communication_entry;
    ctsk.itskpri = TASK_PRIORITY_COMMUNICATION;
    ctsk.stksz = STACK_SIZE_COMMUNICATION;
    task_communication = tk_cre_tsk(&ctsk);

    return ercd;
}

/* Start μT-Kernel 3.0 Scheduler */
ER mtk3_start_scheduler(void)
{
    /* Start all tasks */
    tk_sta_tsk(task_eeg_acquisition, 0);
    tk_sta_tsk(task_preprocessing, 0);
    tk_sta_tsk(task_feature_extraction, 0);
    tk_sta_tsk(task_classification, 0);
    tk_sta_tsk(task_haptic_feedback, 0);
    tk_sta_tsk(task_communication, 0);

    /* Start μT-Kernel 3.0 system */
    tk_set_pow(NORMAL_SPEED);

    return E_OK;
}
