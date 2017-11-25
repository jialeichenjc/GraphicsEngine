/*
This class builds hardware-ready meshes
*/

#ifndef EAE6320_CMESHBUILDER_H
#define EAE6320_CMESHBUILDER_H

// Include Files
//==============

#include <Tools/AssetBuildLibrary/cbBuilder.h>
#include <Engine/Graphics/cMesh.h>

// Class Declaration
//==================

namespace eae6320
{
	namespace Assets
	{
		class cMeshBuilder : public cbBuilder
		{
			
			//static eae6320::cResult Load(const char* const i_path, cMesh*& o_mesh);

			// Input the path to a mesh file, extract mesh info from that file (lua file)
			static eae6320::cResult LoadMesh(const char* const i_path, std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
				std::vector<uint16_t> & i_indexVec);
			
			// mesh paramters
			std::vector<eae6320::Graphics::VertexFormats::sMesh> m_meshVec;
			std::vector<uint16_t> m_indexVec;

			size_t m_indexCount;
			size_t m_vertexCount;

		private:

			// Build
			//------

			virtual cResult Build(const std::vector<std::string>& i_arguments) override;

			static eae6320::cResult LoadMeshValues(lua_State& io_luaState,
				std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
				std::vector<uint16_t> & i_indexVec);

			static void readIndexValueFromLua(lua_State & io_luaState, std::vector<uint16_t> & indexVec, int numIndex);

		};
	}
}


#endif	// EAE6320_CMESHBUILDER_H
