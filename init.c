/*
 * An AmigaOS shared library implementation of libxvidcore.
 *
 * Copyright (C) 2009-2017 Fredrik Wikstrom <fredrik@a500.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "xvidcore_internal.h"
#include "xvidcore.library_rev.h"

static const TEXT USED verstag[] = VERSTAG;

/*
 * The system (and compiler) rely on a symbol named _start which marks
 * the beginning of execution of an ELF file. To prevent others from 
 * executing this library, and to keep the compiler/linker happy, we
 * define an empty _start symbol here.
 *
 * On the classic system (pre-AmigaOS 4.x) this was usually done by
 * moveq #0,d0
 * rts
 *
 */
int32 _start(void) {
	/* If you feel like it, open DOS and print something to the user */
	return RETURN_FAIL;
}

struct ExecIFace   *IExec;
struct NewlibIFace *INewlib;

static struct Interface *OpenInterface(CONST_STRPTR name, uint32 version) {
	struct Library *library;
	struct Interface *interface;

	library = IExec->OpenLibrary(name, version);
	if (library == NULL)
		return NULL;

	interface = IExec->GetInterface(library, "main", 1, NULL);
	if (interface == NULL) {
		IExec->CloseLibrary(library);
		return NULL;
	}

	return interface;
}

static void CloseInterface(struct Interface *interface) {
	struct Library *library;

	if (interface == NULL)
		return;

	library = interface->Data.LibBase;

	IExec->DropInterface(interface);
	IExec->CloseLibrary(library);
}

/* Open the library */
static struct XvidCoreBase *libOpen(struct LibraryManagerInterface *Self, ULONG version) {
	struct XvidCoreBase *libBase = (struct XvidCoreBase *)Self->Data.LibBase; 

	if (version > VERSION) {
		return NULL;
	}

	/* Add any specific open code here 
	   Return 0 before incrementing OpenCnt to fail opening */


	/* Add up the open count */
	libBase->libNode.lib_OpenCnt++;

	return libBase;
}

/* Close the library */
static BPTR libClose(struct LibraryManagerInterface *Self) {
	struct XvidCoreBase *libBase = (struct XvidCoreBase *)Self->Data.LibBase;

	/* Make sure to undo what open did */

	/* Make the close count */
	libBase->libNode.lib_OpenCnt--;

	return 0;
}

/* Expunge the library */
static BPTR libExpunge(struct LibraryManagerInterface *Self) {
	struct XvidCoreBase *libBase = (struct XvidCoreBase *)Self->Data.LibBase;
	BPTR result;

	/* If your library cannot be expunged, return 0 */
	if (libBase->libNode.lib_OpenCnt == 0) {
		result = libBase->segList;

		if (result != ZERO) {
			/* Undo what the init code did */
			CloseInterface((struct Interface *)INewlib);

			IExec->Remove((struct Node *)libBase);
			IExec->DeleteLibrary((struct Library *)libBase);
		}
	} else {
		result = ZERO;
		libBase->libNode.lib_Flags |= LIBF_DELEXP;
	}

	return result;
}

/* The ROMTAG Init Function */
static struct XvidCoreBase *libInit(struct XvidCoreBase *libBase, BPTR seglist, struct ExecIFace *iexec) {
	libBase->libNode.lib_Node.ln_Type = NT_LIBRARY;
	libBase->libNode.lib_Node.ln_Pri  = 0;
	libBase->libNode.lib_Node.ln_Name = (STRPTR)"xvidcore.library";
	libBase->libNode.lib_Flags        = LIBF_SUMUSED|LIBF_CHANGED;
	libBase->libNode.lib_Version      = VERSION;
	libBase->libNode.lib_Revision     = REVISION;
	libBase->libNode.lib_IdString     = (STRPTR)VSTRING;

	libBase->segList = seglist;

	IExec = iexec;

	INewlib = (struct NewlibIFace *)OpenInterface("newlib.library", 53);
	if (INewlib == NULL) {
		IExec->Alert(AG_OpenLib|AO_NewlibLib);
		IExec->DeleteLibrary((struct Library *)libBase);
		return NULL;
	}

	return libBase;
}

/* ------------------- Manager Interface ------------------------ */
/* These are generic. Replace if you need more fancy stuff */
static uint32 _manager_Obtain(struct LibraryManagerInterface *Self) {
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

static uint32 _manager_Release(struct LibraryManagerInterface *Self) {
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,-1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

/* Manager interface vectors */
static const CONST_APTR lib_manager_vectors[] = {
	_manager_Obtain,
	_manager_Release,
	NULL,
	NULL,
	libOpen,
	libClose,
	libExpunge,
	NULL,
	(APTR)-1
};

/* "__library" interface tag list */
static const struct TagItem lib_managerTags[] = {
	{ MIT_Name,        (Tag)"__library"         },
	{ MIT_VectorTable, (Tag)lib_manager_vectors },
	{ MIT_Version,     1                        },
	{ TAG_DONE,        0                        }
};

/* ------------------- Library Interface(s) ------------------------ */

#include "xvidcore_vectors.c"

/* Uncomment this line (and see below) if your library has a 68k jump table */
/* extern APTR VecTable68K[]; */

static const struct TagItem main_v1_Tags[] = {
	{ MIT_Name,        (Tag)"main"          },
	{ MIT_VectorTable, (Tag)main_v1_vectors },
	{ MIT_Version,     1                    },
	{ TAG_DONE,        0                    }
};

static const CONST_APTR libInterfaces[] = {
	lib_managerTags,
	main_v1_Tags,
	NULL
};

static CONST struct TagItem libCreateTags[] = {
	{ CLT_DataSize,   sizeof(struct XvidCoreBase) },
	{ CLT_InitFunc,   (Tag)libInit                },
	{ CLT_Interfaces, (Tag)libInterfaces          },
	/* Uncomment the following line if you have a 68k jump table */
	/* { CLT_Vector68K,  (Tag)VecTable68K            }, */
	{ TAG_DONE,       0                           }
};


/* ------------------- ROM Tag ------------------------ */
static const struct Resident lib_res USED = {
	RTC_MATCHWORD,
	(struct Resident *)&lib_res,
	(APTR)(&lib_res + 1),
	RTF_NATIVE|RTF_AUTOINIT, /* Add RTF_COLDSTART if you want to be resident */
	VERSION,
	NT_LIBRARY, /* Make this NT_DEVICE if needed */
	0, /* PRI, usually not needed unless you're resident */
	"xvidcore.library",
	VSTRING,
	(APTR)libCreateTags
};

