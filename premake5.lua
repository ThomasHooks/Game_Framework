workspace "GameFramework"
	architecture "x64"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

includes = {}
includes["SDL2"] = "%{wks.location}/depd/SDL2-2.0.12/include"
includes["SDL2_image"] = "%{wks.location}/depd/SDL2_image-2.0.5/include"
includes["SDL2_mixer"] = "%{wks.location}/depd/SDL2_mixer-2.0.4/include"
includes["Glad"] = "%{wks.location}/GameFramework/depd/glad/include"
includes["glm"] = "%{wks.location}/GameFramework/depd/glm-0.9.9.8/include"
includes["stb_image"] = "%{wks.location}/GameFramework/depd/stb"
includes["spdlog"] = "%{wks.location}/depd/spdlog-1.x/include"
includes["entt"] = "%{wks.location}/GameFramework/depd/entt/single_include"

include "GameFramework/depd/glad"
include "GameFramework/depd/glm-0.9.9.8"
include "GameFramework"