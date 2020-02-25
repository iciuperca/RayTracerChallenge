cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("RayTracerTest")

add_executable(RayTracerTest
    RayTracerTest.cpp
)

set_target_properties(RayTracerTest PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

target_link_libraries(RayTracerTest RayTracerLib)

target_include_directories(RayTracerTest BEFORE PUBLIC "${CMAKE_SOURCE_DIR}/RayTracerLib/include")
target_include_directories(RayTracerTest PUBLIC "${CMAKE_SOURCE_DIR}/ThirdParty/Catch2/include")
