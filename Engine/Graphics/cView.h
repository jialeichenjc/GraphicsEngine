#pragma once
#if defined( EAE6320_PLATFORM_GL )
#include "OpenGL\Includes.h"
#endif

#if defined(EAE6320_PLATFORM_WINDOWS)
#include "Direct3D\Includes.h" 
#endif

#include "cConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "cRenderState.h"
#include "cSamplerState.h"
#include "cShader.h"
#include "sContext.h"
#include "VertexFormats.h"
#include "Engine\Graphics\cEffect.h"
#include "Engine\Graphics\cSprite.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <utility>

class cView {
public:
#if defined( EAE6320_PLATFORM_D3D )
	// In Direct3D "views" are objects that allow a texture to be used a particular way:
	// A render target view allows a texture to have color rendered to it
	ID3D11RenderTargetView* s_renderTargetView = nullptr;
	// A depth/stencil view allows a texture to have depth rendered to it
	ID3D11DepthStencilView* s_depthStencilView = nullptr;
	
#endif


#if defined(EAE6320_PLATFORM_D3D)
	eae6320::cResult InitializeViews(const unsigned int i_resolutionWidth, const unsigned int i_resolutionHeight);
#endif

	void Buffer();
	void Clear(float f1, float f2, float f3, float f4);
	eae6320::cResult CleanUp();
};
