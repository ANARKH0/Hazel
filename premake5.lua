workspace "Hazel"
	architecture "x64"
 
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
 
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" --Debug-Windows-x64
-- Include diretories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include" 
include "Hazel/vendor/GLFW"		--include Hazel/vendor/GLFW/premake5.lua

project "Hazel"
	location "Hazel"
	kind "SharedLib" --dll
	language "C++"
 
	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"
 
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On" --linking the runtime library
		systemversion "latest"
 
		defines
		{
			"HZ_BUILD_DLL",
			"HZ_PLATFORM_WINDOWS",
		}
 
		--create a postbuild step to put the .dll where we want to be
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputDir.. "/Sandbox")
		}
 
		filter "configurations:Debug" --only apply to Debug configurations
			defines "HZ_DEGUG"
			symbols "On"
 
		filter "configurations:Release" --only apply to Debug configurations
			defines "HZ_RELEASE"
			optimize "On"
		
		filter "configurations:Dist" --only apply to Debug configurations
			defines "HZ_DIST"
			optimize "On"

		filter "system:windows"
			buildoptions "/MT"
			
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" --.exe
	language "C++"
 
	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")
 
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
 
	}
 
	links{
		"Hazel"
	}
 
 
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On" --linking the runtime library
		systemversion "latest"
 
		defines
		{
			"HZ_PLATFORM_WINDOWS",
		}
 
		filter "configurations:Debug" --only apply to Debug configurations
			defines "HZ_DEGUG"
			symbols "On"
 
		filter "configurations:Release" --only apply to Debug configurations
			defines "HZ_RELEASE"
			optimize "On"
		
		filter "configurations:Dist" --only apply to Debug configurations
			defines "HZ_DIST"
			optimize "On"

		filter "system:windows"
        	buildoptions "/MT"