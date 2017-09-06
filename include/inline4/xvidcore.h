#ifndef INLINE4_XVIDCORE_H
#define INLINE4_XVIDCORE_H

/*
** This file was auto generated by idltool 53.23.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

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
#include <interfaces/xvidcore.h>

/* Inline macros for Interface "main" */
#define xvid_get_plugin_func(plugin) IXvidCore->xvid_get_plugin_func((plugin))
#define xvid_global(handle, opt, param1, param2) IXvidCore->xvid_global((handle), (opt), (param1), (param2))
#define xvid_decore(handle, opt, param1, param2) IXvidCore->xvid_decore((handle), (opt), (param1), (param2))
#define xvid_encore(handle, opt, param1, param2) IXvidCore->xvid_encore((handle), (opt), (param1), (param2))

#endif /* INLINE4_XVIDCORE_H */