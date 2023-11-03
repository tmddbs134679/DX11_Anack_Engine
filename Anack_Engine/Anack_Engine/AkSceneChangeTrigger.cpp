#include "AkSceneChangeTrigger.h"
#include "AkSceneChangeScript.h"

namespace Ak
{

	SceneChangeTrigger::SceneChangeTrigger()
	{
		AddComponent<Collider2D>();
		AddComponent<SceneChangeScript>();
		
		
	}

	SceneChangeTrigger::~SceneChangeTrigger()
	{

	}

	void SceneChangeTrigger::Initialize()
	{
		GetComponent<SceneChangeScript>()->SetTriggerName(GetName());
	}

	void SceneChangeTrigger::Update()
	{
		GameObject::Update();
	}

	void SceneChangeTrigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SceneChangeTrigger::Render()
	{
		GameObject::Render();
	}
}
