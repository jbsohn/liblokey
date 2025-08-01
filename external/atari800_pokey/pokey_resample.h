#ifndef MZX_72348A3C_POKEY_RESAMPLE_H_INCLUDED
#define MZX_72348A3C_POKEY_RESAMPLE_H_INCLUDED

/*****************************************************************************
 *                                                                           *
 * Module: POKEY Chip Emulator Filter package                                *
 * Author: Michael Borisov                                                   *
 * Version: 1.2                                                              *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *                 License Information and Copyright Notice                  *
 *                 ========================================                  *
 *                                                                           *
 *  POKEY Chip Emulator is Copyright(c) 2002 by Michael Borisov              *
 *                                                                           *
 *  This program is free software; you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation; either version 2 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program; if not, write to the Free Software              *
 *  Foundation, Inc., 59 Temple Place - Suite 330,                           *
 *                Boston, MA 02111-1307, USA.                                *
 *                                                                           *
 *****************************************************************************/

#include <stdbool.h>

extern double filter_44_8[];
extern double filter_44[];
extern double filter_22_8[];
extern double filter_22[];
extern double filter_11_8[];
extern double filter_11[];
extern double filter_48_8[];
extern double filter_48[];
extern double filter_8_8[];
extern double filter_8[];


int load_precomputed_filter(double* dest, int playback_freq, bool bit16);

#endif /* !defined(MZX_72348A3C_POKEY_RESAMPLE_H_INCLUDED) */
