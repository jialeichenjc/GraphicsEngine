/*
	A vertex format determines the layout of the geometric data
	that the CPU will send to the GPU
*/

#ifndef EAE6320_GRAPHICS_VERTEXFORMATS_H
#define EAE6320_GRAPHICS_VERTEXFORMATS_H

// Include Files
//==============

#include "Configuration.h"

// Vertex Formats
//===============

namespace eae6320
{
	namespace Graphics
	{
		namespace VertexFormats
		{
			struct sGeometry
			{
				// POSITION
				// 2 floats == 8 bytes
				// Offset = 0
				float x, y;

				// TEXCOORD0
				// 2 floats == 8 bytes
				// Offset = 8
				float u, v;
			};

			struct sMesh
			{
				// POSITION
				// 3 floats == 12 bytes
				// Offset = 0
				float x, y, z;

				// COLOR
				// 4 uint8_t == 4 bytes
				// offset = 12
				uint8_t r, g, b, a;

				// TEXTURE
				// 2 floats == 8 bytes
				// Offset = 16
				float u, v;

				sMesh() : r(0), g(0), b(0), a(255) {}
			};
		}
	}
}

#endif	// EAE6320_GRAPHICS_VERTEXFORMATS_H
