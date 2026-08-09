/*                      V E C T O R L I S T . C P P
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
/** @file vectorList.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implementation for VectorList opaque wrapper
 */

#include <cassert>
#include <functional>

#include <brlcad/VectorList.h>

#include <brlcad/C/vectorList.h>

#include "casts.h"


using namespace BRLCAD;


namespace {


VectorList::Element* ElementOrNull
(
    BrlVectorListElement element
) {
    VectorList::Element* ret = nullptr;

    if (element != nullptr) {
        ret = CastVectorListElement(element);
        assert(ret != nullptr);
    }

    return ret;
}


BrlVectorListElement CastIfType
(
    BrlVectorListElement           element,
    VectorList::Element::ElementType type
) {
    BrlVectorListElement ret = nullptr;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == type)
        ret = element;

    return ret;
}


BrlVector3D PointIfType
(
    BrlVectorListElement           element,
    VectorList::Element::ElementType type
) {
    BrlVector3D          ret = nullptr;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == type) {
        switch (type) {
            case VectorList::Element::ElementType::PointDraw:
                ret = new Vector3DData(static_cast<VectorList::PointDraw*>(el)->Point());
                break;
            case VectorList::Element::ElementType::LineMove:
                ret = new Vector3DData(static_cast<VectorList::LineMove*>(el)->Point());
                break;
            case VectorList::Element::ElementType::LineDraw:
                ret = new Vector3DData(static_cast<VectorList::LineDraw*>(el)->Point());
                break;
            case VectorList::Element::ElementType::TriangleMove:
                ret = new Vector3DData(static_cast<VectorList::TriangleMove*>(el)->Point());
                break;
            case VectorList::Element::ElementType::TriangleDraw:
                ret = new Vector3DData(static_cast<VectorList::TriangleDraw*>(el)->Point());
                break;
            case VectorList::Element::ElementType::TriangleEnd:
                ret = new Vector3DData(static_cast<VectorList::TriangleEnd*>(el)->Point());
                break;
            case VectorList::Element::ElementType::PolygonMove:
                ret = new Vector3DData(static_cast<VectorList::PolygonMove*>(el)->Point());
                break;
            case VectorList::Element::ElementType::PolygonDraw:
                ret = new Vector3DData(static_cast<VectorList::PolygonDraw*>(el)->Point());
                break;
            case VectorList::Element::ElementType::PolygonEnd:
                ret = new Vector3DData(static_cast<VectorList::PolygonEnd*>(el)->Point());
                break;
            default:
                break;
        }
    }

    return ret;
}


BrlVector3D NormalIfType
(
    BrlVectorListElement           element,
    VectorList::Element::ElementType type
) {
    BrlVector3D          ret = nullptr;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == type) {
        switch (type) {
            case VectorList::Element::ElementType::TriangleStart:
                ret = new Vector3DData(static_cast<VectorList::TriangleStart*>(el)->Normal());
                break;
            case VectorList::Element::ElementType::TriangleVertexNormal:
                ret = new Vector3DData(static_cast<VectorList::TriangleVertexNormal*>(el)->Normal());
                break;
            case VectorList::Element::ElementType::PolygonStart:
                ret = new Vector3DData(static_cast<VectorList::PolygonStart*>(el)->Normal());
                break;
            case VectorList::Element::ElementType::PolygonVertexNormal:
                ret = new Vector3DData(static_cast<VectorList::PolygonVertexNormal*>(el)->Normal());
                break;
            default:
                break;
        }
    }

    return ret;
}


}


BrlVectorList BrlNewVectorList(void) {
    return new VectorListData(new VectorList());
}


void BrlVectorListClear
(
    BrlVectorList vlist
) {
    if (vlist != nullptr) {
        VectorList* vl = CastVectorList(vlist);

        assert(vl != nullptr);

        if (vl != nullptr)
            vl->Clear();
    }
}


void BrlVectorListIterate
(
    BrlVectorList         vlist,
    BrlVectorListCallback callback,
    void*                 userdata
) {
    if (vlist != nullptr && callback != nullptr) {
        VectorList* vl = CastVectorList(vlist);

        assert(vl != nullptr);

        if (vl != nullptr) {
            vl->Iterate([callback, userdata](const VectorList::Element* element) -> bool {
                if (element == nullptr)
                    return true;

                BrlVectorListElement handle = new VectorListElementData(
                    const_cast<VectorList::Element*>(element), false);
                int cont = callback(handle, userdata);

                delete static_cast<VectorListElementData*>(handle);

                return cont != 0;
            });
        }
    }
}


BrlVectorListElementType BrlVectorListElementGetType
(
    BrlVectorListElement element
) {
    BrlVectorListElementType ret = BrlVectorListElementTypePointDraw;
    VectorList::Element*     el  = ElementOrNull(element);

    if (el != nullptr)
        ret = static_cast<BrlVectorListElementType>(el->Type());

    return ret;
}


BrlVectorListElement BrlCastToVectorListPointDraw(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PointDraw);
}

BrlVectorListElement BrlCastToVectorListPointSize(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PointSize);
}

BrlVectorListElement BrlCastToVectorListLineMove(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::LineMove);
}

BrlVectorListElement BrlCastToVectorListLineDraw(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::LineDraw);
}

BrlVectorListElement BrlCastToVectorListLineWidth(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::LineWidth);
}

BrlVectorListElement BrlCastToVectorListTriangleStart(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::TriangleStart);
}

BrlVectorListElement BrlCastToVectorListTriangleMove(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::TriangleMove);
}

BrlVectorListElement BrlCastToVectorListTriangleDraw(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::TriangleDraw);
}

BrlVectorListElement BrlCastToVectorListTriangleEnd(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::TriangleEnd);
}

BrlVectorListElement BrlCastToVectorListTriangleVertexNormal(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::TriangleVertexNormal);
}

BrlVectorListElement BrlCastToVectorListPolygonStart(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PolygonStart);
}

BrlVectorListElement BrlCastToVectorListPolygonMove(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PolygonMove);
}

BrlVectorListElement BrlCastToVectorListPolygonDraw(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PolygonDraw);
}

BrlVectorListElement BrlCastToVectorListPolygonEnd(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PolygonEnd);
}

BrlVectorListElement BrlCastToVectorListPolygonVertexNormal(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::PolygonVertexNormal);
}

BrlVectorListElement BrlCastToVectorListDisplaySpace(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::DisplaySpace);
}

BrlVectorListElement BrlCastToVectorListModelSpace(BrlVectorListElement element) {
    return CastIfType(element, VectorList::Element::ElementType::ModelSpace);
}


BrlVector3D BrlVectorListPointDrawPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::PointDraw);
}


double BrlVectorListPointSizeSize(BrlVectorListElement element) {
    double               ret = 0.;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == VectorList::Element::ElementType::PointSize)
        ret = static_cast<VectorList::PointSize*>(el)->Size();

    return ret;
}


BrlVector3D BrlVectorListLineMovePoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::LineMove);
}


BrlVector3D BrlVectorListLineDrawPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::LineDraw);
}


double BrlVectorListLineWidthWidth(BrlVectorListElement element) {
    double               ret = 0.;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == VectorList::Element::ElementType::LineWidth)
        ret = static_cast<VectorList::LineWidth*>(el)->Width();

    return ret;
}


BrlVector3D BrlVectorListTriangleStartNormal(BrlVectorListElement element) {
    return NormalIfType(element, VectorList::Element::ElementType::TriangleStart);
}


BrlVector3D BrlVectorListTriangleMovePoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::TriangleMove);
}


BrlVector3D BrlVectorListTriangleDrawPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::TriangleDraw);
}


BrlVector3D BrlVectorListTriangleEndPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::TriangleEnd);
}


BrlVector3D BrlVectorListTriangleVertexNormalNormal(BrlVectorListElement element) {
    return NormalIfType(element, VectorList::Element::ElementType::TriangleVertexNormal);
}


BrlVector3D BrlVectorListPolygonStartNormal(BrlVectorListElement element) {
    return NormalIfType(element, VectorList::Element::ElementType::PolygonStart);
}


BrlVector3D BrlVectorListPolygonMovePoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::PolygonMove);
}


BrlVector3D BrlVectorListPolygonDrawPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::PolygonDraw);
}


BrlVector3D BrlVectorListPolygonEndPoint(BrlVectorListElement element) {
    return PointIfType(element, VectorList::Element::ElementType::PolygonEnd);
}


BrlVector3D BrlVectorListPolygonVertexNormalNormal(BrlVectorListElement element) {
    return NormalIfType(element, VectorList::Element::ElementType::PolygonVertexNormal);
}


BrlVector3D BrlVectorListDisplaySpaceReferencePoint(BrlVectorListElement element) {
    BrlVector3D          ret = nullptr;
    VectorList::Element* el  = ElementOrNull(element);

    if (el != nullptr && el->Type() == VectorList::Element::ElementType::DisplaySpace)
        ret = new Vector3DData(static_cast<VectorList::DisplaySpace*>(el)->ReferencePoint());

    return ret;
}


int BrlVectorListAppend
(
    BrlVectorList        vlist,
    BrlVectorListElement element
) {
    int ret = 0;

    if (vlist != nullptr && element != nullptr) {
        VectorList*          vl = CastVectorList(vlist);
        VectorList::Element* el = CastVectorListElement(element);

        assert(vl != nullptr && el != nullptr);

        if (vl != nullptr && el != nullptr)
            ret = vl->Append(*el) ? 1 : 0;
    }

    return ret;
}


BrlVectorListElement BrlNewVectorListPointDraw
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::PointDraw(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListPointSize
(
    double size
) {
    return new VectorListElementData(new VectorList::PointSize(size));
}


BrlVectorListElement BrlNewVectorListLineMove
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::LineMove(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListLineDraw
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::LineDraw(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListLineWidth
(
    double width
) {
    return new VectorListElementData(new VectorList::LineWidth(width));
}


BrlVectorListElement BrlNewVectorListTriangleStart
(
    double nx,
    double ny,
    double nz
) {
    return new VectorListElementData(new VectorList::TriangleStart(Vector3D(nx, ny, nz)));
}


BrlVectorListElement BrlNewVectorListTriangleMove
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::TriangleMove(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListTriangleDraw
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::TriangleDraw(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListTriangleEnd
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::TriangleEnd(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListTriangleVertexNormal
(
    double nx,
    double ny,
    double nz
) {
    return new VectorListElementData(new VectorList::TriangleVertexNormal(Vector3D(nx, ny, nz)));
}


BrlVectorListElement BrlNewVectorListPolygonStart
(
    double nx,
    double ny,
    double nz
) {
    return new VectorListElementData(new VectorList::PolygonStart(Vector3D(nx, ny, nz)));
}


BrlVectorListElement BrlNewVectorListPolygonMove
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::PolygonMove(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListPolygonDraw
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::PolygonDraw(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListPolygonEnd
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::PolygonEnd(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListPolygonVertexNormal
(
    double nx,
    double ny,
    double nz
) {
    return new VectorListElementData(new VectorList::PolygonVertexNormal(Vector3D(nx, ny, nz)));
}


BrlVectorListElement BrlNewVectorListDisplaySpace
(
    double x,
    double y,
    double z
) {
    return new VectorListElementData(new VectorList::DisplaySpace(Vector3D(x, y, z)));
}


BrlVectorListElement BrlNewVectorListModelSpace(void) {
    return new VectorListElementData(new VectorList::ModelSpace());
}
