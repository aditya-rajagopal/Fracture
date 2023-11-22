workspace "SoulCat"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
	{
		"MultiProcessorCompile"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Fracture/vendor/GLFW/include"
IncludeDir["glad"] = "Fracture/vendor/glad/include"
IncludeDir["ImGui"] = "Fracture/vendor/imgui/"
IncludeDir["glm"] = "Fracture/vendor/glm"
IncludeDir["stb_image"] = "Fracture/vendor/stb_image"

startproject "Sandbox"

group "Dependencies"
    include "Fracture/vendor/GLFW"
    include "Fracture/vendor/glad"
    include "Fracture/vendor/imgui"
group ""

project "Fracture"
    location "Fracture"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FR_PLATFORM_WINDOWS",
            "FR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "FR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "FR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FR_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Fracture/vendor",
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
        symbols "on"

    filter "configurations:Release"
        defines "FR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FR_DIST"
        runtime "Release"
        optimize "on"