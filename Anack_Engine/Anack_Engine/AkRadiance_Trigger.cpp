#include "AkRadiance_Trigger.h"
#include "AkRadiance_Trigger_Script.h"
#include "AkTime.h"
#include "AkMonsterScript.h"
#include "AkSceneManager.h"
#include "AkCameraScript.h"



namespace Ak
{
	Radiance_Trigger::Radiance_Trigger()
		: m_bRadianceAttackStart(false)
		, m_bDestory(false)
	{
		SetName(L"Radiance_Trigger");
		GetComponent<Transform>()->SetScale(10.f, 2.f, 0.f);
		GetComponent<Transform>()->SetPosition(Vector3(0.f, -1.8f, 1.f));
		AddComponent<Collider2D>();
		
		AddComponent<Radiance_Trigger_Script>();
		//Rts->SetOwner(this);

	}

	Radiance_Trigger::~Radiance_Trigger()
	{

	}

	void Radiance_Trigger::Initialize()
	{

	}

	void Radiance_Trigger::Update()
	{

	

		if (GetComponent<Radiance_Trigger_Script>()->GetStart())
		{
			static float fTime = 0.f;
			fTime += Time::DeltaTime();

			if (fTime >= 3.f)
			{
				if (m_Radiance_Light != nullptr)
				{
					m_Radiance_Light->GetComponent<Animator>()->PlayAnimation(L"Radiance_Light", false);
				}
				
				GetComponent<Radiance_Trigger_Script>()->OffStart();
				m_bRadianceAttackStart = true;
				m_Player->GetCurScene()->GetCameraObj()->GetComponent<CameraScript>()->BossDeadCamera();
				
			}
		}

		
		if (m_bRadianceAttackStart)
		{
			static float fTime = 0.f;
			fTime += Time::DeltaTime();

			m_Player->GetCurScene()->GetCameraObj()->GetComponent<CameraScript>()->BossDeadCamera();

			if (fTime >= 9.f)
			{
				m_Radiance->GetAI()->ChangeState(eMonsterState::AttackStart);
				

				for (auto& ac : m_Radiance->GetMonsterAC())
				{
					if (ac->GetKey() == L"Radiance_Scream")
					{
						ac->Play();
					}
				}

				
					SceneManager::DestoryObj(m_Radiance_Light);
					delete m_Radiance_Light;
					m_Radiance_Light = nullptr;

				m_Player->GetCurScene()->GetCameraObj()->GetComponent<CameraScript>()->BossDeadOff();
				m_Player->GetCurScene()->GetCurSceneAC()->Play();
				m_bRadianceAttackStart = false;
				m_bDestory = true;
			}

			if (m_bDestory)
			{
				SceneManager::DestoryObj(this);
				delete this;
				m_Player = nullptr;
				m_Radiance = nullptr;
			}
		}
		
	

		
		GameObject::Update();
	}

	void Radiance_Trigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Trigger::Render()
	{
		GameObject::Render();
	}

}