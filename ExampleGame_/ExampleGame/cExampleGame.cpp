// Include Files
//==============

#include "cExampleGame.h"
#include "Engine/Graphics/cEffect.h"
#include "Engine/Graphics/cSprite.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>

cEffect * effect1;
cEffect * effect2;

cSprite * sprite1;
cSprite * sprite2;
cSprite * sprite3;
// Inherited Implementation
//=========================
void eae6320::cExampleGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	eae6320::Graphics::SubmitBackgroundColor(0.0f, 0.0f, 128.0f, 1.0f);
	eae6320::Graphics::SubmitEffectAndSprite(effect1, sprite1);
	eae6320::Graphics::SubmitEffectAndSprite(effect1, sprite2);
	eae6320::Graphics::SubmitEffectAndSprite(effect2, sprite3);
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
}

// Initialization / Clean Up
//--------------------------

eae6320::cResult eae6320::cExampleGame::Initialize()
{
	

	cEffect::CreateEffect(effect1, "data/Shaders/Vertex/example1.shd", "data/Shaders/Fragment/example1.shd", 0);
	cEffect::CreateEffect(effect2, "data/Shaders/Vertex/example2.shd", "data/Shaders/Fragment/example2.shd", 0);

	cSprite::CreateSprite(sprite1, 0.0f, 0.0f, 1.0f, 1.0f);
	cSprite::CreateSprite(sprite2, -1.0f, -1.0f, 0.0f, 0.0f);
	cSprite::CreateSprite(sprite3, -1.0f, 0.0f, 0.0f, 1.0f);
	return Results::Success;
}

eae6320::cResult eae6320::cExampleGame::CleanUp()
{
	cEffect::CleanUpEffect(effect1);
	cEffect::CleanUpEffect(effect2);
	cSprite::CleanUpSprite(sprite1);
	cSprite::CleanUpSprite(sprite2);
	cSprite::CleanUpSprite(sprite3);

	return Results::Success;
}
