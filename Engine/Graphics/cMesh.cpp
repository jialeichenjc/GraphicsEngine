// Include Files
//==============

#include "cMesh.h"

#include <cstring>
#include <Engine/Asserts/Asserts.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <new>
#include <iostream>

// Initialization

eae6320::cResult cMesh::Load(const char* const i_path) {
	auto result = eae6320::Results::Success;

	// Create a new Lua state
	lua_State* luaState = nullptr;
	{
		luaState = luaL_newstate();
		if (!luaState)
		{
			result = eae6320::Results::OutOfMemory;
			std::cerr << "Failed to create a new Lua state" << std::endl;
			goto OnExit;
		}
	}

	// Load the asset file as a "chunk",
	// meaning there will be a callable function at the top of the stack
	{
		const auto luaResult = luaL_loadfile(luaState, i_path);
		if (luaResult != LUA_OK)
		{
			result = eae6320::Results::Failure;
			std::cerr << lua_tostring(luaState, -1) << std::endl;
			// Pop the error message
			lua_pop(luaState, 1);
			goto OnExit;
		}
	}
	// Execute the "chunk", which should load the asset
	// into a table at the top of the stack
	{
		// Right now, the chunk is at index -1
		// (that's what luaL_loadfile() does)
		constexpr int argumentCount = 0;
		constexpr int returnValueCount = 1;	// We expect an asset table to be returned
		constexpr int noErrorHandler = 0;
		const auto luaResult = lua_pcall(luaState, argumentCount, returnValueCount, noErrorHandler);
		if (luaResult == LUA_OK)
		{
			// A correct asset file _must_ return a table
			if (!lua_istable(luaState, -1))
			{
				result = eae6320::Results::InvalidFile;
				std::cerr << "Asset files must return a table (instead of a "
					<< luaL_typename(luaState, -1) << ")" << std::endl;
				// Pop the returned non-table value
				lua_pop(luaState, 1);
				goto OnExit;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << lua_tostring(luaState, -1) << std::endl;
			// Pop the error message
			lua_pop(luaState, 1);
			goto OnExit;
		}
	}

	// If this code is reached the asset file was loaded successfully,
	// and its table is now at index -1
	result = LoadMeshValues(*luaState);

	lua_pop(luaState, 1);

OnExit:

	if (luaState)
	{
		// If I haven't made any mistakes
		// there shouldn't be anything on the stack
		// regardless of any errors
		EAE6320_ASSERT(lua_gettop(luaState) == 0);

		lua_close(luaState);
		luaState = nullptr;
	}

	return result;
}