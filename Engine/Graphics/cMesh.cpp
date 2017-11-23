// Include Files
//==============

#include "cMesh.h"

#include <cstring>
#include <Engine/Asserts/Asserts.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <new>
#include <iostream>

// Static Data Initialization
//===========================

eae6320::Assets::cManager<cMesh> cMesh::s_manager;

eae6320::cResult cMesh::Load(const char* const i_path, cMesh*& o_mesh) {
	std::vector<eae6320::Graphics::VertexFormats::sMesh> i_meshVec;
	std::vector<uint16_t> i_indexVec;

	auto result = CreateMesh(o_mesh, i_path, i_meshVec, i_indexVec);

	return result;
}

eae6320::cResult cMesh::CreateMesh(cMesh *& mesh, const char* const i_path, 
	std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
	std::vector<uint16_t> & i_indexVec) {

	////auto result = LoadMesh(i_path, i_meshVec, i_indexVec);

	//result = CreateMesh(mesh, i_meshVec, i_indexVec);
	auto result = eae6320::Results::Success;

	mesh = new cMesh();

	eae6320::Platform::sDataFromFile dataFromFile;
	std::string errorMessage;
	if (result = eae6320::Platform::LoadBinaryFile(i_path, dataFromFile, &errorMessage)) {
		uintptr_t ptr = reinterpret_cast<uintptr_t>(dataFromFile.data);
		mesh->m_vertexCount = *reinterpret_cast<size_t*>(ptr);

		ptr += sizeof(size_t);

		mesh->m_vertex = reinterpret_cast<eae6320::Graphics::VertexFormats::sMesh*>(ptr);
		
		ptr += sizeof(eae6320::Graphics::VertexFormats::sMesh) * (mesh->m_vertexCount);

		mesh->m_indexCount = *reinterpret_cast<size_t*>(ptr);

		ptr += sizeof(size_t);

		mesh->m_index = reinterpret_cast<uint16_t*>(ptr);

		for (size_t i = 0; i < mesh->m_indexCount; i++) 
		{
			uint16_t index = *reinterpret_cast<uint16_t*>(ptr);

			ptr += sizeof(uint16_t);
		}
	}

	result = mesh->Initialize(mesh->m_vertex,mesh->m_index);
	if (result) {
		goto OnExit;
	}
	else {
		EAE6320_ASSERT(false);
	}
OnExit:

	return result;
}
//
//// Initialization
//
//eae6320::cResult cMesh::LoadMesh(const char* const i_path, std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
//	std::vector<uint16_t> & i_indexVec) {
//	auto result = eae6320::Results::Success;
//
//	// Create a new Lua state
//	lua_State* luaState = nullptr;
//	{
//		luaState = luaL_newstate();
//		if (!luaState)
//		{
//			result = eae6320::Results::OutOfMemory;
//			std::cerr << "Failed to create a new Lua state" << std::endl;
//			goto OnExit;
//		}
//	}
//
//	// Load the asset file as a "chunk",
//	// meaning there will be a callable function at the top of the stack
//	{
//		const auto luaResult = luaL_loadfile(luaState, i_path);
//		if (luaResult != LUA_OK)
//		{
//			result = eae6320::Results::Failure;
//			std::cerr << lua_tostring(luaState, -1) << std::endl;
//			// Pop the error message
//			lua_pop(luaState, 1);
//			goto OnExit;
//		}
//	}
//	// Execute the "chunk", which should load the asset
//	// into a table at the top of the stack
//	{
//		// Right now, the chunk is at index -1
//		// (that's what luaL_loadfile() does)
//		constexpr int argumentCount = 0;
//		constexpr int returnValueCount = 1;	// We expect an asset table to be returned
//		constexpr int noErrorHandler = 0;
//		const auto luaResult = lua_pcall(luaState, argumentCount, returnValueCount, noErrorHandler);
//		if (luaResult == LUA_OK)
//		{
//			// A correct asset file _must_ return a table
//			if (!lua_istable(luaState, -1))
//			{
//				result = eae6320::Results::InvalidFile;
//				std::cerr << "Asset files must return a table (instead of a "
//					<< luaL_typename(luaState, -1) << ")" << std::endl;
//				// Pop the returned non-table value
//				lua_pop(luaState, 1);
//				goto OnExit;
//			}
//		}
//		else
//		{
//			result = eae6320::Results::InvalidFile;
//			std::cerr << lua_tostring(luaState, -1) << std::endl;
//			// Pop the error message
//			lua_pop(luaState, 1);
//			goto OnExit;
//		}
//	}
//
//	// If this code is reached the asset file was loaded successfully,
//	// and its table is now at index -1
//	result = LoadMeshValues(*luaState, i_meshVec, i_indexVec);
//
//	lua_pop(luaState, 1);
//
//OnExit:
//
//	if (luaState)
//	{
//		// If I haven't made any mistakes
//		// there shouldn't be anything on the stack
//		// regardless of any errors
//		EAE6320_ASSERT(lua_gettop(luaState) == 0);
//
//		lua_close(luaState);
//		luaState = nullptr;
//	}
//
//	return result;
//}

//// load mesh values
//// lua table should be -1 now
//eae6320::cResult cMesh::LoadMeshValues(lua_State& io_luaState, 
//	std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
//	std::vector<uint16_t> & i_indexVec) {
//	auto result = eae6320::Results::Success;
//
//	// table would be at index -2 after this
//	constexpr auto* const key = "numVertex";
//	lua_pushstring(&io_luaState, key);
//	lua_gettable(&io_luaState, -2);
//
//
//	auto test = lua_tointeger(&io_luaState, -1);
//
// 	if (lua_isnil(&io_luaState, -1))
//	{
//		result = eae6320::Results::InvalidFile;
//		std::cerr << "No value for \"" << key << "\" was found in the asset table" << std::endl;
//		
//		lua_pop(&io_luaState, 1);
//		// Now the only thing on the stack is the asset table at -1,
//		// and the calling function will deal with this
//		// (regardless of whether this function succeeds or fails).
//		return result;
//
//	}
//	// value is at index -1;
//	int numVertex = static_cast<int>(lua_tonumber(&io_luaState, -1));
//	
//	// pop the value
//	lua_pop(&io_luaState, 1);
//
//	// read next table (vertices)
//	constexpr auto* const key_vertices = "vertices";
//	lua_pushstring(&io_luaState, key_vertices);
//	lua_gettable(&io_luaState, -2);
//
//	if (lua_isnil(&io_luaState, -1))
//	{
//		result = eae6320::Results::InvalidFile;
//		//std::cerr << "No value for \"" << key << "\" was found in the asset table" << std::endl;
//
//		lua_pop(&io_luaState, 1);
//		// Now the only thing on the stack is the asset table at -1,
//		// and the calling function will deal with this
//		// (regardless of whether this function succeeds or fails).
//		return result;
//
//	}
//
//	// now vertex table at index -1, mesh table at index -2
//	//const auto arrayLength = luaL_len(&io_luaState, -1);
//	// 1 BASED!
////	std::vector<eae6320::Graphics::VertexFormats::sMesh> meshVec(numVertex);
//	for (int i = 1; i <= numVertex; i++) 
//	{
//		eae6320::Graphics::VertexFormats::sMesh vertex;
//
//		lua_pushinteger(&io_luaState, i);
//
//		// now vertex table at index -2, mesh table at index -3
//		lua_gettable(&io_luaState, -2);
//		// individual vertex at -1, vertex table at -2, mesh table at -3
//		constexpr auto* const key_x = "x";
//		lua_pushstring(&io_luaState, key_x);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.x = (float)lua_tonumber(&io_luaState, -1);
//		lua_pop(&io_luaState, 1);
//
//		// get the y value
//		constexpr auto* const key_y = "y";
//		lua_pushstring(&io_luaState, key_y);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.y = (float)lua_tonumber(&io_luaState, -1);
//		lua_pop(&io_luaState, 1);
//
//		// get the z value
//		constexpr auto* const key_z = "z";
//		lua_pushstring(&io_luaState, key_z);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.z = (float)lua_tonumber(&io_luaState, -1);
//		lua_pop(&io_luaState, 1);
//
//		// r value
//		constexpr auto* const key_r = "r";
//		lua_pushstring(&io_luaState, key_r);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.r = static_cast<uint8_t>(lua_tonumber(&io_luaState, -1) * 255.0f);
//		lua_pop(&io_luaState, 1);
//
//		// g value
//		constexpr auto* const key_g = "g";
//		lua_pushstring(&io_luaState, key_g);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.g = static_cast<uint8_t>(lua_tonumber(&io_luaState, -1) * 255.0f);
//		lua_pop(&io_luaState, 1);
//
//		// b value
//		constexpr auto* const key_b = "b";
//		lua_pushstring(&io_luaState, key_b);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.b = static_cast<uint8_t>(lua_tonumber(&io_luaState, -1) * 255.0f);
//		lua_pop(&io_luaState, 1);
//
//		// u value
//		constexpr auto* const key_u = "u";
//		lua_pushstring(&io_luaState, key_u);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.u = (float)lua_tonumber(&io_luaState, -1);
//		lua_pop(&io_luaState, 1);
//
//		// v value
//		constexpr auto* const key_v = "v";
//		lua_pushstring(&io_luaState, key_v);
//		// individual vertex at -2
//		lua_gettable(&io_luaState, -2);
//		vertex.v = (float)lua_tonumber(&io_luaState, -1);
//		lua_pop(&io_luaState, 1);
//
//		i_meshVec.push_back(vertex);
//		lua_pop(&io_luaState, 1);
//	} // one vertex , end of for loop
//
//
//	lua_pop(&io_luaState, 1); // pop the vertex table, now mesh table is at -1
//
//	constexpr auto* const key_index = "numIndex";
//	lua_pushstring(&io_luaState, key_index);
//	lua_gettable(&io_luaState, -2);
//	
//	if (lua_isnil(&io_luaState, -1))
//	{
//		result = eae6320::Results::InvalidFile;
//		//std::cerr << "No value for \"" << key << "\" was found in the asset table" << std::endl;
//
//		lua_pop(&io_luaState, 1);
//		// Now the only thing on the stack is the asset table at -1,
//		// and the calling function will deal with this
//		// (regardless of whether this function succeeds or fails).
//		return result;
//
//	}
//
//	int numIndex = static_cast<int>(lua_tonumber(&io_luaState, -1));
//	// pop the value
//	lua_pop(&io_luaState, 1);
//
//	//std::vector<uint16_t> indexVec;
//
//	// mesh table at -1
//	constexpr auto* const key_indices = "indices";
//	lua_pushstring(&io_luaState, key_indices);
//	lua_gettable(&io_luaState, -2);
//
//	if (lua_isnil(&io_luaState, -1))
//	{
//		result = eae6320::Results::InvalidFile;
//		//std::cerr << "No value for \"" << key << "\" was found in the asset table" << std::endl;
//
//		lua_pop(&io_luaState, 1);
//		// Now the only thing on the stack is the asset table at -1,
//		// and the calling function will deal with this
//		// (regardless of whether this function succeeds or fails).
//		return result;
//
//	}
//	// table of index at -1, mesh table at -2
//	readIndexValueFromLua(io_luaState, i_indexVec, numIndex);
//	
//	// done with index table, pop it
//	lua_pop(&io_luaState, 1);
//
//	//// done with mesh table, pop it
//	//lua_pop(&io_luaState, 1);
//
//	//
//	return result;
//}
//
//// table should be at -1 when this function is called
//void cMesh::readIndexValueFromLua(lua_State & io_luaState, std::vector<uint16_t> & indexVec, int numIndex) {
//	for (int i = 1; i <= numIndex/3; i++) {
//		lua_pushinteger(&io_luaState, i);
//		// now vertex table at index -2, mesh table at index -3
//		lua_gettable(&io_luaState, -2);
//		
//		// {0, 1, 2} at index -1
//		for (int j = 1; j <= 3; j++) {
//			lua_pushinteger(&io_luaState, j);
//			lua_gettable(&io_luaState, -2);
//
//			indexVec.push_back((uint16_t)lua_tonumber(&io_luaState, -1));
//			lua_pop(&io_luaState, 1);
//		}
//		// pop individual index table
//		lua_pop(&io_luaState, 1); 
//	}
//}
//
