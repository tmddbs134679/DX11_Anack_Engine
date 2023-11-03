#include "AkBossStartTigger.h"
#include "AkBossTriggerScript.h"
#include "AkTime.h"
#include "AkSceneManager.h"
#include "AkGround.h"
#include "AkSceneChangeScript.h"

namespace Ak
{
	BossStartTigger::BossStartTigger()
	{
		SetName(L"BossStartTrigger");

		GetComponent<Transform>()->SetScale(2.f, 10.f, 0.f);
		AddComponent<Collider2D>();
		AddComponent<BossTriggerScript>();

	}

	BossStartTigger::~BossStartTigger()
	{
		fTime = 0.f;
	}

	void BossStartTigger::Initialize()
	{

	}

	void BossStartTigger::Update()
	{
		GameObject::Update();

		if (GetComponent<BossTriggerScript>()->GetTriggerState())
		{
			
			fTime += Time::DeltaTime();

			if (fTime >= 0.2f)
			{
		
				m_bBrumm->GetComponent<AudioSource>()->Stop();
				SceneManager::DestoryObj(this);
				delete this;
			}
		}
	}

	void BossStartTigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void BossStartTigger::Render()
	{
		GameObject::Render();
	}

}