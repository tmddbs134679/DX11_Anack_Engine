#include "AkSceneChangeScript.h"
#include "AkSceneManager.h"
#include "AkTime.h"
#include "AkLight.h"
#include "AkScene.h"
#include "AkInput.h"



namespace Ak
{

	SceneChangeScript::SceneChangeScript()
		: mTime(0.f)
		, bEnter(false)
		, mScene(nullptr)
		, m_bInBattleScene(false)
		, m_bInAbyssScene(false)
		, m_bBossToStartScene(false)
		, m_bUI(true)
		, m_bAbyssToRadiance(false)
	{

	}

	SceneChangeScript::~SceneChangeScript()
	{

	}

	void SceneChangeScript::Initialize()
	{

	}

	void SceneChangeScript::Update()
	{
		//0.5초 지연 후 화면전환 setting
		if (bEnter)
		{
			if (m_bInBattleScene)
			{
				mTime += Time::DeltaTime();
				if (mTime >= 1.f)
				{
					SceneManager::LoadScene(L"Battle_BG01");
				}
			}
			
			if (m_bInAbyssScene)
			{
				mTime += Time::DeltaTime();
				if (mTime >= 1.f)
				{
					SceneManager::LoadScene(L"AbyssScene");
				}
			}


			if (m_bAbyssToRadiance)
			{
				mTime += Time::DeltaTime();
				if (mTime >= 1.f)
				{
					SceneManager::LoadScene(L"RadianceScene");
				}
			}
		

			if (m_bBossToStartScene)
			{
				mTime += Time::DeltaTime();
				if (mTime >= 1.f)
				{
					SceneManager::LoadScene(L"StartGame");
				}
			}

			
		}



	}

	void SceneChangeScript::LateUpdate()
	{

	}

	void SceneChangeScript::Render()
	{

	}

	void SceneChangeScript::OnCollisionEnter(Collider2D* other)
	{		
		
		mTime = 0.f;

	}

	void SceneChangeScript::OnCollision(Collider2D* other)
	{
		bEnter = true;

		if (m_strTriggerName == L"StartTrigger")
		{
			
			m_bInBattleScene = true;
			mScene->GetFade()->bInFadeOut();
		}

		if (m_strTriggerName == L"BattleTrigger")
		{
			
			m_bInAbyssScene = true;
			mScene->GetFade()->bInFadeOut();
		}


		GameObject* pPlayer = other->GetOwner();




		if (m_strTriggerName == L"GrimmTrigger")
		{
			if (Input::GetKeyDown(eKeyCode::UP))
			{

				if (!pPlayer->GetCoin())
				{
					if (m_bUI)
					{
						UI_NPC* pUI_NPC = new UI_NPC();
						pUI_NPC->SetGrimmTrigger(true);
						pUI_NPC->Initialize();
						m_ui = pUI_NPC;
						m_bUI = false;
					}
					else
					{
						m_ui->SetGrimmTrigger(false);
						delete m_ui;
						m_ui = nullptr;
						m_bUI = true;
					}
					
					
				}
				else
				{
					SceneManager::LoadScene(L"BossScene");
				}
			}
		}
	
		if (m_strTriggerName == L"BattleToStartTrigger")
		{
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				SceneManager::LoadScene(L"StartGame");
			}
		}

		if (m_strTriggerName == L"BossToStartTrigger")
		{
			
			m_bBossToStartScene = true;
			mScene->GetFade()->bInFadeOut();
			
		}

		if (m_strTriggerName == L"AbyssToRadiance")
		{
			
			m_bAbyssToRadiance = true;
			mScene->GetFade()->bInFadeOut();
		}
		
	}

	void SceneChangeScript::OnCollisionExit(Collider2D* other)
	{
		mTime = 0.f;
	}

}