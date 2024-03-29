/*
	This file should be #included by all shaders
*/

// Version Information
//====================

#if defined( EAE6320_PLATFORM_GL )

	// GLSL shaders require the version to be #defined before anything else in the shader
	#version 420

#endif

// Types
//======

#if defined( EAE6320_PLATFORM_D3D )

	#define vec2 float2
	#define vec3 float3
	#define vec4 float4
	#define mat2 float2x2
	#define mat3 float3x3
	#define mat4 float4x4

#elif defined( EAE6320_PLATFORM_GL )

	#define float2 vec2
	#define float3 vec3
	#define float4 vec4
	#define float2x2 mat2
	#define float3x3 mat3
	#define float4x4 mat4

#endif

// Constant Buffers
//=================

#if defined( EAE6320_PLATFORM_D3D )

	#define DeclareConstantBuffer( i_name, i_id ) cbuffer i_name : register( b##i_id )

#elif defined( EAE6320_PLATFORM_GL )

	#define DeclareConstantBuffer( i_name, i_id ) layout( std140, binding = i_id ) uniform i_name

#endif

// Textures
//=========

#if defined( EAE6320_PLATFORM_D3D )

	#define DeclareTextures( i_texture, i_sampler, i_id ) Texture2D i_texture : register( t##i_id );\
														SamplerState i_sampler : register( s##i_id )

#elif defined( EAE6320_PLATFORM_GL )

	#define DeclareTextures( i_texture, i_sampler, i_id ) layout( binding = i_id ) uniform sampler2D i_texture

#endif

// SampledColor
//=============

#if defined( EAE6320_PLATFORM_D3D )

	#define SampledColor const float4 
	
	#define GetSampledColor( i_colorTexture, i_sampler ) i_colorTexture.Sample( i_sampler, i_texture )

#elif defined( EAE6320_PLATFORM_GL )

	#define SampledColor vec4 
	
	#define GetSampledColor( i_colorTexture, i_sampler ) texture2D( i_colorTexture, i_texture );

#endif

// Vertex Position
#if defined( EAE6320_PLATFORM_D3D )

	#define PositionOutput o_position

#elif defined( EAE6320_PLATFORM_GL )

	#define PositionOutput gl_Position

#endif

// Multiplication
#if defined( EAE6320_PLATFORM_D3D )

	#define Multiply( i_matrix, i_vector ) mul( i_matrix, i_vector)

#elif defined( EAE6320_PLATFORM_GL )

	#define Multiply( i_matrix, i_vector ) i_matrix * i_vector

#endif