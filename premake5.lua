workspace "Nutella"
    configurations {"Debug", "Release", "Dist"}
    architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "nutella/vendor/GLFW/include"
IncludeDir["Glad"] = "nutella/vendor/Glad/include"
IncludeDir["ImGui"] = "nutella/vendor/imgui"

-- include vendor premake files
include "nutella/vendor/GLFW"
include "nutella/vendor/Glad"
include "nutella/vendor/imgui"

project "Nutella"
    location "nutella"
    kind "SharedLib"

    language "C++"
    staticruntime "Off"

    pchheader "ntpch.hpp"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
    }

    includedirs {
        "%{prj.location}/src",
        "%{prj.location}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links {
        "GLFW", "GL", "dl",
        "Glad",
        "ImGui"
    }

    linkoptions { 
        "-pthread"
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    postbuildcommands {
        "mkdir -p ../bin/" .. outputdir .. "/Sandbox",
        "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/%{cfg.buildtarget.name}"
    }
    
    filter "configurations:Debug"
        defines {"NT_DEBUG", "NT_ENABLE_ASSERTS"}
        symbols "On"

    filter "configurations:Release"
        defines "NT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NT_DIST"
        optimize "On"

project "Sandbox"
    location "sandbox"
    kind "ConsoleApp"

    language "C++"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    links "Nutella"
    runpathdirs "%{cfg.targetdir}" -- adds relatively (i.e. this is $ORIGIN)

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
    }

    includedirs {
        "nutella/src",
        "nutella/src/**",
        "nutella/vendor/spdlog/include"
    }
    
    filter "configurations:Debug"
        defines "NT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NT_DIST"
        optimize "On"
