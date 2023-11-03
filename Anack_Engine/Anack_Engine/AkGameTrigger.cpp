#include "AkGameTrigger.h"
#include "AkGroundScript.h"
#include "AkTexture.h"
#include "AkResources.h"

namespace Ak
{
	GameTrigger::GameTrigger()
	{
		AddComponent<Collider2D>();
		AddComponent<GroundScript>();
	}

	GameTrigger::~GameTrigger()
	{
		
	}

	void GameTrigger::Initialize()
	{

	}

	void GameTrigger::Update()
	{
		GameObject::Update();
	}

	void GameTrigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void GameTrigger::Render()
	{
		GameObject::Render();
	}
}