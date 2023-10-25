workspace "SoulCat"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Fracture/vendor/GLFW/include"
IncludeDir["glad"] = "Fracture/vendor/glad/include"
IncludeDir["ImGui"] = "Fracture/vendor/imgui/"
IncludeDir["glm"] = "Fracture/vendor/glm"

startproject "Sandbox"

group "Dependencies"
    include "Fracture/vendor/GLFW"
    include "Fracture/vendor/glad"
    include "Fracture/vendor/imgui"
group ""

project "Fracture"
    location "Fracture"
    kind "SharedLib"
    staticruntime "off"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "frpch.h"
    pchsource "Fracture/src/frpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "FR_PLATFORM_WINDOWS",
            "FR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

    
    filter "configurations:Debug"
        defines "FR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FR_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FR_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    staticruntime "off"
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
        "Fracture/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Fracture"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "FR_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "FR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FR_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FR_DIST"
        runtime "Release"
        optimize "On"