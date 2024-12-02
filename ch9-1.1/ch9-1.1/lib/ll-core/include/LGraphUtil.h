/* ============================================================================
 *  LGraphUtil.h
 * ============================================================================

 *  Author:         (C) 2003 Stefano Emiliozzi, Camil Demetrescu
 *  License:        See the end of this file for license information
 *  Created:        January 12, 2003
 *  Module:         LL

 *  Last changed:   $Date: 2005/12/13 16:45:14 $
 *  Changed by:     $Author: demetres $   
 *  Revision:       $Revision: 1.1 $    
*/

#ifndef __LGraphUtil__
#define __LGraphUtil__

/* INCLUDES */
#include "LType.h"
#include "LGraph.h"
#include "LEdgeInfo.h"
#include "LNodeInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/* COMPONENT ID */
#define LGraphUtil_ID   0x802F

/* PUBLIC FUNCTIONS */
LGraph*     LGraphUtil_RandomNM          (ui2 n, ui4 m, ui4 inSeed);
LGraph*     LGraphUtil_RandomUNM         (ui2 n, ui4 m, ui4 inSeed);
LGraph*     LGraphUtil_RandomNP          (ui2 n, f4 p, ui4 inSeed);
LGraph*     LGraphUtil_RandomUNP         (ui2 n, f4 p, ui4 inSeed);
LGraph*     LGraphUtil_Grid              (ui2 n, Bool inDirected);
LGraph*     LGraphUtil_RandomClustered   (ui2 n, ui2 inC, f4 inPc, f4 inPi, ui4 inSeed, Bool inDirected);

LEdgeInfo*  LGraphUtil_RndEdgeInfoUI4    (LGraph* inGraph, ui4 inA, ui4 inB, ui4 inSeed);
void        LGraphUtil_AddCycle          (LGraph** thruGraph);
Bool        LGraphUtil_LoadDimacs        (i1* inPathName, LGraph** outGraph, 
                                          LEdgeInfo** outEdgeInfo, Bool inDirected);
Bool        LGraphUtil_SaveDimacs        (i1* inPathName, LGraph* inGraph, 
                                          LEdgeInfo* inEdgeInfo);
Bool        LGraphUtil_LoadXML           (i1* inPathName, LGraph** outGraph, 
                                          LEdgeInfo** outEdgeInfo, Bool inDirected);
Bool        LGraphUtil_SaveXML           (i1* inPathName, LGraph* inGraph, 
                                          LEdgeInfo* inEdgeInfo);
LGraph*     LGraphUtil_PredToTree        (LGraph* inGraph, LNodeInfo* inPredArray, 
                                          LNodeInfo** outTreeToGraph, 
                                          LNodeInfo** outGraphToTree);
LGraph*     LGraphUtil_CopyGraph         (LGraph* inGraph);
LEdgeInfo*  LGraphUtil_CopyEdgeInfo      (LGraph* inGraph, LEdgeInfo* inEdgeInfo);
LGraph*     LGraphUtil_ReverseGraph      (LGraph* inGraph);
void        LGraphUtil_RemoveSelfLoops   (LGraph** thruGraph);
void        LGraphUtil_RemoveRandomNodes (ui4 inNodeNumber, LGraph* thruGraph);

#ifdef __cplusplus
}
#endif

#endif

/* Copyright (C) 2003 Stefano Emiliozzi, Camil Demetrescu

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
