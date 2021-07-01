workspace "GameFramework"
	architecture "x64"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

includes = {}
includes["SDL2"] = "%{wks.location}/depd/SDL2-2.0.12/include"
includes["SDL2_image"] = "%{wks.location}/depd/SDL2_image-2.0.5/include"
includes["SDL2_mixer"] = "%{wks.location}/depd/SDL2_mixer-2.0.4/include"
includes["Glad"] = "%{wks.location}/depd/glad/include"
includes["glm"] = "%{wks.location}/depd/glm-0.9.9.8/include"
includes["stb_image"] = "%{wks.location}/depd/stb"
includes["spdlog"] = "%{wks.location}/depd/spdlog-1.x/include"
includes["entt"] = "%{wks.location}/depd/entt/single_include"
includes["ImGui"] = "%{wks.location}/depd/ImGui"
includes["GameFramework"] = "%{wks.location}/GameFramework/src"

include "depd/glad"
include "depd/glm-0.9.9.8"
include "depd/ImGui"
include "GameFramework"
include "BlockForge"