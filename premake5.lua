workspace "SoulCat"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fracture"
    location "Fracture"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "frpch.h"
    pchsource "Fracture/src/frpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FR_PLATFORM_WINDOWS",
            "FR_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "FR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FR_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Fracture/vendor/spdlog/include",
        "Fracture/src"
    }

    links
    {
        "Fracture"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FR_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "FR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FR_DIST"
        optimize "On"