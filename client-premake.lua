outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "nutella/vendor/spdlog/include"
IncludeDir["GLFW"] = "nutella/vendor/GLFW/include"
IncludeDir["Glad"] = "nutella/vendor/Glad/include"
IncludeDir["ImGui"] = "nutella/vendor/imgui"
IncludeDir["glm"] = "nutella/vendor/glm"
IncludeDir["stb_image"] = "nutella/vendor/stb_image"

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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
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
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "NT_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "NT_DIST"
        runtime "Release"
        optimize "On"
