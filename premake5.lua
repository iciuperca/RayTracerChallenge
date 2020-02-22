workspace "RayTracerChallange"
    configurations { "Debug", "Release" }
    platforms {"x64"}
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    location ("build/" .. _ACTION)

filter "action:vs*"
    toolset "msc-ClangCL"

filter "platforms:x64"
    architecture "x64"

filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
    optimize "Off"

filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "Full"

project "RayTracer"
    kind "ConsoleApp"
    files { "RayTracer/**.h", "RayTracer/**.cpp" }
    links { "RayTracerLib" }
    includedirs { "RayTracerLib/include" }

project "RayTracerTest"
    kind "ConsoleApp"
    files { "RayTracerTest/**.h", "RayTracerTest/**.cpp" }
    links { "RayTracerLib" }
    includedirs { "RayTracerLib/include", "ThirdParty/Catch2/include" }

project "RayTracerLib"
    kind "StaticLib"
    files { "RayTracerLib/include/RayTracerLib/**.h", "RayTracerLib/src/**.cpp" }
    includedirs { "RayTracerLib/include" }
