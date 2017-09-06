#include "cEffect.d3d.h"

eae6320::cResult cEffectD3D::InitializeEffect() {
	auto result = eae6320::Results::Success;

	if (!(result = eae6320::Graphics::cShader::s_manager.Load("data/Shaders/Vertex/example.shd",
		m_vertexShader, eae6320::Graphics::ShaderTypes::Vertex)))
	{
		EAE6320_ASSERT(false);
		goto OnExit;
	}

OnExit:

	return result;
}

eae6320::cResult cEffectD3D::CleanUp() {
	auto result = eae6320::Results::Success;

	if (m_vertexShader)
	{
		const auto localResult = eae6320::Graphics::cShader::s_manager.Release(m_vertexShader);
		if (!localResult)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = localResult;
			}
		}
	}
	if (m_fragmentShader)
	{
		const auto localResult = eae6320::Graphics::cShader::s_manager.Release(m_fragmentShader);
		if (!localResult)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = localResult;
			}
		}
	}

	{
		const auto localResult = m_renderState.CleanUp();
		if (!localResult)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = localResult;
			}
		}
	}
}