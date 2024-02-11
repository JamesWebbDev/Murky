workspace "Murky"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

-- Global Path
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Directories to 3rd-party based projects
IncludeDir = {}
IncludeDir["GLFW"] = "Murky/3rdParty/glfw/include"
IncludeDir["Glad"] = "Murky/3rdParty/glad/include"
IncludeDir["Stb_Image"] = "Murky/3rdParty/stb_image/include"
IncludeDir["Base64"] = "Murky/3rdParty/base64/include"
IncludeDir["ImGui"] = "Murky/3rdParty/imgui"
IncludeDir["ImGui_B"] = "Murky/3rdParty/imgui/backends"

-- Execute 3rd party premake scripts here to generate projects
include "Murky/3rdParty/glfw"
include "Murky/3rdParty/glad"
include "Murky/3rdParty/stb_image"
include "Murky/3rdParty/base64"
include "Murky/3rdParty/imgui"


project "Murky"
    location "Murky" -- localise path to 'Murky' directory

    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "mkpch.h"
    pchsource "Murky/src/mkpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",

        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Stb_Image}",
        "%{IncludeDir.Base64}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGui_B}",

        "%{prj.name}/3rdParty/spdlog/include",
        "%{prj.name}/3rdParty/glm/glm",
        "%{prj.name}/3rdParty/glm/glm/*",
        "%{prj.name}/3rdParty/imgui",
        "%{prj.name}/3rdParty/imgui/backends",

        "%{prj.name}/include/*"
    }

    -- Link engine other generated projects
    links
    {
        "opengl32.lib",
        "GLFW",
        "Glad",
        "Stb_Image",
        "Base64",
        "ImGui",
    }

    filter "system:windows"
        
        systemversion "latest"

        defines
        {
            "MK_PLATFORM_WINDOWS",
            "MK_BUILD_DLL",
            "GLFW_INCLUDE_NONE" -- thanks to glad
        }

        postbuildcommands
        {
            {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/CoolGame"}
        }

    filter "configurations:Debug"
        defines "MK_DEBUG"
        runtime "Debug"
        symbols "On" 

    filter "configurations:Release"
        defines "MK_RELEASE"
        runtime "Release"
        optimize "On" 

    filter "configurations:Dist"
        defines "MK_DIST"
        runtime "Release"
        optimize "On" 

project "CoolGame"
    location "CoolGame"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    debugdir ("bin/" .. outputdir .. "/%{prj.name}")
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Stb_Image}",
        "%{IncludeDir.Base64}",

        "Murky/3rdParty/spdlog/include",
        "Murky/3rdParty/glm/glm",
        "Murky/3rdParty/glm/glm/*",
        "Murky/3rdParty/imgui",
        "Murky/3rdParty/imgui/backends",

        "Murky/include/*",

        "Murky/src"
    }

    links
    {
        "Murky", -- links to project
        --"GLFW",
        --"Glad",
        --"Stb_Image",
        --"Base64",
        --"ImGui",
        --"opengl32.lib"
        --"OpenGL32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MK_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "MK_DEBUG"
        runtime "Debug"
        symbols "On" 

    filter "configurations:Release"
        defines "MK_RELEASE"
        runtime "Release"
        optimize "On" 

    filter "configurations:Dist"
        defines "MK_DIST"
        runtime "Release"
        optimize "On" 

        filter { "system:windows", "configurations:Release" }