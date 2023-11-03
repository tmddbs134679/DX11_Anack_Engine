#include "AkBattleToStartTrigger.h"
#include "AkSceneChangeScript.h"

namespace Ak
{
	BattleToStartTrigger::BattleToStartTrigger()
	{
		
		AddComponent<Collider2D>();
		GetComponent<Collider2D>()->SetSize(Vector2(2.f, 2.f));

		AddComponent<SceneChangeScript>();
		GetComponent<SceneChangeScript>()->SetTriggerName(L"BattleToStartTrigger");

	}

	BattleToStartTrigger::~BattleToStartTrigger()
	{

	}

	void BattleToStartTrigger::Initialize()
	{

	}

	void BattleToStartTrigger::Update()
	{
		GameObject::Update();
	}

	void BattleToStartTrigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void BattleToStartTrigger::Render()
	{
		GameObject::Render();
	}

}