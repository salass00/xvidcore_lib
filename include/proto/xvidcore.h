#ifndef PROTO_XVIDCORE_H
#define PROTO_XVIDCORE_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef LIBRARIES_XVIDCORE_H
#include <libraries/xvidcore.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::Library * XvidCoreBase;
  #else
   extern struct Library * XvidCoreBase;
  #endif
 #else
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::XvidCoreBase * XvidCoreBase;
  #else
   extern struct XvidCoreBase * XvidCoreBase;
  #endif
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/xvidcore.h>
 #ifdef __USE_INLINE__
  #include <inline4/xvidcore.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_XVIDCORE_PROTOS_H
  #define CLIB_XVIDCORE_PROTOS_H 1
 #endif /* CLIB_XVIDCORE_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::XvidCoreIFace * IXvidCore;
  #else
   extern struct XvidCoreIFace * IXvidCore;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_XVIDCORE_PROTOS_H
  #include <clib/xvidcore_protos.h>
 #endif /* CLIB_XVIDCORE_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/xvidcore.h>
  #else /* __PPC__ */
   #include <ppcinline/xvidcore.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/xvidcore_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/xvidcore_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_XVIDCORE_H */
