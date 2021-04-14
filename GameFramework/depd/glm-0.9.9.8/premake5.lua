project "glm"
	kind "StaticLib"
	language "C++"

	targetdir ("dist/" .. outputdir .. "/%{prj.name}")
	objdir ("imt/" .. outputdir .. "/%{prj.name}")

	files { "include/glm/**.h", "include/glm/**.hpp", "include/glm/**.inl", "include/glm/**.cpp" }

	includedirs { "include" }

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"