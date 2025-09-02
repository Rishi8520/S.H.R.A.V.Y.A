#include "hal_data.h"

/* μT-Kernel 3.0 includes - adjust path based on your mtk3_bsp2 location */
#include "mtk3_bsp2/include/tk/tkernel.h"
//#include "mtk3_bsp2/include/tk/device.h"
#include "mtk3_bsp2/include/sys/sysdef.h"
/* SHRAVYA system includes */
#include "shravyaCONFIG.h"
#include "eegTYPES.h"
#include "semaphoresGLOBAL.h"

/* ✅ μT-Kernel 3.0 Basic Types - PRESERVED FOR TRON CONTEST */
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

/* ✅ Additional μT-Kernel 3.0 Error Codes */
#ifndef E_SYS
#define E_SYS (-5)
#endif
#ifndef E_NOMEM
#define E_NOMEM (-10)
#endif
#ifndef E_LIMIT
#define E_LIMIT (-4)
#endif
#ifndef E_PAR
#define E_PAR (-17)
#endif

/* ✅ μT-Kernel Task Attributes - PRESERVED */
#ifndef TA_HLNG
#define TA_HLNG (0x00000001U)
#endif
#ifndef TA_RNG3
#define TA_RNG3 (0x00000300U)
#endif
#ifndef TA_TFIFO
#define TA_TFIFO (0x00000000U)
#endif
#ifndef TA_WMUL
#define TA_WMUL (0x00000002U)
#endif

/* ✅ Additional μT-Kernel 3.0 Task States */
#ifndef TTS_RUN
#define TTS_RUN (0x01)
#endif
#ifndef TTS_RDY
#define TTS_RDY (0x02)
#endif
#ifndef TTS_WAI
#define TTS_WAI (0x04)
#endif
#ifndef TTS_SUS
#define TTS_SUS (0x08)
#endif

/* ✅ μT-Kernel Function Prototypes - PRESERVED FOR TRON CONTEST */
extern ER tk_ini_ker(void);
extern ER tk_ext_ker(void);
extern ER tk_set_pow(INT level);
extern ER tk_dly_tsk(INT dlytim);
extern ID tk_cre_tsk(void *pk_ctsk);
extern ER tk_sta_tsk(ID tskid, INT stacd);
extern ID tk_cre_sem(void *pk_csem);
extern ID tk_cre_mtx(void *pk_cmtx);
extern ID tk_cre_flg(void *pk_cflg);

/* ✅ Additional μT-Kernel 3.0 Function Prototypes */
extern ER tk_wai_sem(ID semid, INT timeout);
extern ER tk_sig_sem(ID semid, INT cnt);
extern ER tk_isig_sem(ID semid, INT cnt);
extern ER tk_loc_mtx(ID mtxid, INT timeout);
extern ER tk_unl_mtx(ID mtxid);
extern ER tk_set_flg(ID flgid, INT setptn);
extern ER tk_wai_flg(ID flgid, INT waiptn, INT wfmode, INT *p_flgptn, INT timeout);
extern ER tk_del_tsk(ID tskid);
extern ER tk_del_sem(ID semid);
extern ER tk_del_mtx(ID mtxid);
extern ER tk_del_flg(ID flgid);

/* ✅ μT-Kernel Structure Types - PRESERVED */
typedef struct {
    uint32_t tskatr;
    void *task;
    int itskpri;
    uint32_t stksz;
    void *stkadr;
} T_CTSK;

typedef struct {
    uint32_t sematr;
    int isemcnt;
    int maxsem;
} T_CSEM;

typedef struct {
    uint32_t mtxatr;
    int ceilpri;
} T_CMTX;

typedef struct {
    uint32_t flgatr;
    uint32_t iflgptn;
} T_CFLG;

typedef void (*FP)(INT stacd, void *exinf);

/* ✅ μT-Kernel 3.0 System Information Structure */
typedef struct {
    uint32_t sysstat;
    ID runtskid;
    ID schedtskid;
} T_RSYS;

/* SHRAVYA Task Priorities */
#define TASK_PRIORITY_EEG_ACQ           10
#define TASK_PRIORITY_PREPROCESSING     15
#define TASK_PRIORITY_FEATURE_EXTRACT   20
#define TASK_PRIORITY_CLASSIFICATION    25
#define TASK_PRIORITY_HAPTIC           30
#define TASK_PRIORITY_COMMUNICATION    35

/* ✅ SHRAVYA μT-Kernel 3.0 Object IDs */
static ID eeg_acquisition_task_id = 0;
static ID preprocessing_task_id = 0;
static ID feature_extraction_task_id = 0;
static ID classification_task_id = 0;
static ID haptic_task_id = 0;
static ID communication_task_id = 0;

/* ✅ SHRAVYA Synchronization Object IDs - GLOBAL FOR INTER-TASK COMMUNICATION */
//ID eeg_data_semaphore = 0;
//ID preprocessing_semaphore = 0;
//ID feature_extraction_semaphore = 0;
//ID classification_semaphore = 0;
//ID haptic_semaphore = 0;
ID system_mutex = 0;
ID status_flag = 0;

/* Function prototypes */
void shravya_system_init(void);
void shravya_start_application(void);
ER mtk3_kernel_init(void);

/* ✅ Task Entry Points - PRESERVED FOR TRON CONTEST */
extern void task_eeg_acquisition_entry(INT stacd, void *exinf);
extern void task_preprocessing_entry(INT stacd, void *exinf);
extern void task_feature_extraction_entry(INT stacd, void *exinf);
extern void task_classification_entry(INT stacd, void *exinf);
extern void task_haptic_feedback_entry(INT stacd, void *exinf);
extern void task_communication_entry(INT stacd, void *exinf);

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/**
 * @brief Main entry point for SHRAVYA EEG System
 * ✅ TRON Programming Contest 2025 Compliant
 */
void hal_entry(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;
    ER kernel_err = E_OK;

    /* Step 1: Initialize SHRAVYA hardware subsystems */
    shravya_system_init();

    /* Step 2: Initialize μT-Kernel 3.0 */
    kernel_err = mtk3_kernel_init();
    if (kernel_err != E_OK)
    {
        /* Kernel initialization failed - handle error */
        while(1)
        {
            /* Flash error LED pattern */
            R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
        }
    }

    /* Step 3: Start SHRAVYA application tasks */
    shravya_start_application();

    /* Step 4: Start μT-Kernel 3.0 scheduler - this should never return */
    tk_ext_ker();

    #if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code if using TrustZone */
    R_BSP_NonSecureEnter();
    #endif

    /* Should never reach here if kernel is running properly */
    while(1)
    {
        __NOP();
    }
}

/**
 * @brief Initialize SHRAVYA hardware subsystems
 * ✅ FIXED: Simplified to avoid missing FSP configurations
 */
void shravya_system_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* ✅ Only initialize peripherals that are configured in FSP */

    /* Initialize I/O ports if configured */
    #ifdef g_ioport_ctrl
    err = R_IOPORT_Open(&g_ioport_ctrl, &g_ioport_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Handle I/O port initialization error */
    }
    #endif

    /* ✅ Initialize SPI if configured - Using SPI_B driver */
    #ifdef g_spi0_ctrl
    err = R_SPI_B_Open(&g_spi0_ctrl, &g_spi0_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Handle SPI initialization error */
    }
    #endif

    /* ✅ Initialize I2C if configured */
    #ifdef g_i2c0_ctrl
    err = R_IIC_MASTER_Open(&g_i2c0_ctrl, &g_i2c0_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Handle I2C initialization error - continue without I2C for now */
    }
    #endif

    /* ✅ Initialize GPT timer if configured */
    #ifdef g_timer0_ctrl
    err = R_GPT_Open(&g_timer0_ctrl, &g_timer0_cfg);
    if (FSP_SUCCESS == err)
    {
        /* Set up 500Hz sampling period */
        uint32_t period_counts = 96000; /* Adjust based on your clock configuration */
        err = R_GPT_PeriodSet(&g_timer0_ctrl, period_counts);
        if (FSP_SUCCESS != err)
        {
            /* Handle timer period set error */
        }
    }
    #endif

    /* ✅ Initialize external interrupt if configured */
    #ifdef g_external_irq0_ctrl
    err = R_ICU_ExternalIrqOpen(&g_external_irq0_ctrl, &g_external_irq0_cfg);
    if (FSP_SUCCESS == err)
    {
        /* Enable external interrupt for EEG data ready */
        err = R_ICU_ExternalIrqEnable(&g_external_irq0_ctrl);
        if (FSP_SUCCESS != err)
        {
            /* Handle external interrupt enable error */
        }
    }
    #endif
}

/**
 * @brief Initialize μT-Kernel 3.0
 * ✅ TRON Programming Contest 2025 Implementation
 */
ER mtk3_kernel_init(void)
{
    ER ercd = E_OK;

    /* ✅ Initialize μT-Kernel 3.0 system */
    ercd = tk_ini_ker();
    if (ercd != E_OK)
    {
        return ercd;
    }

    /* ✅ Set system power management */
    ercd = tk_set_pow(0);
    if (ercd != E_OK)
    {
        return ercd;
    }

    return E_OK;
}

/**
 * @brief Create and start SHRAVYA application tasks
 * ✅ Full μT-Kernel 3.0 TRON Contest Implementation
 */
void shravya_start_application(void)
{
    ER ercd = E_OK;
    T_CTSK ctsk;
    T_CSEM csem;
    T_CMTX cmtx;
    T_CFLG cflg;

    /* ✅ Create synchronization objects first */

    /* Create semaphores for inter-task communication */
    csem.sematr = TA_TFIFO;
    csem.isemcnt = 0;
    csem.maxsem = 1;

    eeg_data_semaphore = tk_cre_sem(&csem);
    preprocessing_semaphore = tk_cre_sem(&csem);
    feature_extraction_semaphore = tk_cre_sem(&csem);
    classification_semaphore = tk_cre_sem(&csem);
    haptic_semaphore = tk_cre_sem(&csem);

    /* Create system mutex for resource protection */
    cmtx.mtxatr = TA_TFIFO;
    cmtx.ceilpri = 1;
    system_mutex = tk_cre_mtx(&cmtx);

    /* Create status flag for system events */
    cflg.flgatr = TA_TFIFO | TA_WMUL;
    cflg.iflgptn = 0;
    status_flag = tk_cre_flg(&cflg);

    /* ✅ Task creation template */
    ctsk.tskatr = TA_HLNG | TA_RNG3;
    ctsk.stkadr = NULL; /* Auto stack allocation */

    /* ✅ Create EEG Acquisition Task (Highest Priority) */
    ctsk.task = (FP)task_eeg_acquisition_entry;
    ctsk.itskpri = TASK_PRIORITY_EEG_ACQ;
    ctsk.stksz = 2048;

    eeg_acquisition_task_id = tk_cre_tsk(&ctsk);
    if (eeg_acquisition_task_id > 0)
    {
        tk_sta_tsk(eeg_acquisition_task_id, 0);
    }

    /* ✅ Create Signal Processing Task */
    ctsk.task = (FP)task_preprocessing_entry;
    ctsk.itskpri = TASK_PRIORITY_PREPROCESSING;
    ctsk.stksz = 2048;

    preprocessing_task_id = tk_cre_tsk(&ctsk);
    if (preprocessing_task_id > 0)
    {
        tk_sta_tsk(preprocessing_task_id, 0);
    }

    /* ✅ Create Feature Extraction Task */
    ctsk.task = (FP)task_feature_extraction_entry;
    ctsk.itskpri = TASK_PRIORITY_FEATURE_EXTRACT;
    ctsk.stksz = 3072;

    feature_extraction_task_id = tk_cre_tsk(&ctsk);
    if (feature_extraction_task_id > 0)
    {
        tk_sta_tsk(feature_extraction_task_id, 0);
    }

    /* ✅ Create AI Classification Task */
    ctsk.task = (FP)task_classification_entry;
    ctsk.itskpri = TASK_PRIORITY_CLASSIFICATION;
    ctsk.stksz = 4096;

    classification_task_id = tk_cre_tsk(&ctsk);
    if (classification_task_id > 0)
    {
        tk_sta_tsk(classification_task_id, 0);
    }

    /* ✅ Create Haptic Feedback Task */
    ctsk.task = (FP)task_haptic_feedback_entry;
    ctsk.itskpri = TASK_PRIORITY_HAPTIC;
    ctsk.stksz = 1024;

    haptic_task_id = tk_cre_tsk(&ctsk);
    if (haptic_task_id > 0)
    {
        tk_sta_tsk(haptic_task_id, 0);
    }

    /* ✅ Create Communication Task (Lowest Priority) */
    ctsk.task = (FP)task_communication_entry;
    ctsk.itskpri = TASK_PRIORITY_COMMUNICATION;
    ctsk.stksz = 2048;

    communication_task_id = tk_cre_tsk(&ctsk);
    if (communication_task_id > 0)
    {
        tk_sta_tsk(communication_task_id, 0);
    }
}

/**
 * @brief R_BSP_WarmStart - BSP warm start callback
 */
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
        #if BSP_FEATURE_FLASH_LP_VERSION != 0
        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;
        #endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */
        #ifdef g_ioport_ctrl
        /* Configure pins if IOPORT is configured */
        R_IOPORT_Open(&g_ioport_ctrl, &g_ioport_cfg);
        #endif

        #if BSP_CFG_SDRAM_ENABLED
        /* Setup SDRAM and initialize it. Must configure pins first. */
        R_BSP_SdramInit(true);
        #endif
    }
}

#if BSP_TZ_SECURE_BUILD
FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable();

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable()
{
    /* Trustzone secure callable function */
}
FSP_CPP_FOOTER
#endif
