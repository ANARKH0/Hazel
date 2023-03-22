project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"

	}
	includedirs
	{
		"include"
	}

	filter "configurations:Debug" --only apply to Debug configurations
		defines "HZ_DEGUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release" --only apply to Debug configurations
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist" --only apply to Debug configurations
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"