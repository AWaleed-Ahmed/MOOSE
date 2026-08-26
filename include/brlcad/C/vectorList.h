/*                    V E C T O R L I S T . H
 * BRL-CAD
 *
 * Copyright (c) 2026 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file vectorList.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for VectorList reading
 */


#ifndef BRLCAD_C_VECTORLIST_INCLUDED
#define BRLCAD_C_VECTORLIST_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlHandle BrlVectorList;
typedef BrlHandle BrlVectorListElement;


enum BrlVectorListElementType {
    BrlVectorListElementTypePointDraw = 0,
    BrlVectorListElementTypePointSize,
    BrlVectorListElementTypeLineMove,
    BrlVectorListElementTypeLineDraw,
    BrlVectorListElementTypeLineWidth,
    BrlVectorListElementTypeTriangleStart,
    BrlVectorListElementTypeTriangleMove,
    BrlVectorListElementTypeTriangleDraw,
    BrlVectorListElementTypeTriangleEnd,
    BrlVectorListElementTypeTriangleVertexNormal,
    BrlVectorListElementTypePolygonStart,
    BrlVectorListElementTypePolygonMove,
    BrlVectorListElementTypePolygonDraw,
    BrlVectorListElementTypePolygonEnd,
    BrlVectorListElementTypePolygonVertexNormal,
    BrlVectorListElementTypeDisplaySpace,
    BrlVectorListElementTypeModelSpace
};


BRLCAD_MOOSE_EXPORT BrlVectorList              BrlNewVectorList(void);
BRLCAD_MOOSE_EXPORT void                       BrlVectorListClear(BrlVectorList vlist);


typedef int (*BrlVectorListCallback)(BrlVectorListElement element,
                                     void*                userdata);

BRLCAD_MOOSE_EXPORT void                       BrlVectorListIterate(BrlVectorList         vlist,
                                                                    BrlVectorListCallback callback,
                                                                    void*                 userdata);


BRLCAD_MOOSE_EXPORT enum BrlVectorListElementType BrlVectorListElementGetType(BrlVectorListElement element);


BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPointDraw(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPointSize(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListLineMove(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListLineDraw(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListLineWidth(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListTriangleStart(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListTriangleMove(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListTriangleDraw(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListTriangleEnd(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListTriangleVertexNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPolygonStart(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPolygonMove(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPolygonDraw(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPolygonEnd(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListPolygonVertexNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListDisplaySpace(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlCastToVectorListModelSpace(BrlVectorListElement element);


BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPointDrawPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT double                     BrlVectorListPointSizeSize(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListLineMovePoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListLineDrawPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT double                     BrlVectorListLineWidthWidth(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListTriangleStartNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListTriangleMovePoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListTriangleDrawPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListTriangleEndPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListTriangleVertexNormalNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPolygonStartNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPolygonMovePoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPolygonDrawPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPolygonEndPoint(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListPolygonVertexNormalNormal(BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT BrlVector3D                BrlVectorListDisplaySpaceReferencePoint(BrlVectorListElement element);

BRLCAD_MOOSE_EXPORT int                        BrlVectorListAppend(BrlVectorList        vlist,
                                                                   BrlVectorListElement element);

BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPointDraw(double x,
                                                                         double y,
                                                                         double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPointSize(double size);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListLineMove(double x,
                                                                        double y,
                                                                        double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListLineDraw(double x,
                                                                        double y,
                                                                        double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListLineWidth(double width);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListTriangleStart(double nx,
                                                                             double ny,
                                                                             double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListTriangleMove(double x,
                                                                            double y,
                                                                            double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListTriangleDraw(double x,
                                                                            double y,
                                                                            double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListTriangleEnd(double x,
                                                                           double y,
                                                                           double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListTriangleVertexNormal(double nx,
                                                                                    double ny,
                                                                                    double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPolygonStart(double nx,
                                                                            double ny,
                                                                            double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPolygonMove(double x,
                                                                           double y,
                                                                           double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPolygonDraw(double x,
                                                                           double y,
                                                                           double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPolygonEnd(double x,
                                                                          double y,
                                                                          double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListPolygonVertexNormal(double nx,
                                                                                   double ny,
                                                                                   double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListDisplaySpace(double x,
                                                                            double y,
                                                                            double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement       BrlNewVectorListModelSpace(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_VECTORLIST_INCLUDED
