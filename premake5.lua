workspace "Nutella"
    configurations {"Debug", "Release", "Dist"}
    architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Nutella"
    location "nutella"
    kind "SharedLib"

    language "C++"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
    }

    includedirs {
        "%{prj.location}/vendor/spdlog/include"
    }

    postbuildcommands {
        "mkdir -p ../bin/" .. outputdir .. "/Sandbox",
        "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/%{cfg.buildtarget.name}"
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

project "Sandbox"
    location "sandbox"
    kind "ConsoleApp"

    language "C++"

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
