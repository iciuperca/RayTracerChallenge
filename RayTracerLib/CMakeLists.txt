cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("RayTracerLib")

add_library(RayTracerLib STATIC
    src/Canvas.cpp
    src/Color.cpp
    src/RayMath.cpp
    src/Tuple.cpp
    include/RayTracerLib/Canvas.h
    include/RayTracerLib/Color.h
    include/RayTracerLib/Matrix.h
    include/RayTracerLib/RayMath.h
    include/RayTracerLib/Tuple.h
)

set_target_properties(RayTracerLib PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

target_include_directories(RayTracerLib BEFORE PUBLIC include)
