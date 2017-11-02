#include "cView.h"
void cView::Clear(float f1, float f2, float f3, float f4) {
	{
		glClearColor(f1, f2, f3, f4);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}
	{
		constexpr GLbitfield clearColor = GL_COLOR_BUFFER_BIT;
		glClear(clearColor);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}

	{
		glDepthMask(GL_TRUE);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
		glClearDepth(1);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}
	{
		constexpr GLbitfield clearDepth = GL_DEPTH_BUFFER_BIT;
		glClear(clearDepth);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}
}

void cView::Buffer() {
	const auto deviceContext = eae6320::Graphics::sContext::g_context.deviceContext;
	EAE6320_ASSERT(deviceContext != NULL);

	const auto glResult = SwapBuffers(deviceContext);
	EAE6320_ASSERT(glResult != FALSE);
}

eae6320::cResult cView::CleanUp() {
	auto result = eae6320::Results::Success;

	return result;
}
