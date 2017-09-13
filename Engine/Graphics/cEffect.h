#pragma once
#include "cRenderState.h"
#include "cSamplerState.h"
#include "cShader.h"
#include "sContext.h"
#include "VertexFormats.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <utility>

class cEffect {
public:
	eae6320::Graphics::cShader::Handle m_vertexShader;
	eae6320::Graphics::cShader::Handle m_fragmentShader;

	eae6320::Graphics::cRenderState m_renderState;

	eae6320::cResult Initialize();

	eae6320::cResult CleanUp();

#if defined( EAE6320_PLATFORM_GL )
	GLuint s_programId = 0;
#endif

private:
	eae6320::cResult Initialize_Platform();

	eae6320::cResult CleanUp_Platform();

};