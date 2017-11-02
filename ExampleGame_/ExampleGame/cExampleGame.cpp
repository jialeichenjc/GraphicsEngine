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

eae6320::Physics::sRigidBodyState rigidBody4; // for meshData4
eae6320::Physics::sRigidBodyState rigidBody5; // for meshData4

eae6320::Graphics::cCamera camera;

float timer = 0.0f;

// Inherited Implementation
//=========================
void eae6320::cExampleGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	eae6320::Graphics::SubmitBackgroundColor(125.0f, 0.0f, 128.0f, 1.0f);
	//eae6320::Graphics::SubmitEffectAndSprite(data2);

	eae6320::Graphics::SubmitCamera(camera);
	eae6320::Graphics::SubmitEffectAndMesh(data4, rigidBody4);

	eae6320::Graphics::SubmitEffectAndMesh(data5, rigidBody5);

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
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up)) {
		//data4.rigidBodyState.velocity.y = 0.5f;
		//data4.rigidBodyState.Update()
		rigidBody4.velocity.y = 0.5f;
	}
	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
		//data4.rigidBodyState.velocity.y = -0.5f;
		rigidBody4.velocity.y = -0.5f;
	}

	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
		rigidBody4.velocity.x = -0.5f;
	}
	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		rigidBody4.velocity.x = 0.5f;
	}

	if (!UserInput::IsKeyPressed(UserInput::KeyCodes::Up) && !UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
		rigidBody4.velocity.y = 0.0f;
	}

	if (!UserInput::IsKeyPressed(UserInput::KeyCodes::Left) && !UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		rigidBody4.velocity.x = 0.0f;
	}
	if (UserInput::IsKeyPressed('W')) {
		camera.m_rigidBodyState.velocity.z = -0.5f;
	}

	else if (UserInput::IsKeyPressed('S')) {
		camera.m_rigidBodyState.velocity.z = 0.5f;
	}
	else if (UserInput::IsKeyPressed('A')) {
		camera.m_rigidBodyState.velocity.x = -0.5f;
	}
	else if (UserInput::IsKeyPressed('D')) {
		camera.m_rigidBodyState.velocity.x = 0.5f;
	}

	if (!UserInput::IsKeyPressed('W') && !UserInput::IsKeyPressed('S')) {
		camera.m_rigidBodyState.velocity.z = 0.0f;
	}

	if (!UserInput::IsKeyPressed('A') && !UserInput::IsKeyPressed('D')) {
		camera.m_rigidBodyState.velocity.x = 0.0f;
	}

	//if(!UserInput::IsKeyPressed(UserInput::KeyCodes::Up) && !UserInput::IsKeyPressed(UserInput::KeyCodes::Down))
}

void  eae6320::cExampleGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {
	rigidBody4.Update(i_elapsedSecondCount_sinceLastUpdate);
	//data4.rigidBodyState = rigidBody4;
	//data4.rigidBodyState.Update(i_elapsedSecondCount_sinceLastUpdate);
	camera.m_rigidBodyState.Update(i_elapsedSecondCount_sinceLastUpdate);
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

	std::vector<eae6320::Graphics::VertexFormats::sMesh> i_meshVec(8);
	//eae6320::Graphics::VertexFormats::sMesh vertex1;
	i_meshVec[0].x = -1.0f;
	i_meshVec[0].y = -1.0f;
	i_meshVec[0].z = 1.0f;

	i_meshVec[0].r = 255;

	i_meshVec[1].x = -1.0f;
	i_meshVec[1].y = 1.0f;
	i_meshVec[1].z = 1.0f;

	i_meshVec[1].r = 255;
	i_meshVec[1].g = 255;

	i_meshVec[2].x = 1.0f;
	i_meshVec[2].y = 1.0f;
	i_meshVec[2].z = 1.0f;

	i_meshVec[2].r = 255;
	i_meshVec[2].g = 255;

	i_meshVec[3].x = 1.0f;
	i_meshVec[3].y = -1.0f;
	i_meshVec[3].z = 1.0f;

	i_meshVec[3].b = 255;

	i_meshVec[4].x = -1.0f;
	i_meshVec[4].y = -1.0f;
	i_meshVec[4].z = -1.0f;

	i_meshVec[4].r = 255;

	i_meshVec[5].x = -1.0f;
	i_meshVec[5].y = 1.0f;
	i_meshVec[5].z = -1.0f;

	i_meshVec[5].r = 255;
	i_meshVec[5].g = 255;

	i_meshVec[6].x = 1.0f;
	i_meshVec[6].y = 1.0f;
	i_meshVec[6].z = -1.0f;

	i_meshVec[6].r = 255;
	i_meshVec[6].g = 255;

	i_meshVec[7].x = 1.0f;
	i_meshVec[7].y = -1.0f;
	i_meshVec[7].z = -1.0f;

	i_meshVec[7].b = 255;
	

	std::vector<uint16_t> i_indexVec(36);
	// front
	i_indexVec[0] = 0;
	i_indexVec[1] = 1;
	i_indexVec[2] = 2;
	i_indexVec[3] = 0;
	i_indexVec[4] = 2;
	i_indexVec[5] = 3;
	
	// bottom
	i_indexVec[6] = 0;
	i_indexVec[7] = 3;
	i_indexVec[8] = 4;
	i_indexVec[9] = 4;
	i_indexVec[10] = 3;
	i_indexVec[11] = 7;

	// left
	i_indexVec[12] = 5;
	i_indexVec[13] = 1;
	i_indexVec[14] = 4;
	i_indexVec[15] = 4;
	i_indexVec[16] = 1;
	i_indexVec[17] = 0;

	// right
	i_indexVec[18] = 3;
	i_indexVec[19] = 2;
	i_indexVec[20] = 7;
	i_indexVec[21] = 2;
	i_indexVec[22] = 6;
	i_indexVec[23] = 7;
	
	// top
	i_indexVec[24] = 1;
	i_indexVec[25] = 5;
	i_indexVec[26] = 6;
	i_indexVec[27] = 1;
	i_indexVec[28] = 6;
	i_indexVec[29] = 2;

	// back
	i_indexVec[30] = 4;
	i_indexVec[31] = 5;
	i_indexVec[32] = 6;
	i_indexVec[33] = 4;
	i_indexVec[34] = 6;
	i_indexVec[35] = 7;


	result = cMesh::CreateMesh(mesh1, i_meshVec, i_indexVec);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}
	
	std::vector<eae6320::Graphics::VertexFormats::sMesh> i_meshVec2(4);
	i_meshVec2[0].x = -3.0f;
	i_meshVec2[0].y = -1.0f;
	i_meshVec2[0].z = 2.0f;

	i_meshVec2[0].r = 127;
	i_meshVec2[0].g = 127;
	i_meshVec2[0].b = 127;

	i_meshVec2[1].x = 3.0f;
	i_meshVec2[1].y = -1.0f;
	i_meshVec2[1].z = 2.0f;

	i_meshVec2[1].r = 255;
	i_meshVec2[1].g = 255;
	i_meshVec2[1].b = 255;

	i_meshVec2[2].x = -3.0f;
	i_meshVec2[2].y = -1.0f;
	i_meshVec2[2].z = -2.0f;

	i_meshVec2[2].r = 255;

	i_meshVec2[3].x = 3.0f;
	i_meshVec2[3].y = -1.0f;
	i_meshVec2[3].z = -2.0f;

	std::vector<uint16_t> i_indexVec2(6);
	i_indexVec2[0] = 0;
	i_indexVec2[1] = 2;
	i_indexVec2[2] = 3;
	i_indexVec2[3] = 0;
	i_indexVec2[4] = 3;
	i_indexVec2[5] = 1;

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

	eae6320::Math::sVector position(0.0f, 0.0f, 10.0f);
	/*data4.rigidBodyState.position.x = 0.0f;
	data4.rigidBodyState.position.y = 0.0f;
	data4.rigidBodyState.position.z = 0.0f;*/
	camera.m_rigidBodyState.position = position;

	camera.m_verticalFieldOfView_inRadians = eae6320::Math::Pi / 4;
	camera.m_z_nearPlane = 0.1f;
	camera.m_z_farPlane = 100.0f;
	camera.m_aspectRatio = 1;
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
