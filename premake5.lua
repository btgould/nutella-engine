require('gmake2')

local p = premake
local gmake2 = p.modules.gmake2

workspace "Nutella"
    configurations {"Debug", "Release", "Dist"}
    architecture "x86_64"

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

project "Sandbox"
    location "sandbox"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++17"
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
        "nutella/vendor/spdlog/include",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
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

premake.override(gmake2, 'projectrules', function(base, wks)
    local project = p.project

    for prj in p.workspace.eachproject(wks) do
        local deps = project.getdependencies(prj)
        deps = table.extract(deps, "name")
        _p('%s:%s', p.esc(prj.name), gmake2.list(deps))

        local cfgvar = gmake2.tovar(prj.name)
        _p('ifneq (,$(%s_config))', cfgvar)

        _p(1,'@echo "==== Building %s ($(%s_config)) ===="', prj.name, cfgvar)

        local prjpath = p.filename(prj, gmake2.getmakefilename(prj, true))
        local prjdir = path.getdirectory(path.getrelative(wks.location, prjpath))
        local prjname = path.getname(prjpath)

        -- removed `--no-print-directory` here --
        _x(1,'@${MAKE} -C %s -f %s config=$(%s_config)', prjdir, prjname, cfgvar)

        _p('endif')
        _p('')
    end
end)
