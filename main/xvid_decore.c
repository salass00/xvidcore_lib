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

#include "../xvidcore_internal.h"
#include "../xvidcore_vectors.h"

/****** xvidcore/main/xvid_decore *******************************************
*
*   NAME
*      xvid_decore -- Description
*
*   SYNOPSIS
*      int xvid_decore(void *handle, int opt, void *param1, void *param2);
*
*   FUNCTION
*
*   INPUTS
*       handle - 
*       opt - 
*       param1 - 
*       param2 - 
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

int _XvidCore_xvid_decore(struct XvidCoreIFace *Self, void *handle, int opt, void *param1, void *param2) {
	return xvid_decore(handle, opt, param1, param2);
}

