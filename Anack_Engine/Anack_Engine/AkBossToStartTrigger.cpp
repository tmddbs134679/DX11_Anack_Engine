#include "AkBossToStartTrigger.h"
#include "AkSceneChangeScript.h"

namespace Ak
{
	BossToStartTrigger::BossToStartTrigger()
	{
		AddComponent<Collider2D>();
		GetComponent<Collider2D>()->SetSize(Vector2(2.f, 2.f));

		AddComponent<SceneChangeScript>();
		GetComponent<SceneChangeScript>()->SetTriggerName(L"BossToStartTrigger");
	}

	BossToStartTrigger::~BossToStartTrigger()
	{

	}

	void BossToStartTrigger::Initialize()
	{

	}

	void BossToStartTrigger::Update()
	{
		GameObject::Update();
	}

	void BossToStartTrigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void BossToStartTrigger::Render()
	{
		GameObject::Render();
	}

}