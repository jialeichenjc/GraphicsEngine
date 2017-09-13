#include "../cEffect.h"

eae6320::cResult cEffect::Initialize_Platform() {
	auto result = eae6320::Results::Success;

	return result;
}

void cEffect::Bind_Platform() {
	ID3D11ClassInstance* const* noInterfaces = nullptr;
	constexpr unsigned int interfaceCount = 0;
	auto* const direct3dImmediateContext = eae6320::Graphics::sContext::g_context.direct3dImmediateContext;

	// Vertex shader
	{
		EAE6320_ASSERT(s_vertexShader);
		auto* const shader = eae6320::Graphics::cShader::s_manager.Get(s_vertexShader);
		EAE6320_ASSERT(shader && shader->m_shaderObject.vertex);
		direct3dImmediateContext->VSSetShader(shader->m_shaderObject.vertex, noInterfaces, interfaceCount);
	}
	// Fragment shader
	{
		EAE6320_ASSERT(s_fragmentShader);
		auto* const shader = eae6320::Graphics::cShader::s_manager.Get(s_fragmentShader);
		EAE6320_ASSERT(shader && shader->m_shaderObject.fragment);
		direct3dImmediateContext->PSSetShader(shader->m_shaderObject.fragment, noInterfaces, interfaceCount);
	}
	s_renderState.Bind();
}