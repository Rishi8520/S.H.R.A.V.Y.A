/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/02.
 *
 *----------------------------------------------------------------------
 */
/*
 *  errno.h
 *
 *  micro T-Kernel Error Code - ✅ FIXED FOR TRON CONTEST
 */
#ifndef _MTKBSP_TK_ERRNO_H_
#define _MTKBSP_TK_ERRNO_H_

/* ✅ REMOVED problematic include - define error codes directly */
// #include <mtkernel/include/tk/errno.h>

/* ✅ ESSENTIAL: Declare the errno variable for BSP compatibility */
#ifndef errno
extern int errno;  // ← ADD THIS LINE - This is what was missing!
#endif

/* ✅ μT-Kernel 3.0 Error Codes - ESSENTIAL FOR TRON CONTEST */
#ifndef E_OK
#define E_OK            (0)      /* Normal completion */
#endif
#ifndef E_SYS
#define E_SYS           (-5)     /* System error */
#endif
#ifndef E_NOMEM
#define E_NOMEM         (-10)    /* Insufficient memory */
#endif
#ifndef E_NOSPT
#define E_NOSPT         (-9)     /* Unsupported function */
#endif
#ifndef E_INOSPT
#define E_INOSPT        E_NOSPT  /* Unsupported function (in handler) */
#endif
#ifndef E_RSFN
#define E_RSFN          (-17)    /* Reserved function code number */
#endif
#ifndef E_RSATR
#define E_RSATR         (-18)    /* Reserved attribute */
#endif
#ifndef E_PAR
#define E_PAR           (-19)    /* Parameter error */
#endif
#ifndef E_ID
#define E_ID            (-20)    /* Invalid ID number */
#endif
#ifndef E_CTX
#define E_CTX           (-25)    /* Context error */
#endif
#ifndef E_MACV
#define E_MACV          (-26)    /* Inaccessible memory/access violation */
#endif
#ifndef E_OACV
#define E_OACV          (-27)    /* Object access violation */
#endif
#ifndef E_ILUSE
#define E_ILUSE         (-28)    /* Illegal service call use */
#endif
#ifndef E_NOEXS
#define E_NOEXS         (-42)    /* Object does not exist */
#endif
#ifndef E_OBJ
#define E_OBJ           (-41)    /* Invalid object state */
#endif
#ifndef E_NOACT
#define E_NOACT         (-43)    /* Non-existent activation request */
#endif
#ifndef E_QOVR
#define E_QOVR          (-43)    /* Queue overflow */
#endif
#ifndef E_RLWAI
#define E_RLWAI         (-49)    /* WAIT state was forcibly released */
#endif
#ifndef E_TMOUT
#define E_TMOUT         (-50)    /* Polling failure or timeout */
#endif
#ifndef E_DLT
#define E_DLT           (-51)    /* Waiting object was deleted */
#endif
#ifndef E_DISWAI
#define E_DISWAI        (-52)    /* Release from WAIT state was disabled */
#endif

/* ✅ Additional system error codes */
#ifndef E_IO
#define E_IO            (-EIO)   /* I/O error */
#endif
#ifndef E_LIMIT
#define E_LIMIT         (-34)    /* Limit exceeded */
#endif

/* ✅ POSIX-compatible errno values for FSP compatibility */
#ifndef EPERM
#define EPERM           1        /* Operation not permitted */
#endif
#ifndef ENOENT
#define ENOENT          2        /* No such file or directory */
#endif
#ifndef EIO
#define EIO             5        /* I/O error */
#endif
#ifndef ENOMEM
#define ENOMEM          12       /* Out of memory */
#endif
#ifndef EACCES
#define EACCES          13       /* Permission denied */
#endif
#ifndef EBUSY
#define EBUSY           16       /* Device or resource busy */
#endif
#ifndef EINVAL
#define EINVAL          22       /* Invalid argument */
#endif

#endif /* _MTKBSP_TK_ERRNO_H_ */
