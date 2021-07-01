project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("dist/" .. outputdir .. "/%{prj.name}")
	objdir ("imt/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"imconfig.h",
		"imgui.cpp",
		"imgui.h",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h"
	}

	includedirs { "include" }

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		cppdialect "C++17"