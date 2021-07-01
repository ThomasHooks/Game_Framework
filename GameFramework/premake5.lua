project "GameFramework"
	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/dist/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/imt/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"src/**.h", 
		"src/**.hpp", 
		"src/**.cpp",
		"%{wks.location}/depd/stb/stb_image/stb_image.cpp",
		"%{wks.location}/depd/stb/stb_image/stb_image.h"
	}

	includedirs
	{ 
		"src",
		"%{includes.stb_image}",
		"%{includes.entt}",
		"%{includes.spdlog}",
		"%{includes.SDL2}",
		"%{includes.SDL2_image}",
		"%{includes.SDL2_mixer}",
		"%{includes.Glad}",
		"%{includes.glm}"
	}

	libdirs 
	{ 
		"%{wks.location}/depd/SDL2-2.0.12/lib/x64",
		"%{wks.location}/depd/SDL2_image-2.0.5/lib/x64",
		"%{wks.location}/depd/SDL2_mixer-2.0.4/lib/x64"
	}

	links { "SDL2.lib", "SDL2main.lib", "SDL2_image.lib", "SDL2_mixer.lib", "Glad", "opengl32.lib", "glm" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"