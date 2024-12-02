/* ============================================================================
 *  LRandSource.h
 * ============================================================================

 *  Author:         (c) 2001-2003 Camil Demetrescu, Stefano Emiliozzi
 *  License:        See the end of this file for license information
 *  Created:        November 29, 2001
 *  Module:         LL

 *  Last changed:   $Date: 2006/03/19 15:55:52 $
 *  Changed by:     $Author: goldberg $
 *  Revision:       $Revision: 1.2 $
*/

#ifndef __LRandSource__
#define __LRandSource__

#include "LType.h"

#ifdef __cplusplus
extern "C" {
#endif

/* COMPONENT ID */
#define LRandsource_ID  0x8008

typedef struct LRandSource LRandSource;

LRandSource* LRandSource_New        (ui4 inSeed);
void         LRandSource_Delete     (LRandSource** ThisA);
ui4          LRandSource_GetRandUI4 (LRandSource* This, ui4 inMin, ui4 inMax);
ui8          LRandSource_GetRandUI8 (LRandSource* This, ui8 inMin, ui8 inMax);
f8           LRandSource_GetRandF8  (LRandSource* This);
ui4          LRandSource_GetSeed    (LRandSource* This);

#ifdef __cplusplus
}
#endif

#endif

/* Copyright (C) 2001-2003 Camil Demetrescu, Stefano Emiliozzi

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

