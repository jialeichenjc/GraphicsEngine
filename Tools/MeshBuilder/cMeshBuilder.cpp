// Include Files
//==============

#include "cMeshBuilder.h"

#include <algorithm>
#include <codecvt>
#include <Engine/Graphics/TextureFormats.h>
#include <Engine/Math/Functions.h>
#include <Engine/Platform/Platform.h> 
#include <External/DirectXTex/Includes.h>
#include <fstream>
#include <locale>
#include <string>
#include <Tools/AssetBuildLibrary/Functions.h>
#include <utility>

// Inherited Implementation
//=========================

// Build
//------
eae6320::cResult eae6320::Assets::cMeshBuilder::Build (const std::vector<std::string>& i_arguments) {
	auto result = eae6320::Results::Success;
	std::string errMsg = "Mesh file cannot be loaded";
	
	if (!(result = eae6320::Platform::CopyFileA(m_path_source, m_path_target, false, true, &errMsg))) {
		EAE6320_ASSERTF(false, errMsg.c_str());
		OutputErrorMessageWithFileInfo(m_path_source, errMsg.c_str());

		goto OnExit;
	}
	
OnExit:

	return result;
}