
/* This file was generated by idltool 53.23. Do not edit */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif
#ifndef LIBRARIES_XVIDCORE_H
#include <libraries/xvidcore.h>
#endif

/* forward declaration */
struct XvidCoreIFace;

extern uint32               VARARGS68K _XvidCore_Obtain(struct XvidCoreIFace *);
extern uint32               VARARGS68K _XvidCore_Release(struct XvidCoreIFace *);
extern xvid_plugin_func *   VARARGS68K _XvidCore_xvid_get_plugin_func(struct XvidCoreIFace *, int plugin);
extern int                  VARARGS68K _XvidCore_xvid_global(struct XvidCoreIFace *, void * handle, int opt, void * param1, void * param2);
extern int                  VARARGS68K _XvidCore_xvid_decore(struct XvidCoreIFace *, void * handle, int opt, void * param1, void * param2);
extern int                  VARARGS68K _XvidCore_xvid_encore(struct XvidCoreIFace *, void * handle, int opt, void * param1, void * param2);
