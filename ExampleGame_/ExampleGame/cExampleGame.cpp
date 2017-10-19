// Include Files
//==============

#include "cExampleGame.h"
#include "Engine/Graphics/cEffect.h"
#include "Engine/Graphics/cSprite.h"
#include "Engine/Graphics/cTexture.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>

cEffect * effect1;
cEffect * effect2;

cSprite * sprite1;
cSprite * sprite2;
cSprite * sprite3;

eae6320::Graphics::cTexture::Handle texture1;
eae6320::Graphics::cTexture::Handle texture2;
eae6320::Graphics::cTexture::Handle texture3;

eae6320::Graphics::renderData data1;
eae6320::Graphics::renderData data2;
eae6320::Graphics::renderData data3;

float timer = 0.0f;

// Inherited Implementation
//=========================
void eae6320::cExampleGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	eae6320::Graphics::SubmitBackgroundColor(0.0f, 0.0f, 128.0f, 1.0f);
	eae6320::Graphics::SubmitEffectAndSprite(data1);
	eae6320::Graphics::SubmitEffectAndSprite(data2);
	eae6320::Graphics::SubmitEffectAndSprite(data3);
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


	data1 = eae6320::Graphics::renderData(effect1, sprite1, eae6320::Graphics::cTexture::s_manager.Get(texture1));
	data2 = eae6320::Graphics::renderData(effect2, sprite2, eae6320::Graphics::cTexture::s_manager.Get(texture2));
	data3 = eae6320::Graphics::renderData(effect2, sprite3, eae6320::Graphics::cTexture::s_manager.Get(texture3));
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

	return Results::Success;
}
