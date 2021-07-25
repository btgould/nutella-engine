outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

NTIncludeDir = {}
NTIncludeDir["spdlog"] = "nutella/vendor/spdlog/include"
NTIncludeDir["GLFW"] = "nutella/vendor/GLFW/include"
NTIncludeDir["Glad"] = "nutella/vendor/Glad/include"
NTIncludeDir["ImGui"] = "nutella/vendor/imgui"
NTIncludeDir["glm"] = "nutella/vendor/glm"
NTIncludeDir["stb_image"] = "nutella/vendor/stb_image"

-- include vendor premake files
include "nutella/vendor/GLFW"
include "nutella/vendor/Glad"
include "nutella/vendor/imgui"

project "Nutella"
    location "nutella"
    kind "SharedLib"

    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    pchheader "ntpch.hpp"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/vendor/stb_image/stb_image.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{NTIncludeDir.spdlog}",
        "%{NTIncludeDir.GLFW}",
        "%{NTIncludeDir.Glad}",
        "%{NTIncludeDir.ImGui}",
        "%{NTIncludeDir.glm}",
        "%{NTIncludeDir.stb_image}"
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
        defines {"NT_DEBUG", "NT_ENABLE_ASSERTS", "NT_PROFILE"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"NT_RELEASE", "NT_PROFILE"}
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "NT_DIST"
        runtime "Release"
        optimize "On"
