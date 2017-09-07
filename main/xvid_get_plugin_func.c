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

/****** xvidcore/main/xvid_get_plugin_func **********************************
*
*   NAME
*      xvid_get_plugin_func -- Description
*
*   SYNOPSIS
*      xvid_plugin_func *xvid_get_plugin_func(int plugin);
*
*   FUNCTION
*
*   INPUTS
*       plugin - 
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

static xvid_plugin_func * const xvid_plugins[] = {
	xvid_plugin_single,
	xvid_plugin_2pass1,
	xvid_plugin_2pass2,
	xvid_plugin_lumimasking,
	xvid_plugin_psnr,
	xvid_plugin_dump,
	xvid_plugin_ssim,
	xvid_plugin_psnrhvsm
};

xvid_plugin_func *_XvidCore_xvid_get_plugin_func(struct XvidCoreIFace *Self, int plugin) {
	if (plugin >= XVID_PLUGIN_SINGLE && plugin <= XVID_PLUGIN_PSNRHVSM)
		return xvid_plugins[plugin];
	else
		return NULL;
}

