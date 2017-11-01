#pragma once
//#include "cRenderState.h"
//#include "cSamplerState.h"
//#include "cShader.h"
//#include "sContext.h"
//#include "VertexFormats.h"
//
//
//#if defined( EAE6320_PLATFORM_GL )
//#include "OpenGL\Includes.h"
//#endif
//
//#if defined(EAE6320_PLATFORM_WINDOWS)
//#include "Direct3D\Includes.h" 
//#endif

#include <Engine/Physics/sRigidBodyState.h>
#include <Engine\Math\cMatrix_transformation.h>
#include <Engine\Math\cQuaternion.h>
#include <Engine\Math\sVector.h>
#include <Engine\Math\Constants.h>

//#include <Engine/Asserts/Asserts.h>
//#include <Engine/Concurrency/cEvent.h>
//#include <Engine/Logging/Logging.h>
//#include <Engine/Platform/Platform.h>
//#include <Engine/Time/Time.h>
//#include <Engine/UserOutput/UserOutput.h>
//#include <Engine/Assets/ReferenceCountedAssets.h>
//
//#include <utility>


// Forward Declarations
//=====================
//
//namespace eae6320
//{
//	namespace Math
//	{
//		class cQuaternion;
//		class cMatrix_transformation
//		struct sVector;
//	}
//}


class cCamera {
public:
	
	//void UpdateSimulationBasedOnInput();

	// probably not needed
	eae6320::Math::cMatrix_transformation m_matrixTransform;

	eae6320::Physics::sRigidBodyState m_rigidBodyState;

	//eae6320::Math::cQuaternion m_orientation;

	//eae6320::Math::sVector m_position;

	float m_verticalFieldOfView_inRadians;

	float m_aspectRatio;

	float m_z_nearPlane;

	float m_z_farPlane;
	//static cMatrix_transformation::CreateWorldToCameraTransform()
};