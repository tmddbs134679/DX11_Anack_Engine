#include "AkGrimmTrigger.h"
#include "AkGrimmTriggerScript.h"
#include "AkSceneChangeScript.h"

namespace Ak
{
	GrimmTrigger::GrimmTrigger()
	{
		SetName(L"GrimmTrigger");

		GetComponent<Transform>()->SetScale(2.f, 3.f, 0.f);
		AddComponent<Collider2D>();
		AddComponent<SceneChangeScript>();

		GetComponent<SceneChangeScript>()->SetTriggerName(L"GrimmTrigger");

		
	}

	GrimmTrigger::~GrimmTrigger()
	{

	}

	void GrimmTrigger::Initialize()
	{

	}

	void GrimmTrigger::Update()
	{
		GameObject::Update();
	}

	void GrimmTrigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void GrimmTrigger::Render()
	{
		GameObject::Render();
	}

}