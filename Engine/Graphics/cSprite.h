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

class cSprite {
public:
#if defined( EAE6320_PLATFORM_GL )
	// A vertex buffer holds the data for each vertex
	GLuint s_vertexBufferId = 0;
	// A vertex array encapsulates the vertex data as well as the vertex input layout
	GLuint s_vertexArrayId = 0;
#endif

#if defined( EAE6320_PLATFORM_D3D )
	// A vertex buffer holds the data for each vertex
	ID3D11Buffer* s_vertexBuffer = nullptr;
	// D3D has an "input layout" object that associates the layout of the vertex format struct
	// with the input from a vertex shader
	ID3D11InputLayout* s_vertexInputLayout = nullptr;
#endif
	EAE6320_ASSETS_DECLAREREFERENCECOUNT();
	EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();
	EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(cSprite);

	// Access
	//-------

	using Handle = eae6320::Assets::cHandle<cSprite>;
	static eae6320::Assets::cManager<cSprite> s_manager;

	static eae6320::cResult CreateSprite(cSprite *& sprite, float p1, float p2, float p3, float p4);
	//eae6320::cResult CleanUpSprite(cSprite *& sprite);
	void Draw();

	~cSprite() {
		CleanUp();
	}
private:
	cSprite() = default;
	eae6320::cResult Initialize(float p1, float p2, float p3, float p4);

	eae6320::cResult CleanUp();

};