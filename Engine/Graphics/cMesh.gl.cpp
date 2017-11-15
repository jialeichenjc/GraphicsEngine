#include "cMesh.h"
eae6320::cResult cMesh::CreateMesh(cMesh *& mesh, std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec,
	std::vector<uint16_t> & i_indexVec) {
	
	auto result = eae6320::Results::Success;
	mesh = new cMesh();
	result = mesh->Initialize(i_meshVec, i_indexVec);
	if (result) {
		goto OnExit;
	}
	else {
		EAE6320_ASSERT(false);
	}
OnExit:

	return result;
}

eae6320::cResult cMesh::Initialize(std::vector<eae6320::Graphics::VertexFormats::sMesh> & i_meshVec, std::vector<uint16_t> & i_indexVec) {
	auto result = eae6320::Results::Success;
	m_indexCount = i_indexVec.size();
	m_vertexCount = i_meshVec.size();
	// Create a vertex array object and make it active
	{
		constexpr GLsizei arrayCount = 1;
		glGenVertexArrays(arrayCount, &s_vertexArrayId);
		const auto errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindVertexArray(s_vertexArrayId);
			const auto errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				result = eae6320::Results::Failure;
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to bind a new vertex array: %s",
					reinterpret_cast<const char*>(gluErrorString(errorCode)));
				goto OnExit;
			}
		}
		else
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to get an unused vertex array ID: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
			goto OnExit;
		}
	}
	// Create a vertex buffer object and make it active
	{
		constexpr GLsizei bufferCount = 1;
		glGenBuffers(bufferCount, &s_vertexBufferId);
		const auto errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindBuffer(GL_ARRAY_BUFFER, s_vertexBufferId);
			const auto errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				result = eae6320::Results::Failure;
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to bind a new vertex buffer: %s",
					reinterpret_cast<const char*>(gluErrorString(errorCode)));
				goto OnExit;
			}
		}
		else
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to get an unused vertex buffer ID: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
			goto OnExit;
		}
	}

	// Create index buffer
	{
		constexpr GLsizei bufferCount = 1;
		glGenBuffers(bufferCount, &s_indexBufferId);
		const auto errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_indexBufferId);
			const auto errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				result = eae6320::Results::Failure;
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to bind a new vertex buffer: %s",
					reinterpret_cast<const char*>(gluErrorString(errorCode)));
				goto OnExit;
			}
		}
		else
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to get an unused vertex buffer ID: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
			goto OnExit;
		}
	}

	// Assign the data to the buffer
	{
		const auto vertexCount = i_meshVec.size();
		eae6320::Graphics::VertexFormats::sMesh * vertexData = new eae6320::Graphics::VertexFormats::sMesh[vertexCount];

		{
			for (size_t i = 0; i < i_meshVec.size(); i++) {
				vertexData[i].x = i_meshVec[i].x;
				vertexData[i].y = i_meshVec[i].y;
				vertexData[i].z = i_meshVec[i].z;
				vertexData[i].r = i_meshVec[i].r;
				vertexData[i].g = i_meshVec[i].g;
				vertexData[i].b = i_meshVec[i].b;
				//vertexData[i].a = i_meshVec[i].a;

			}

		}
		const auto bufferSize = vertexCount * sizeof(eae6320::Graphics::VertexFormats::sMesh);
		EAE6320_ASSERT(bufferSize < (uint64_t(1u) << (sizeof(GLsizeiptr) * 8)));
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(bufferSize), reinterpret_cast<GLvoid*>(vertexData),
			// In our class we won't ever read from the buffer
			GL_STATIC_DRAW);
		const auto errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to allocate the vertex buffer: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
			goto OnExit;
		}
		delete[] vertexData;
	}

	// Assign the data to the index buffer
	{
		const auto indexCount = i_indexVec.size();
		uint16_t * indexData = new uint16_t[indexCount];

		{

			for (size_t i = 0; i < i_indexVec.size(); i+=3) {
				indexData[i] = i_indexVec[i];
				indexData[i + 1] = i_indexVec[i + 1];
				indexData[i + 2] = i_indexVec[i + 2];
			}

		}

		const auto bufferSize = indexCount * sizeof(uint16_t);
		EAE6320_ASSERT(bufferSize < (uint64_t(1u) << (sizeof(GLsizeiptr) * 8)));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(bufferSize), reinterpret_cast<GLvoid*>(indexData),
			// In our class we won't ever read from the buffer
			GL_STATIC_DRAW);
		const auto errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to allocate the vertex buffer: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
			goto OnExit;
		}
		delete[] indexData;
	}


	// Initialize vertex format
	{
		// The "stride" defines how large a single vertex is in the stream of data
		// (or, said another way, how far apart each position element is)
		const auto stride = static_cast<GLsizei>(sizeof(eae6320::Graphics::VertexFormats::sMesh));

		// Position (0)
		// 3 floats == 12 bytes
		// Offset = 0
		{
			constexpr GLuint vertexElementLocation = 0;
			constexpr GLint elementCount = 3;
			constexpr GLboolean notNormalized = GL_FALSE;	// The given floats should be used as-is
			glVertexAttribPointer(vertexElementLocation, elementCount, GL_FLOAT, notNormalized, stride,
				reinterpret_cast<GLvoid*>(offsetof(eae6320::Graphics::VertexFormats::sMesh, x)));
			const auto errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				glEnableVertexAttribArray(vertexElementLocation);
				const GLenum errorCode = glGetError();
				if (errorCode != GL_NO_ERROR)
				{
					result = eae6320::Results::Failure;
					EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
					eae6320::Logging::OutputError("OpenGL failed to enable the POSITION vertex attribute at location %u: %s",
						vertexElementLocation, reinterpret_cast<const char*>(gluErrorString(errorCode)));
					goto OnExit;
				}
			}
			else
			{
				result = eae6320::Results::Failure;
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to set the POSITION vertex attribute at location %u: %s",
					vertexElementLocation, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				goto OnExit;
			}
		}

		// Color (4)
		// 4 uint8_t == 4 bytes
		// Offset = 8
		{
			constexpr GLuint vertexElementLocation = 1;
			constexpr GLint elementCount = 4;
			constexpr GLboolean normalized = GL_TRUE;	// normalized
			glVertexAttribPointer(vertexElementLocation, elementCount, GL_UNSIGNED_BYTE, normalized, stride,
				reinterpret_cast<GLvoid*>(offsetof(eae6320::Graphics::VertexFormats::sMesh, r)));
			const auto errorCode = glGetError();
			if (errorCode == GL_NO_ERROR)
			{
				glEnableVertexAttribArray(vertexElementLocation);
				const GLenum errorCode = glGetError();
				if (errorCode != GL_NO_ERROR)
				{
					result = eae6320::Results::Failure;
					EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
					eae6320::Logging::OutputError("OpenGL failed to enable the TEXCOORD vertex attribute at location %u: %s",
						vertexElementLocation, reinterpret_cast<const char*>(gluErrorString(errorCode)));
					goto OnExit;
				}
			}
			else
			{
				result = eae6320::Results::Failure;
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to set the TEXCOORD vertex attribute at location %u: %s",
					vertexElementLocation, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				goto OnExit;
			}
		}
	}

OnExit:

	return result;

}

void cMesh::DrawMesh() {
	// Bind a specific vertex buffer to the device as a data source
	{
		glBindVertexArray(s_vertexArrayId);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}
	// Render triangles from the currently-bound vertex buffer
	{
		// The mode defines how to interpret multiple vertices as a single "primitive";
		// a triangle list is defined
		// (meaning that every primitive is a triangle and will be defined by three vertices)
		constexpr GLenum mode = GL_TRIANGLES;
		// It's possible to start rendering primitives in the middle of the stream
		const GLvoid* const offset = 0;
		// As of this comment we are only drawing a single triangle
		// (you will have to update this code in future assignments!)
		glDrawElements(mode, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_SHORT, offset);
		EAE6320_ASSERT(glGetError() == GL_NO_ERROR);
	}
}

eae6320::cResult cMesh::CleanUpMesh(cMesh *& mesh) {
	auto result = eae6320::Results::Success;
	if (mesh != NULL) {
		result = mesh->CleanUp();
		mesh->DecrementReferenceCount();
		mesh = NULL;
	}

	return result;
}

eae6320::cResult cMesh::CleanUp() {
	auto result = eae6320::Results::Success;

	if (s_vertexArrayId != 0)
	{
		// Make sure that the vertex array isn't bound
		{
			// Unbind the vertex array
			glBindVertexArray(0);
			const auto errorCode = glGetError();
			if (errorCode != GL_NO_ERROR)
			{
				if (result)
				{
					result = eae6320::Results::Failure;
				}
				EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
				eae6320::Logging::OutputError("OpenGL failed to unbind all vertex arrays before cleaning up geometry: %s",
					reinterpret_cast<const char*>(gluErrorString(errorCode)));
			}
		}
		constexpr GLsizei arrayCount = 1;
		glDeleteVertexArrays(arrayCount, &s_vertexArrayId);
		const auto errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			if (result)
			{
				result = eae6320::Results::Failure;
			}
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to delete the vertex array: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
		}
		s_vertexArrayId = 0;
	}
	if (s_vertexBufferId != 0)
	{
		constexpr GLsizei bufferCount = 1;
		glDeleteBuffers(bufferCount, &s_vertexBufferId);
		const auto errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			if (result)
			{
				result = eae6320::Results::Failure;
			}
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to delete the vertex buffer: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
		}
		s_vertexBufferId = 0;
	}

	if (s_indexBufferId != 0)
	{
		constexpr GLsizei bufferCount = 1;
		glDeleteBuffers(bufferCount, &s_indexBufferId);
		const auto errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			if (result)
			{
				result = eae6320::Results::Failure;
			}
			EAE6320_ASSERTF(false, reinterpret_cast<const char*>(gluErrorString(errorCode)));
			eae6320::Logging::OutputError("OpenGL failed to delete the vertex buffer: %s",
				reinterpret_cast<const char*>(gluErrorString(errorCode)));
		}
		s_indexBufferId = 0;
	}
	return result;
}