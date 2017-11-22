#include "cEffect.h" 
void cEffect::Bind() {
	Bind_Platform();
}

eae6320::cResult cEffect::CreateEffect(cEffect *& effect, char* vertexPath, const char* fragPath, const uint8_t renderState) {
	auto result = eae6320::Results::Success;
	effect = new cEffect();

	result = effect->Initialize(vertexPath, fragPath, renderState);
	if(result) {
		goto OnExit;
	}
	else {
		EAE6320_ASSERT(false);
	}
OnExit:

	return result;
}

eae6320::cResult cEffect::CleanUpEffect(cEffect *& effect) {
	auto result = eae6320::Results::Success;
	if (effect != NULL) {
		result = effect->CleanUp();
		effect->DecrementReferenceCount();
		effect = NULL;
	}
	
	return result;
}

eae6320::cResult cEffect::Initialize(const char* vertexPath, const char* fragPath, const uint8_t renderState) {
	auto result = eae6320::Results::Success;

	if (!(result = eae6320::Graphics::cShader::s_manager.Load(vertexPath,
		s_vertexShader, eae6320::Graphics::ShaderTypes::Vertex)))
	{
		EAE6320_ASSERT(false);
		goto OnExit;
	}
	if (!(result = eae6320::Graphics::cShader::s_manager.Load(fragPath,
		s_fragmentShader, eae6320::Graphics::ShaderTypes::Fragment)))
	{
		EAE6320_ASSERT(false);
		goto OnExit;
	}
	{
		//constexpr uint8_t defaultRenderState = 0;
		if (!(result = s_renderState.Initialize(renderState)))
		{
			EAE6320_ASSERT(false);
			goto OnExit;
		}
	}

	result = Initialize_Platform();
	OnExit:

	return result;
}

eae6320::cResult cEffect::CleanUp() {
	auto result = eae6320::Results::Success;

	if (s_vertexShader)
	{
		const auto localResult = eae6320::Graphics::cShader::s_manager.Release(s_vertexShader);
		if (!localResult)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = localResult;
			}
		}
	}
	if (s_fragmentShader)
	{
		const auto localResult = eae6320::Graphics::cShader::s_manager.Release(s_fragmentShader);
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
		const auto localResult = s_renderState.CleanUp();
		if (!localResult)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = localResult;
			}
		}
	}

	return result;
}

