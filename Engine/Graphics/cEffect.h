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

class cEffect {
public:
	eae6320::Graphics::cShader::Handle s_vertexShader;
	eae6320::Graphics::cShader::Handle s_fragmentShader;

	eae6320::Graphics::cRenderState s_renderState;

	
	static eae6320::cResult CreateEffect(cEffect *& effect, char* vertexPath, const char* fragPath, const uint8_t renderState);

	//static eae6320::cResult CleanUpEffect(cEffect *& effect);
	void Bind();

	
	EAE6320_ASSETS_DECLAREREFERENCECOUNT()
	EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS()
	EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(cEffect)

#if defined( EAE6320_PLATFORM_GL )
	GLuint s_programId = 0;
#endif
	~cEffect() {
		CleanUp();
	}
private:
	eae6320::cResult Initialize_Platform();
	// constructor
	cEffect() {}
	eae6320::cResult Initialize(const char* vertexPath, const char* fragPath, const uint8_t renderState);

	void Bind_Platform();
	eae6320::cResult CleanUp();
	
};