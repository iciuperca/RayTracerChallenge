cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("RayTracer")

add_executable(RayTracer
    RayTracer.cpp
)

set_target_properties(RayTracer PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

target_link_libraries(RayTracer RayTracerLib)
target_include_directories(RayTracer BEFORE PUBLIC ../RayTracerLib/include)
