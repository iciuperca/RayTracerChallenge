cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("RayTracerChallenge")

#set(TARGET_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (MINGW)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
endif()

add_subdirectory(RayTracer)
add_subdirectory(RayTracerTest)
add_subdirectory(RayTracerLib)
