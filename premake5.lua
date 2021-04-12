workspace "GameFramework"
	architecture "x64"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

includes = {}
includes["SDL2"] = "depd/SDL2-2.0.12/include"
includes["SDL2_image"] = "depd/SDL2_image-2.0.5/include"
includes["SDL2_mixer"] = "depd/SDL2_mixer-2.0.4/include"

project "GameFramework"
	location "GameFramework"
	kind "ConsoleApp"
	language "C++"

	targetdir ("dist/" .. outputdir .. "/%{prj.name}")
	objdir ("imt/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp",
		"%{prj.name}/example/**.h", "%{prj.name}/example/**.hpp", "%{prj.name}/example/**.cpp"
	}

	includedirs
	{ 
		"%{prj.name}/src",
		"%{prj.name}/example",
		"%{prj.name}/depd/entt/single_include",
		"depd/spdlog-1.x/include",
		"%{includes.SDL2}",
		"%{includes.SDL2_image}",
		"%{includes.SDL2_mixer}"
	}

	libdirs 
	{ 
		"depd/SDL2-2.0.12/lib/x64",
		"depd/SDL2_image-2.0.5/lib/x64",
		"depd/SDL2_mixer-2.0.4/lib/x64"
	}

	links { "SDL2.lib", "SDL2main.lib", "SDL2_image.lib", "SDL2_mixer.lib" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"