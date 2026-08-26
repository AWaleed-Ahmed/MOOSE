import sys
import os
import ctypes

# Add the parent directory to the path so we can load the _bindings module to get the raw library
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from brlcad._bindings import _lib, c_void_p

def test_vectorlist_casts():
    print("Testing VectorList explicit C-API casts...")
    
    # 1. Create a VectorList
    vlist = _lib.BrlNewVectorList()
    
    # 2. Create one of every element type
    elements = {
        "DisplaySpace": _lib.BrlNewVectorListDisplaySpace(10.0, 20.0, 30.0),
        "LineDraw": _lib.BrlNewVectorListLineDraw(1.0, 1.0, 1.0),
        "LineMove": _lib.BrlNewVectorListLineMove(2.0, 2.0, 2.0),
        "LineWidth": _lib.BrlNewVectorListLineWidth(2.5),
        "ModelSpace": _lib.BrlNewVectorListModelSpace(),
        "PointDraw": _lib.BrlNewVectorListPointDraw(3.0, 3.0, 3.0),
        "PointSize": _lib.BrlNewVectorListPointSize(5.0),
        "PolygonDraw": _lib.BrlNewVectorListPolygonDraw(4.0, 4.0, 4.0),
        "PolygonEnd": _lib.BrlNewVectorListPolygonEnd(5.0, 5.0, 5.0),
        "PolygonMove": _lib.BrlNewVectorListPolygonMove(6.0, 6.0, 6.0),
        "PolygonStart": _lib.BrlNewVectorListPolygonStart(0.0, 0.0, 1.0),
        "PolygonVertexNormal": _lib.BrlNewVectorListPolygonVertexNormal(0.0, 1.0, 0.0),
        "TriangleDraw": _lib.BrlNewVectorListTriangleDraw(7.0, 7.0, 7.0),
        "TriangleEnd": _lib.BrlNewVectorListTriangleEnd(8.0, 8.0, 8.0),
        "TriangleMove": _lib.BrlNewVectorListTriangleMove(9.0, 9.0, 9.0),
        "TriangleStart": _lib.BrlNewVectorListTriangleStart(1.0, 0.0, 0.0),
        "TriangleVertexNormal": _lib.BrlNewVectorListTriangleVertexNormal(0.0, 0.0, 1.0),
    }
    
    # 3. Test explicit downcasting for each one
    # Note: Because the C-API returns a BrlVectorListElement (BrlHandle), 
    # we just need to ensure the cast functions don't segfault and return a valid handle.
    
    # We must explicitly set argtypes and restype for these raw C functions since they 
    # aren't mapped in our _bindings.py abstraction!
    for name, obj in elements.items():
        cast_func_name = f"BrlCastToVectorList{name}"
        cast_func = getattr(_lib, cast_func_name)
        cast_func.argtypes = [c_void_p]
        cast_func.restype = c_void_p
        
        print(f"Testing {cast_func_name}...")
        casted = cast_func(obj)
        assert casted, f"Downcast failed for {name} (returned NULL/None/0)"
        
        # Verify it returns NULL when given a DIFFERENT type of element!
        # Pick another element at random
        other_name = "ModelSpace" if name != "ModelSpace" else "DisplaySpace"
        other_obj = elements[other_name]
        
        wrong_cast = cast_func(other_obj)
        assert not wrong_cast, f"Downcast should have returned NULL/None when given {other_name}, but didn't!"

    print("All C-API explicit cast functions passed!")

if __name__ == "__main__":
    test_vectorlist_casts()
