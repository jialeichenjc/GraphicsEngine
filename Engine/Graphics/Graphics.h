/*
	This file declares the external interface for the graphics system
*/

#ifndef EAE6320_GRAPHICS_H
#define EAE6320_GRAPHICS_H

// Include Files
//==============

#include "Configuration.h"

#include <cstdint>
#include <Engine/Results/Results.h>
#include <Engine\Math\sVector.h>
#include <Engine\Physics\sRigidBodyState.h>
#include "cTexture.h"
#include "cCamera.h"
#if defined( EAE6320_PLATFORM_WINDOWS )
	#include <Engine/Windows/Includes.h>
#endif

// Interface
//==========
class cEffect;
class cSprite;
class cTexture;
class cMesh;
namespace eae6320
{
	namespace Graphics
	{
		// Submission
		//-----------

		struct renderData {
			cEffect * effect;
			cSprite * sprite;
			cTexture * texture;

			renderData() = default;

			renderData(cEffect* iEffect, cSprite * iSprite, cTexture * iTexture)
				: effect(iEffect), sprite(iSprite), texture(iTexture) {}

		};


		struct meshData {
			cEffect * effect;
			cMesh * mesh;

			meshData() = default;
			//Math::sVector pos;
			
			eae6320::Physics::sRigidBodyState rigidBodyState;
;			meshData(cEffect * iEffect, cMesh * iMesh)
				: effect(iEffect), mesh(iMesh) {}

		};

		// These functions should be called from the application (on the application loop thread)

		// As the class progresses you will add your own functions for submitting data,
		// but the following is an example (that gets called automatically)
		// of how the application submits the total elapsed times
		// for the frame currently being submitted
		void SubmitElapsedTime( const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_simulationTime );

		void SubmitBackgroundColor(const float r, const float g, const float b, const float a);

		// When the application is ready to submit data for a new frame
		// it should call this before submitting anything
		// (or, said another way, it is not safe to submit data for a new frame
		// until this function returns successfully)
		cResult WaitUntilDataForANewFrameCanBeSubmitted( const unsigned int i_timeToWait_inMilliseconds );
		// When the application has finished submitting data for a frame
		// it must call this function
		cResult SignalThatAllDataForAFrameHasBeenSubmitted();

		// Render
		//-------

		// This is called (automatically) from the main/render thread.
		// It will render a submitted frame as soon as it is ready
		// (i.e. as soon as SignalThatAllDataForAFrameHasBeenSubmitted() has been called)
		void RenderFrame();

		// Initialization / Clean Up
		//--------------------------

		struct sInitializationParameters
		{
#if defined( EAE6320_PLATFORM_WINDOWS )
			HWND mainWindow = NULL;
	#if defined( EAE6320_PLATFORM_D3D )
			uint16_t resolutionWidth, resolutionHeight;
	#elif defined( EAE6320_PLATFORM_GL )
			HINSTANCE thisInstanceOfTheApplication = NULL;
	#endif
#endif
		};
		void SubmitEffectAndSprite(eae6320::Graphics::renderData);
		void SubmitEffectAndMesh(eae6320::Graphics::meshData&, eae6320::Physics::sRigidBodyState&);
		void SubmitCamera(eae6320::Graphics::cCamera);

		cResult Initialize( const sInitializationParameters& i_initializationParameters );
		cResult CleanUp();
	}
}

#endif	// EAE6320_GRAPHICS_H
