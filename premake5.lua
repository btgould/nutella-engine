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
        "%{prj.location}/src/*.cpp",
        "%{prj.location}/include/*.hpp",
    }

    includedirs {
        "%{prj.location}/include",
        "%{prj.location}/vendor/spdlog/include"
    }

    postbuildcommands {
        "mkdir -p ../bin/" .. outputdir .. "/Sandbox",
        "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/%{cfg.buildtarget.name}"
    }

    filter "system:windows"
        -- do all windows specific stuff here
    
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
    runpathdirs "%{cfg.targetdir}"

    files {
        "%{prj.location}/src/*.cpp",
        "%{prj.location}/include/*.hpp",
    }

    includedirs {
        "%{prj.location}/include",
        "nutella/include",
        "nutella/vendor/spdlog/include"
    }

    filter "system:windows"
        -- do all windows specific stuff here
    
    filter "configurations:Debug"
        defines "NT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NT_DIST"
        optimize "On"