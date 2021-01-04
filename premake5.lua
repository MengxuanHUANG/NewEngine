workspace "NewEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "Sandbox"

--Include dirctories relative to root folder(solution dir)

IncludeDir = {}
IncludeDir["GLFW"] = "NewEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "NewEngine/vendor/Glad/include"
IncludeDir["glm"] = "NewEngine/vendor/glm"
IncludeDir["stb_image"] = "NewEngine/vendor/stb_image"

include "NewEngine/vendor/GLFW"
include "NewEngine/vendor/Glad"

project "NewEngine"
	location "NewEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "NewEngine/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/glm/glm/**.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "MY_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "MY_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "MY_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	targetdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NewEngine/src",
		"NewEngine/vendor",
		"NewEngine/vendor/spdlog/include",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS"
		}

	links
	{
		"NewEngine"
	}

	filter "configurations:Debug"
		defines "MY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MY_DIST"
		runtime "Release"
		optimize "on"