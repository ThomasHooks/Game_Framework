project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("dist/" .. outputdir .. "/%{prj.name}")
	objdir ("imt/" .. outputdir .. "/%{prj.name}")

	files { "include/glad/glad.h", "src/glad.c", "include/KHR/khrplatform.h" }

	includedirs { "include" }

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"