workspace "Project Risk"
    architecture "x64"
    startproject "Client"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    libdirs
    {
        "%{prj.name}/lib",
    }

    includedirs
    {
        "%{prj.name}/include",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "ENGINE"
    }

    links
    {
        "glfw3_mt"
    }

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl"
    }

    filter "system:Windows"
        defines
        {"WIN",}

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "speed"

    filter "files:**.c"
        flags {"NoPCH"}


project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    staticruntime "On"

    includedirs
    {
        "Engine/src",
        "Engine/include"    
    }

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl"
    }

    links
    {
        "Engine",
    }

    filter "system:Windows"
        defines
        {"WIN",}

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "speed"