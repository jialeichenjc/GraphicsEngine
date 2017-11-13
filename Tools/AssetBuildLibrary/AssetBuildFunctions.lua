--[[
	This file contains the logic for building assets
]]

-- Static Data Initialization
--===========================

-- Environment Variables
local EngineSourceContentDir, GameInstallDir, GameLicenseDir, GameSourceContentDir, LicenseDir, OutputDir 
do
	-- EngineSourceContentDir
	do
		local errorMessage
		EngineSourceContentDir, errorMessage = GetEnvironmentVariable( "EngineSourceContentDir" )
		if not EngineSourceContentDir then
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
	-- GameLicenseDir
	do
		local errorMessage
		GameLicenseDir, errorMessage = GetEnvironmentVariable( "GameLicenseDir" )
		if not GameLicenseDir then
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
	-- LicenseDir
	do
		local errorMessage
		LicenseDir, errorMessage = GetEnvironmentVariable( "LicenseDir" )
		if not LicenseDir then
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
end

-- External Interface
--===================

function BuildAssets()
	local wereThereErrors = false

	-- Build the shaders and copy them to the installation location
	do
		local path_shaderBuilder = OutputDir .. "ShaderBuilder.exe"
		do
			local shader_authored = EngineSourceContentDir .. "Shaders/Vertex/commonVertex1"
			local shader_built = GameInstallDir .. "data/Shaders/Vertex/example1.shd"
			CreateDirectoryIfItDoesntExist( shader_built )
			local command = "\"" .. path_shaderBuilder .. "\""
				.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" vertex"
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. shader_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
			end
		end
		-- Build another effect
		do
			local shader_authored = EngineSourceContentDir .. "Shaders/Vertex/commonVertex2"
			local shader_built = GameInstallDir .. "data/Shaders/Vertex/example2.shd"
			CreateDirectoryIfItDoesntExist( shader_built )
			local command = "\"" .. path_shaderBuilder .. "\""
				.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" vertex"
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. shader_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
			end
		end
		do
			local shader_authored = EngineSourceContentDir .. "Shaders/Fragment/commonFrag1"
			local shader_built = GameInstallDir .. "data/Shaders/Fragment/example1.shd"
			CreateDirectoryIfItDoesntExist( shader_built )
			local command = "\"" .. path_shaderBuilder .. "\""
				.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" fragment"
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. shader_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
			end
		end
		do
			local shader_authored = EngineSourceContentDir .. "Shaders/Fragment/commonFrag2"
			local shader_built = GameInstallDir .. "data/Shaders/Fragment/example2.shd"
			CreateDirectoryIfItDoesntExist( shader_built )
			local command = "\"" .. path_shaderBuilder .. "\""
				.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" fragment"
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. shader_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
			end
		end

		if EAE6320_PLATFORM_D3D then
	
			do
				local shader_authored = EngineSourceContentDir .. "Shaders/Vertex/vertexInputLayout_geometry.hlsl"
				local shader_built = GameInstallDir .. "data/Shaders/Vertex/vertexInputLayout_geometry.shd"
				CreateDirectoryIfItDoesntExist( shader_built )
				local command = "\"" .. path_shaderBuilder .. "\""
					.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" vertex"
				local result, exitCode = ExecuteCommand( command )
				if result then
					if exitCode == 0 then
						-- Display a message for each asset
						print( "Built " .. shader_authored )
					else
						wereThereErrors = true
						-- The builder should already output a descriptive error message if there was an error
						-- (remember that you write the builder code,
						-- and so if the build process failed it means that _your_ code has returned an error code)
						-- but it can be helpful to still return an additional vague error message here
						-- in case there is a bug in the specific builder that doesn't output an error message
						OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
					end
				else
					wereThereErrors = true
					-- If the command wasn't executed then the second return value is an error message
					OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
				end
			end

			do
				local shader_authored = EngineSourceContentDir .. "Shaders/Vertex/vertexInputLayout_mesh.hlsl"
				local shader_built = GameInstallDir .. "data/Shaders/Vertex/vertexInputLayout_mesh.shd"
				CreateDirectoryIfItDoesntExist( shader_built )
				local command = "\"" .. path_shaderBuilder .. "\""
					.. " \"" .. shader_authored .. "\" \"" .. shader_built .. "\" vertex"
				local result, exitCode = ExecuteCommand( command )
				if result then
					if exitCode == 0 then
						-- Display a message for each asset
						print( "Built " .. shader_authored )
					else
						wereThereErrors = true
						-- The builder should already output a descriptive error message if there was an error
						-- (remember that you write the builder code,
						-- and so if the build process failed it means that _your_ code has returned an error code)
						-- but it can be helpful to still return an additional vague error message here
						-- in case there is a bug in the specific builder that doesn't output an error message
						OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), shader_authored )
					end
				else
					wereThereErrors = true
					-- If the command wasn't executed then the second return value is an error message
					OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), shader_authored )
				end
			end
		end
	end

	-- Build three textures
	local path_textureBuilder = OutputDir .. "TextureBuilder.exe"
		do
			local texture_authored = EngineSourceContentDir .. "Textures/shifu.jpg"
			local texture_built = GameInstallDir .. "data/Textures/shifu.jpg"
			CreateDirectoryIfItDoesntExist( texture_built )
			local command = "\"" .. path_textureBuilder .. "\""
				.. " \"" .. texture_authored .. "\" \"" .. texture_built
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. texture_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), texture_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), texture_authored )
			end
		end

		do
			local texture_authored = EngineSourceContentDir .. "Textures/babyPanda.jpg"
			local texture_built = GameInstallDir .. "data/Textures/babyPanda.jpg"
			CreateDirectoryIfItDoesntExist( texture_built )
			local command = "\"" .. path_textureBuilder .. "\""
				.. " \"" .. texture_authored .. "\" \"" .. texture_built
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. texture_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), texture_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), texture_authored )
			end
		end

		do
			local texture_authored = EngineSourceContentDir .. "Textures/cupcake.jpg"
			local texture_built = GameInstallDir .. "data/Textures/cupcake.jpg"
			CreateDirectoryIfItDoesntExist( texture_built )
			local command = "\"" .. path_textureBuilder .. "\""
				.. " \"" .. texture_authored .. "\" \"" .. texture_built
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. texture_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), texture_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), texture_authored )
			end
		end

	local path_meshBuilder = OutputDir .. "MeshBuilder.exe"
		do
			local mesh_authored = EngineSourceContentDir .. "Meshes/mesh1.lua"
			local mesh_built = GameInstallDir .. "data/Meshes/mesh1.lua"
			CreateDirectoryIfItDoesntExist( mesh_built )
			local command = "\"" .. path_meshBuilder .. "\""
				.. " \"" .. mesh_authored .. "\" \"" .. mesh_built
			local result, exitCode = ExecuteCommand( command )
			if result then
				if exitCode == 0 then
					-- Display a message for each asset
					print( "Built " .. mesh_authored )
				else
					wereThereErrors = true
					-- The builder should already output a descriptive error message if there was an error
					-- (remember that you write the builder code,
					-- and so if the build process failed it means that _your_ code has returned an error code)
					-- but it can be helpful to still return an additional vague error message here
					-- in case there is a bug in the specific builder that doesn't output an error message
					OutputErrorMessage( "The command " .. command .. " failed with exit code " .. tostring( exitCode ), mesh_authored )
				end
			else
				wereThereErrors = true
				-- If the command wasn't executed then the second return value is an error message
				OutputErrorMessage( "The command " .. command .. " couldn't be executed: " .. tostring( exitCode ), mesh_authored )
			end
		end


	-- Copy the licenses to the installation location
	do
		CreateDirectoryIfItDoesntExist( GameLicenseDir )
		local sourceLicenses = GetFilesInDirectory( LicenseDir )
		for i, sourceLicense in ipairs( sourceLicenses ) do
			local sourceFileName = sourceLicense:sub( #LicenseDir + 1 )
			local targetPath = GameLicenseDir .. sourceFileName
			local result, errorMessage = CopyFile( sourceLicense, targetPath )
			if result then
				-- Display a message
				print( "Installed " .. sourceFileName )
			else
				wereThereErrors = true
				OutputErrorMessage( "The license \"" .. sourceLicense .. "\" couldn't be copied to \"" .. targetPath .. "\": " .. errorMessage )
			end
		end
	end

	-- Copy user settings
	do
		local sourceLicenses = GetFilesInDirectory( OutputDir )
		for i, sourceLicense in ipairs( sourceLicenses ) do
			local sourceFileName = sourceLicense:sub( #OutputDir + 1 )
			if sourceFileName == "settings.ini" then 
				local targetPath = GameInstallDir .. sourceFileName
				local result, errorMessage = CopyFile( sourceLicense, targetPath )
				if result then
					-- Display a message
					print( "Installed " .. sourceFileName )
				else
					wereThereErrors = true
					OutputErrorMessage( "The user settings \"" .. sourceLicense .. "\" couldn't be copied to \"" .. targetPath .. "\": " .. errorMessage )
				end
			end
		end
	end
	return not wereThereErrors
end
