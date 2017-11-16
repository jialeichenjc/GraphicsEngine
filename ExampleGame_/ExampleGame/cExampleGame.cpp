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

//cMesh * mesh2;

eae6320::Graphics::cTexture::Handle texture1;
eae6320::Graphics::cTexture::Handle texture2;
eae6320::Graphics::cTexture::Handle texture3;

cMesh::Handle mesh1;
cMesh::Handle mesh2;

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
	eae6320::Graphics::SubmitElapsedTime(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

	eae6320::Graphics::SubmitBackgroundColor(125.0f, 0.0f, 128.0f, 1.0f);
	eae6320::Graphics::SubmitEffectAndSprite(data1);

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
		rigidBody4.velocity.y = 0.5f;
	}
	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
		//data4.rigidBodyState.velocity.y = -0.5f;
		rigidBody4.velocity.y = -0.5f;
	}
	else {
		rigidBody4.velocity.y = 0.0f;
	}

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
		rigidBody4.velocity.x = -0.5f;
	}
	
	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		rigidBody4.velocity.x = 0.5f;
	}

	else {
		rigidBody4.velocity.x = 0.0f;
	}
	if (UserInput::IsKeyPressed('W')) {
		camera.m_rigidBodyState.velocity.z = -1.0f;
	}

	else if (UserInput::IsKeyPressed('S')) {
		camera.m_rigidBodyState.velocity.z = 1.0f;
	}
	else {
		camera.m_rigidBodyState.velocity.z = 0.0f;
	}
	if (UserInput::IsKeyPressed('A')) {
		camera.m_rigidBodyState.velocity.x = -0.5f;
	}
	else if (UserInput::IsKeyPressed('D')) {
		camera.m_rigidBodyState.velocity.x = 0.5f;
	}

	else {
		camera.m_rigidBodyState.velocity.x = 0.0f;
	}
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

	result = cSprite::CreateSprite(sprite1, 0.5f, 0.5f, 1.0f, 1.0f);
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

	//result = cMesh::CreateMesh(mesh1, "data/Meshes/mesh1.lua", i_meshVec, i_indexVec);
	result = cMesh::s_manager.Load("data/Meshes/mesh1.lua", mesh1);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	//result = cMesh::CreateMesh(mesh2, "data/Meshes/mesh2.lua", i_meshVec2, i_indexVec2);
	result = cMesh::s_manager.Load("data/Meshes/mesh2.lua", mesh2);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}
	

	data1 = eae6320::Graphics::renderData(effect2, sprite1, eae6320::Graphics::cTexture::s_manager.Get(texture1));
	data2 = eae6320::Graphics::renderData(effect2, sprite2, eae6320::Graphics::cTexture::s_manager.Get(texture2));
	data3 = eae6320::Graphics::renderData(effect2, sprite3, eae6320::Graphics::cTexture::s_manager.Get(texture3));

	data4 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh1), eae6320::Graphics::cTexture::s_manager.Get(texture3));
	data5 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh2), eae6320::Graphics::cTexture::s_manager.Get(texture2));

	eae6320::Math::sVector position(0.0f, 0.0f, 10.0f);
	camera.m_rigidBodyState.position = position;

	camera.m_verticalFieldOfView_inRadians = eae6320::Math::Pi / 4;
	camera.m_z_nearPlane = 0.1f;
	camera.m_z_farPlane = 100.0f;
	camera.m_aspectRatio = 1;
	return Results::Success;
}

eae6320::cResult eae6320::cExampleGame::CleanUp()
{
	
	effect1->DecrementReferenceCount();
	effect2->DecrementReferenceCount();

	eae6320::Graphics::cTexture::s_manager.Release(texture1);
	eae6320::Graphics::cTexture::s_manager.Release(texture2);
	eae6320::Graphics::cTexture::s_manager.Release(texture3);

	sprite1->DecrementReferenceCount();
	sprite2->DecrementReferenceCount();
	sprite3->DecrementReferenceCount();

	cMesh::s_manager.Release(mesh1);
	cMesh::s_manager.Release(mesh2);

	return Results::Success;
}
