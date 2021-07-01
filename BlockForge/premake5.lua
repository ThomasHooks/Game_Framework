project "BlockForge"
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/dist/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/imt/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"src/**.h", 
		"src/**.hpp", 
		"src/**.cpp"
	}

	includedirs
	{ 
		"src",
		"%{includes.spdlog}",
		"%{includes.SDL2}",
		"%{includes.SDL2_mixer}",
		"%{includes.glm}",
		"%{includes.entt}",
		"%{includes.ImGui}",
		"%{includes.GameFramework}"
	}

	libdirs 
	{ 
		"%{wks.location}/depd/SDL2-2.0.12/lib/x64",
		"%{wks.location}/depd/SDL2_mixer-2.0.4/lib/x64"
	}

	links { "SDL2.lib", "SDL2main.lib", "SDL2_mixer.lib", "GameFramework", "glm", "ImGui" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"