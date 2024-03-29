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
#include <Engine/Graphics/cRenderState.h>
#include <fstream>

//#include <cstdio>

cEffect * effect1;
cEffect * effect2;
cEffect * effect3;

cSprite * sprite1;
cSprite * sprite2;
cSprite * sprite3;

//cMesh * mesh2;

eae6320::Graphics::cTexture::Handle texture1;
eae6320::Graphics::cTexture::Handle texture2;
eae6320::Graphics::cTexture::Handle texture3;

cMesh::Handle mesh1;
cMesh::Handle mesh2;
cMesh::Handle mesh3;
cMesh::Handle mesh4;

eae6320::Graphics::renderData data1;
eae6320::Graphics::renderData data2;
eae6320::Graphics::renderData data3;

eae6320::Graphics::meshData data4;
eae6320::Graphics::meshData data5;
eae6320::Graphics::meshData data6;
eae6320::Graphics::meshData data7;

eae6320::Physics::sRigidBodyState rigidBody4; // for meshData4
eae6320::Physics::sRigidBodyState rigidBody5; // for meshData5
eae6320::Physics::sRigidBodyState rigidBody6; // for meshData6
eae6320::Physics::sRigidBodyState rigidBody7; // for meshData7

eae6320::Graphics::cCamera camera;

float timer = 0.0f;

// test function
//void eae6320::cExampleGame::testWriteFile() {
//	File * pfile;
//	pFile
//}

// Inherited Implementation
//=========================
void eae6320::cExampleGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	eae6320::Graphics::SubmitElapsedTime(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

	eae6320::Graphics::SubmitBackgroundColor(125.0f, 0.0f, 128.0f, 1.0f);
	//eae6320::Graphics::SubmitEffectAndSprite(data1);

	eae6320::Graphics::SubmitCamera(camera);

	eae6320::Graphics::SubmitEffectAndMesh(data5, rigidBody4);
	eae6320::Graphics::SubmitEffectAndMesh(data4, rigidBody5); // almond
	eae6320::Graphics::SubmitEffectAndMesh(data6, rigidBody6);
	eae6320::Graphics::SubmitEffectAndMesh(data7, rigidBody7);
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
	if (timer > 1.0f) 
	{
		rigidBody5.velocity.y = 0.8f;
		rigidBody6.velocity.y = -1.3f;
		rigidBody7.velocity.y = -1.6f;
	}

	if (timer > 10.0f) 
	{
		rigidBody5.velocity.y = -0.8f;
		rigidBody6.velocity.y = 1.3f;
		rigidBody7.velocity.y = 1.6f;

		timer = -8.0f;
	}



}

void  eae6320::cExampleGame::UpdateSimulationBasedOnInput() {
	//if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up)) {
	//	rigidBody4.velocity.y = 1.5f;
	//}
	//else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down) && rigidBody4.position.y >= 0.3f) {
	//	//data4.rigidBodyState.velocity.y = -0.5f;
	//	rigidBody4.velocity.y = -1.5f;
	//}
	//else {
	//	rigidBody4.velocity.y = 0.0f;
	//}

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
		rigidBody4.velocity.x = -1.5f;
	}
	
	else if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		rigidBody4.velocity.x = 1.5f;
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
	timer += i_elapsedSecondCount_sinceLastUpdate;

	rigidBody5.Update(i_elapsedSecondCount_sinceLastUpdate);
	rigidBody6.Update(i_elapsedSecondCount_sinceLastUpdate);
	rigidBody7.Update(i_elapsedSecondCount_sinceLastUpdate);

	camera.m_rigidBodyState.Update(i_elapsedSecondCount_sinceLastUpdate);
}
// Initialization / Clean Up
//--------------------------

eae6320::cResult eae6320::cExampleGame::Initialize()
{
	
	auto result = eae6320::Results::Success;
	result = cEffect::CreateEffect(effect1, "data/Shaders/Vertex/commonvertex1.shd", "data/Shaders/Fragment/commonfrag1.shd", 
		eae6320::Graphics::RenderStates::DepthBuffering);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cEffect::CreateEffect(effect2, "data/Shaders/Vertex/commonvertex2.shd", "data/Shaders/Fragment/commonfrag2.shd", 0);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	// effect3 is used for translucent meshes and has both depth buffering and transparency enabled
	result = cEffect::CreateEffect(effect3, "data/Shaders/Vertex/commonvertex3.shd", "data/Shaders/Fragment/commonfrag3.shd", 
		eae6320::Graphics::RenderStates::AlphaTransparency | eae6320::Graphics::RenderStates::DepthBuffering);
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

	result = eae6320::Graphics::cTexture::s_manager.Load("data/Textures/wood.jpg", texture2);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = eae6320::Graphics::cTexture::s_manager.Load("data/Textures/shifu.tga", texture3);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	//result = cMesh::CreateMesh(mesh1, "data/Meshes/mesh1.lua", i_meshVec, i_indexVec);
	result = cMesh::s_manager.Load("data/Meshes/mesh1.lua.bin", mesh1);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	//result = cMesh::CreateMesh(mesh2, "data/Meshes/mesh2.lua", i_meshVec2, i_indexVec2);
	result = cMesh::s_manager.Load("data/Meshes/mesh2.lua.bin", mesh2);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}
	
	result = cMesh::s_manager.Load("data/Meshes/mesh3.lua.bin", mesh3);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	result = cMesh::s_manager.Load("data/Meshes/mesh4.lua.bin", mesh4);
	if (!result) {
		EAE6320_ASSERT(false);
		return eae6320::Results::Failure;
	}

	data1 = eae6320::Graphics::renderData(effect2, sprite1, eae6320::Graphics::cTexture::s_manager.Get(texture1));
	data2 = eae6320::Graphics::renderData(effect2, sprite2, eae6320::Graphics::cTexture::s_manager.Get(texture2));
	data3 = eae6320::Graphics::renderData(effect2, sprite3, eae6320::Graphics::cTexture::s_manager.Get(texture3));

	// data4: almond; data5: floor 
	data4 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh1), eae6320::Graphics::cTexture::s_manager.Get(texture3));
	data5 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh2), eae6320::Graphics::cTexture::s_manager.Get(texture2));
	
	// data6 and data7 are translucent balls
	data6 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh1), eae6320::Graphics::cTexture::s_manager.Get(texture3));
	data7 = eae6320::Graphics::meshData(effect1, cMesh::s_manager.Get(mesh1), eae6320::Graphics::cTexture::s_manager.Get(texture3));

	// the board
	rigidBody4.position.x = -3.5f;
	rigidBody4.position.y = 0.5f;
	rigidBody4.position.z = -0.5f;

	rigidBody5.position.x = 0.5f;
	rigidBody5.position.y = -2.5f;
	rigidBody5.position.z = -0.5f;

	rigidBody6.position.x = -1.5f;
	rigidBody6.position.y = 0.5f;

	//rigidBody7.position.z = 1.0f;
	rigidBody7.position.x = 2.5f;
	rigidBody7.position.y = 0.8f;
	

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
	
	if (effect1) {
		effect1->DecrementReferenceCount();
	}
	
	if (effect2) {
		effect2->DecrementReferenceCount();
	}

	if (effect3) {
		effect3->DecrementReferenceCount();
	}

	if (texture1) {
		eae6320::Graphics::cTexture::s_manager.Release(texture1);
	}

	if (texture2) {
		eae6320::Graphics::cTexture::s_manager.Release(texture2);
	}

	if (texture3) {
		eae6320::Graphics::cTexture::s_manager.Release(texture3);
	}

	if (sprite1) {
		sprite1->DecrementReferenceCount();
	}

	if (sprite2) {
		sprite2->DecrementReferenceCount();
	}

	if (sprite3) {
		sprite3->DecrementReferenceCount();
	}
	
	if (mesh1) {
		cMesh::s_manager.Release(mesh1);
	}

	if (mesh2) {
		cMesh::s_manager.Release(mesh2);
	}

	if (mesh3) {
		cMesh::s_manager.Release(mesh3);
	}

	if (mesh4) {
		cMesh::s_manager.Release(mesh4);
	}

	return Results::Success;
}
