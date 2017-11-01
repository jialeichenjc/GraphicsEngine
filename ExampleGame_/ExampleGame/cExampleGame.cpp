// Include Files
//==============

#include "cExampleGame.h"
#include "Engine/Graphics/cEffect.h"
#include "Engine/Graphics/cSprite.h"
#include "Engine/Graphics/cTexture.h"
#include "Engine/Graphics/cMesh.h"
#include "Engine/Graphics/cCamera.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>
#include <Engine/Math/Constants.h>

cEffect * effect1;
cEffect * effect2;

cSprite * sprite1;
cSprite * sprite2;
cSprite * sprite3;

cMesh * mesh1;
cMesh * mesh2;

eae6320::Graphics::cTexture::Handle texture1;
eae6320::Graphics::cTexture::Handle texture2;
eae6320::Graphics::cTexture::Handle texture3;

eae6320::Graphics::renderData data1;
eae6320::Graphics::renderData data2;
eae6320::Graphics::renderData data3;

eae6320::Graphics::meshData data4;
eae6320::Graphics::meshData data5;

eae6320::Graphics::cCamera camera;

float timer = 0.0f;

// Inherited Implementation
//=========================
void eae6320::cExampleGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	eae6320::Graphics::SubmitBackgroundColor(125.0f, 0.0f, 128.0f, 1.0f);
	eae6320::Graphics::SubmitEffectAndSprite(data2);

	eae6320::Graphics::SubmitEffectAndMesh(data4);
	eae6320::Graphics::SubmitEffectAndMesh(data5);

}

// Run
//----

void eae6320::cExampleGame::UpdateBasedOnInput()
{
	// Is the user pressing the ESC key?
	if ( UserInput::IsKeyPressed( UserInput::KeyCodes::Escape ) )
	{
		// Exit the application
		const auto result = Exit( EXIT_SUCCESS );
		EAE6320_ASSERT( result );
	}

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Tab))
	{
		data1.texture = eae6320::Graphics::cTexture::s_manager.Get(texture2);
	}
	else 
	{
		data1.texture = eae6320::Graphics::cTexture::s_manager.Get(texture1);
	}
}

void  eae6320::cExampleGame::UpdateBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {
	timer += i_elapsedSecondCount_sinceLastUpdate;
	if (timer > 3) 
	{
		data2.texture = eae6320::Graphics::cTexture::s_manager.Get(texture3);
	}

	if (timer > 6) 
	{
		data2.texture = eae6320::Graphics::cTexture::s_manager.Get(texture2);
		timer = 0.0f;
	}

}

void  eae6320::cExampleGame::UpdateSimulationBasedOnInput() {
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up))
	{
		//data4.pos.y += 0.02f;
	}
}

void  eae6320::cExampleGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {

}
// Initialization / Clean Up
//--------------------------

eae6320::cResult eae6320::cExampleGame::Initialize()
{
	
	auto result = eae6320::Results::Success;
	result = cEffect::CreateEffect(effect1, "data/Shaders/Vertex/example1.shd", "data/Shaders/Fragment/example1.shd", 0);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cEffect::CreateEffect(effect2, "data/Shaders/Vertex/example2.shd", "data/Shaders/Fragment/example2.shd", 0);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cSprite::CreateSprite(sprite1, 0.0f, 0.0f, 1.0f, 1.0f);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cSprite::CreateSprite(sprite2, -1.0f, -1.0f, 0.0f, 0.0f);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cSprite::CreateSprite(sprite3, -1.0f, 0.0f, 0.0f, 1.0f);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = eae6320::Graphics::cTexture::s_manager.Load("data/Textures/babyPanda.jpg", texture1);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = eae6320::Graphics::cTexture::s_manager.Load("data/Textures/cupcake.jpg", texture2);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = eae6320::Graphics::cTexture::s_manager.Load("data/Textures/shifu.jpg", texture3);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	std::vector<eae6320::Graphics::VertexFormats::sMesh> i_meshVec(4);
	eae6320::Graphics::VertexFormats::sMesh vertex1;
	vertex1.x = 0.0f;
	vertex1.y = -1.0f;
	vertex1.z = 0.0f;

	vertex1.r = 255;

	eae6320::Graphics::VertexFormats::sMesh vertex2;
	vertex2.x = 1.0f;
	vertex2.y = -1.0f;
	vertex2.z = 0.0f;

	vertex2.r = 255;
	vertex2.g = 255;

	eae6320::Graphics::VertexFormats::sMesh vertex3;
	vertex3.x = 1.0f;
	vertex3.y = 0.0f;
	vertex3.z = 0.0f;

	vertex3.r = 255;
	vertex3.g = 255;

	eae6320::Graphics::VertexFormats::sMesh vertex4;
	vertex4.x = 0.0f;
	vertex4.y = 0.0f;
	vertex4.z = 0.0f;

	vertex4.b = 255;
	i_meshVec[0] = vertex1;
	i_meshVec[1] = vertex2;
	i_meshVec[2] = vertex3;
	i_meshVec[3] = vertex4;

	std::vector<uint16_t> i_indexVec(6);
	i_indexVec[0] = 0;
	i_indexVec[1] = 2;
	i_indexVec[2] = 1;
	i_indexVec[3] = 0;
	i_indexVec[4] = 3;
	i_indexVec[5] = 2;

	result = cMesh::CreateMesh(mesh1, i_meshVec, i_indexVec);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	std::vector<eae6320::Graphics::VertexFormats::sMesh> i_meshVec2(3);
	eae6320::Graphics::VertexFormats::sMesh vertex5;
	vertex5.x = -1.0f;
	vertex5.y = 0.0f;
	vertex5.z = 0.0f;

	vertex5.r = 127;
	vertex5.g = 127;
	vertex5.b = 127;

	eae6320::Graphics::VertexFormats::sMesh vertex6;
	vertex6.x = 0.0f;
	vertex6.y = 0.0f;
	vertex6.z = 0.0f;

	vertex6.r = 255;
	vertex6.g = 255;
	vertex6.b = 255;

	eae6320::Graphics::VertexFormats::sMesh vertex7;
	vertex7.x = 0.0f;
	vertex7.y = 1.0f;
	vertex7.z = 0.0f;

	vertex7.r = 255;

	i_meshVec2[0] = vertex5;
	i_meshVec2[1] = vertex6;
	i_meshVec2[2] = vertex7;

	std::vector<uint16_t> i_indexVec2(3);
	i_indexVec2[0] = 0;
	i_indexVec2[1] = 2;
	i_indexVec2[2] = 1;

	result = cMesh::CreateMesh(mesh2, i_meshVec2, i_indexVec2);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	data1 = eae6320::Graphics::renderData(effect2, sprite1, eae6320::Graphics::cTexture::s_manager.Get(texture1));
	data2 = eae6320::Graphics::renderData(effect2, sprite2, eae6320::Graphics::cTexture::s_manager.Get(texture2));
	data3 = eae6320::Graphics::renderData(effect2, sprite3, eae6320::Graphics::cTexture::s_manager.Get(texture3));

	data4 = eae6320::Graphics::meshData(effect1, mesh1);
	data5 = eae6320::Graphics::meshData(effect1, mesh2);

	camera.m_verticalFieldOfView_inRadians = eae6320::Math::Pi / 4;
	camera.m_z_nearPlane = 0.1f;
	camera.m_z_farPlane = 100.0f;

	return Results::Success;
}

eae6320::cResult eae6320::cExampleGame::CleanUp()
{
	cEffect::CleanUpEffect(effect1);
	cEffect::CleanUpEffect(effect2);

	eae6320::Graphics::cTexture::s_manager.Release(texture1);
	eae6320::Graphics::cTexture::s_manager.Release(texture2);
	eae6320::Graphics::cTexture::s_manager.Release(texture3);

	cSprite::CleanUpSprite(sprite1);
	cSprite::CleanUpSprite(sprite2);
	cSprite::CleanUpSprite(sprite3);

	cMesh::CleanUpMesh(mesh1);
	cMesh::CleanUpMesh(mesh2);

	return Results::Success;
}
