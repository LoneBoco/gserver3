workspace "gserver3"
	startproject "gserver3"

	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	symbols "On"
	targetdir ( "Build/%{_ACTION}/bin/%{cfg.buildcfg}" )
	libdirs { "Build/%{_ACTION}/bin/%{cfg.buildcfg}" }

	-- C++20 support
	-- C++latest until <ranges> is supported outside of it.
	cppdialect "C++latest"

	linkgroups "On"
	flags { "MultiProcessorCompile" }

	filter "configurations:Debug"
	 	defines { "DEBUG", "_DEBUG" }
		editandcontinue "Off"
		optimize "Off"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		flags { "LinkTimeOptimization" }

	-- Set our platform architectures.
	filter "platforms:x32"
		architecture "x32"
	filter "platforms:x64"
		architecture "x64"

	-- Toolset specific
	filter "toolset:msc*"
		defines { "_CRT_SECURE_NO_WARNINGS" }
		disablewarnings { "4005", "5050", "5104", "5105" }
		buildoptions {
			"/guard:cf",	-- Control Flow Guard
			"/Qspectre",	-- Spectre Mitigation
			"/Zc:preprocessor",	-- Use alternative preprocessor (like GCC/clang, required for BabyDI)

			-- Enables 'import std;'
			-- "/experimental:module",
			-- "/stdIfcDir \"$(VC_IFCPath)\"",
		}
	--[[
	filter "toolset:clang*"
		links { "c++experimental", "stdc++fs" }
		buildoptions { "-std=c++20", "-Wno-switch" }
	]]

	-- Windows defines.
	filter "system:windows"
		defines { "WIN32", "_WIN32", "_WINDOWS", "WIN32_LEAN_AND_MEAN", "NOMINMAX" }
	filter { "system:windows", "platforms:x64" }
		defines { "WIN64", "_WIN64" }

	-- OS defines
	filter "system:windows"
		defines { "GRAAL_WINDOWS" }
	filter "system:linux"
		defines { "GRAAL_LINUX" }
	filter "system:macosx"
		defines { "GRAAL_MACOSX" }

project "gserver3"
	kind "ConsoleApp"
	-- kind "WindowedApp"
	language "C++"
	location "projects"
	targetdir "../bin"
	debugdir "../bin"

	vectorextensions "SSE2"
	rtti "On"

	files { "../src/**" }
	includedirs { "../src" }

	-- Library includes.
	includedirs {
		"../dependencies/bzip2/",
		"../dependencies/zlib/",
		"../dependencies/BabyDI/include/",
	}

	dependson { "bzip2", "zlib" }

	-- Libraries.
	links {
		"bzip2",
		"zlib",
	}

	defines { "NOMINMAX" }

	-- Boost
	includedirs { os.getenv("BOOST_ROOT") or "../dependencies/boost/" }
	libdirs { path.join(os.getenv("BOOST_ROOT") or "../dependencies/boost/", "/stage/lib") }

	-- Debug name.
	filter "configurations:Debug"
		targetname "gserver3_d"

	-- Disable MSVC warnings because 3rd party libraries never update.
	filter "toolset:msc*"
		defines { "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING", "_SILENCE_CXX20_IS_POD_DEPRECATION_WARNING" }

	-- Enable scanning for module dependencies with MSVC.
	filter "toolset:msc*"
		scanformoduledependencies "on"

	-- Post-build commands.
	filter {}
		-- postbuildcommands { "{COPY} %{wks.location}/../doc/settings.ini %{cfg.targetdir}" }
		postbuildcommands { "{COPY} %{wks.location}/../media/ %{cfg.targetdir}"}

	-- Per-platform libraries.
	filter { "system:linux or system:macosx or system:bsd or system:solaris" }
		links { "pthread", "dl" }

	filter { "system:linux" }
		links { "X11", "GL" }

project "bzip2"
	kind "StaticLib"
	language "C"
	compileas "C"
	location "projects"
	files { "../dependencies/bzip2/**.h", "../dependencies/bzip2/**.c" }
	includedirs { "../dependencies/bzip2/" }
	removefiles {
		"../dependencies/bzip2/bzip2.c",
		"../dependencies/bzip2/bzip2recover.c",
		"../dependencies/bzip2/dlltest.c",
		"../dependencies/bzip2/mk251.c",
		"../dependencies/bzip2/spewG.c",
		"../dependencies/bzip2/unzcrash.c",
	}
	filter "toolset:msc*"
		disablewarnings { "4244", "4267", "4996" }

project "zlib"
	kind "StaticLib"
	language "C"
	compileas "C"
	location "projects"
	files { "../dependencies/zlib/*.h", "../dependencies/zlib/*.c" }
	includedirs { "../dependencies/zlib/" }
	filter "toolset:msc*"
		disablewarnings { "4244", "4267", "4996" }
