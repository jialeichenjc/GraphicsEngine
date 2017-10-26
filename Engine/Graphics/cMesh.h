#pragma once
#include "cRenderState.h"
#include "cSamplerState.h"
#include "cShader.h"
#include "sContext.h"
#include "VertexFormats.h"


#if defined( EAE6320_PLATFORM_GL )
#include "OpenGL\Includes.h"
#endif

#if defined(EAE6320_PLATFORM_WINDOWS)
#include "Direct3D\Includes.h" 
#endif

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <Engine/Assets/ReferenceCountedAssets.h>

#include <utility>

class cMesh {
public:
#if defined( EAE6320_PLATFORM_GL )
	// A vertex buffer holds the data for each vertex
	GLuint s_vertexBufferId = 0;
	// A vertex array encapsulates the vertex data as well as the vertex input layout
	GLuint s_vertexArrayId = 0;
	// Index buffer
	GLuint s_indexBufferId = 0;

#endif

#if defined( EAE6320_PLATFORM_D3D )
	// Index buffer
	ID3D11Buffer* s_indexBuffer = nullptr;

	// A vertex buffer holds the data for each vertex
	ID3D11Buffer* s_vertexBuffer = nullptr;
	// D3D has an "input layout" object that associates the layout of the vertex format struct
	// with the input from a vertex shader
	ID3D11InputLayout* s_vertexInputLayout = nullptr;
#endif
	EAE6320_ASSETS_DECLAREREFERENCECOUNT();
	EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();
	EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(cMesh);


	static eae6320::cResult CreateMesh(cMesh *& mesh, std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
		std::vector<uint16_t> & i_indexVec);
	static eae6320::cResult CleanUpMesh(cMesh *& i_mesh);
	void DrawMesh();
private:
	cMesh() = default;
	size_t m_indexCount;
	size_t m_vertexCount;
	eae6320::cResult Initialize(std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
		std::vector<uint16_t> & i_indexVec);

	eae6320::cResult CleanUp();

};