#pragma once
#include "../Graphics.h"

#include "Includes.h"
#include "../cConstantBuffer.h"
#include "../ConstantBufferFormats.h"
#include "../cRenderState.h"
#include "../cSamplerState.h"
#include "../cShader.h"
#include "../sContext.h"
#include "../VertexFormats.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <utility>

class cEffectD3D {
public:
	eae6320::Graphics::cShader::Handle m_vertexShader;
	eae6320::Graphics::cShader::Handle m_fragmentShader;

	eae6320::Graphics::cRenderState m_renderState;
	
	eae6320::cResult InitializeEffect();

	eae6320::cResult CleanUp();

};