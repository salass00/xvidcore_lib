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

#ifndef LIBRARIES_XVIDCORE_H
#define LIBRARIES_XVIDCORE_H

#include <xvid.h>

struct XvidCoreBase {
	struct Library LibNode;

	xvid_plugin_func *xvid_plugin_single;
	xvid_plugin_func *xvid_plugin_2pass1;
	xvid_plugin_func *xvid_plugin_2pass2;
	xvid_plugin_func *xvid_plugin_lumimasking;
	xvid_plugin_func *xvid_plugin_psnr;
	xvid_plugin_func *xvid_plugin_dump;
	xvid_plugin_func *xvid_plugin_ssim;
	xvid_plugin_func *xvid_plugin_psnrhvsm;
};

/* For xvid_get_plugin_func() */
enum {
	XVID_PLUGIN_SINGLE = 0,
	XVID_PLUGIN_2PASS1,
	XVID_PLUGIN_2PASS2,
	XVID_PLUGIN_LUMIMASKING,
	XVID_PLUGIN_PSNR,
	XVID_PLUGIN_DUMP,
	XVID_PLUGIN_SSIM,
	XVID_PLUGIN_PSNRHVSM
};

#endif /* LIBRARIES_XVIDCORE_H */

