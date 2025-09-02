#include "hal_data.h"

/* ✅ μT-Kernel 3.0 Type System */
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

/* ✅ μT-Kernel Structure Types */
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

/* ✅ Global ID counter for object creation */
static ID next_id = 1;

/* ✅ Stub implementations for TRON Contest demonstration */

ER tk_ini_ker(void) {
    /* Initialize kernel - stub implementation */
    return E_OK;
}

ER tk_ext_ker(void) {
    /* Exit kernel - stub implementation */
    return E_OK;
}

ER tk_dly_tsk(INT dlytim) {
    /* Task delay - use FSP delay */
    R_BSP_SoftwareDelay(dlytim, BSP_DELAY_UNITS_MILLISECONDS);
    return E_OK;
}

ID tk_cre_sem(T_CSEM *pk_csem) {
    /* Create semaphore - return unique ID */
    (void)pk_csem;
    return next_id++;
}

ID tk_cre_mtx(T_CMTX *pk_cmtx) {
    /* Create mutex - return unique ID */
    (void)pk_cmtx;
    return next_id++;
}

ID tk_cre_flg(T_CFLG *pk_cflg) {
    /* Create event flag - return unique ID */
    (void)pk_cflg;
    return next_id++;
}

ID tk_cre_tsk(T_CTSK *pk_ctsk) {
    /* Create task - return unique ID */
    (void)pk_ctsk;
    return next_id++;
}

ER tk_sta_tsk(ID tskid, INT stacd) {
    /* Start task - stub implementation */
    (void)tskid;
    (void)stacd;
    return E_OK;
}

ER tk_wai_sem(ID semid, INT timeout) {
    /* Wait semaphore - stub implementation */
    (void)semid;
    (void)timeout;
    return E_OK;
}

ER tk_sig_sem(ID semid, INT cnt) {
    /* Signal semaphore - stub implementation */
    (void)semid;
    (void)cnt;
    return E_OK;
}

ER tk_set_pow(INT powmode) {
    /* Set power mode - stub implementation */
    (void)powmode;
    return E_OK;
}

/* ✅ Standard library stubs for newlib */
int _read(int fd, char *ptr, int len) {
    (void)fd; (void)ptr; (void)len;
    return 0;
}

int _write(int fd, const char *ptr, int len) {
    (void)fd; (void)ptr; (void)len;
    return len;
}

int _close(int fd) {
    (void)fd;
    return 0;
}

int _fstat(int fd, void *st) {
    (void)fd; (void)st;
    return 0;
}

int _isatty(int fd) {
    (void)fd;
    return 1;
}

int _lseek(int fd, int ptr, int dir) {
    (void)fd; (void)ptr; (void)dir;
    return 0;
}
