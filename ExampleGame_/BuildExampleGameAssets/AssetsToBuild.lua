--[[
	This file lists every asset that must be built by the AssetBuildSystem
]]

return
{
	meshes =
	{
		EngineSourceContentDir .. "Meshes/mesh1.lua",

		EngineSourceContentDir .. "Meshes/mesh2.lua",
	},
	shaders =
	{
		-- EAE6320_TODO:
		-- These are some examples showing how to use the optional argument,
		-- but with my disk layout and file extension.
		-- You need to update the paths to match your content
		-- and then add the other shaders that you use.
		-- { path = "Shaders/Vertex/vertexInputLayout_mesh.shader", arguments = { "vertex" } },
		{ path = EngineSourceContentDir .. "Shaders/Vertex/commonVertex1", arguments = { "vertex" } },
		
		{ path = EngineSourceContentDir .. "Shaders/Vertex/commonVertex2", arguments = { "vertex" } },

		{ path = EngineSourceContentDir .. "Shaders/Fragment/commonFrag1", arguments = { "fragment" } },

		{ path = EngineSourceContentDir .. "Shaders/Fragment/commonFrag2", arguments = { "fragment" } },

		{ path = EngineSourceContentDir .. "Shaders/Vertex/vertexInputLayout_geometry.hlsl", argument = { "vertex" } },

		{ path = EngineSourceContentDir .. "Shaders/Vertex/Shaders/Vertex/vertexInputLayout_mesh.hlsl", argument = { "vertex" } },
	},
	textures =
	{
		-- EAE6320_TODO:
		-- These are some examples with my disk layout.
		-- You need to update the paths to match your content
		-- and then add the other textures that you use.
		EngineSourceContentDir .. "Textures/cupcake.jpg",

		EngineSourceContentDir .. "Textures/babyPanda.jpg",

		EngineSourceContentDir .. "Textures/shifu.png",
	},
}
