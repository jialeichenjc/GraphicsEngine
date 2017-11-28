--[[
	This file lists every asset that must be built by the AssetBuildSystem
]]
-- Environment Variables
local EngineSourceContentDir, GameSourceContentDir, GameInstallDir, OutputDir, LicenseDir, GameLicenseDir
do
	-- EngineSourceContentDir
	do
		local errorMessage
		EngineSourceContentDir, errorMessage = GetEnvironmentVariable( "EngineSourceContentDir" )
		if not EngineSourceContentDir then
			error( errorMessage )
		end
	end
	-- GameSourceContentDir
	do
		local errorMessage
		GameSourceContentDir, errorMessage = GetEnvironmentVariable( "GameSourceContentDir" )
		if not GameSourceContentDir then
			error( errorMessage )
		end
	end
	-- GameInstallDir
	do
		local errorMessage
		GameInstallDir, errorMessage = GetEnvironmentVariable( "GameInstallDir" )
		if not GameInstallDir then
			error( errorMessage )
		end
	end
	-- OutputDir
	do
		local errorMessage
		OutputDir, errorMessage = GetEnvironmentVariable( "OutputDir" )
		if not OutputDir then
			error( errorMessage )
		end
	end
	-- LicenseDir
	do
		local errorMessage
		LicenseDir, errorMessage = GetEnvironmentVariable( "LicenseDir" )
		if not LicenseDir then
			error( errorMessage )
		end
	end
	-- GameLicenseDir
	do
		local errorMessage
		GameLicenseDir, errorMessage = GetEnvironmentVariable( "GameLicenseDir" )
		if not GameLicenseDir then
			error( errorMessage )
		end
	end
end

return
{
	meshes =
	{
		"Meshes/mesh1.lua", arguments = { "meshes" } ,

		"Meshes/mesh2.lua", arguments = { "meshes" } ,
	},
	shaders =
	{
		-- EAE6320_TODO:
		-- These are some examples showing how to use the optional argument,
		-- but with my disk layout and file extension.
		-- You need to update the paths to match your content
		-- and then add the other shaders that you use.
		-- { path = "Shaders/Vertex/vertexInputLayout_mesh.shader", arguments = { "vertex" } },
		{ path = "Shaders/Vertex/commonVertex1", arguments = { "vertex" } },
		
		{ path = "Shaders/Vertex/commonVertex2", arguments = { "vertex" } },

		{ path = "Shaders/Fragment/commonFrag1", arguments = { "fragment" } },

		{ path = "Shaders/Fragment/commonFrag2", arguments = { "fragment" } },

		{ path = "Shaders/Vertex/vertexInputLayout_geometry.hlsl", arguments = { "vertex" } },

		{ path = "Shaders/Vertex/vertexInputLayout_mesh.hlsl", arguments = { "vertex" } },
	},
	textures =
	{
		-- EAE6320_TODO:
		-- These are some examples with my disk layout.
		-- You need to update the paths to match your content
		-- and then add the other textures that you use.
		"Textures/cupcake.jpg",

		"Textures/babyPanda.jpg",

		"Textures/shifu.png",
	},
}
