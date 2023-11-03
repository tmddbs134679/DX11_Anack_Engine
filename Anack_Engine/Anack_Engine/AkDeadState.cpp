#include "AkDeadState.h"
#include "AkAI.h"
#include "AkAnimator.h"
#include "AkRigidBody.h"
#include "AkTime.h"
#include "AkSceneManager.h"
#include "AkParticleSystem.h"
#include "AkResources.h"
#include "AkCoin.h"
#include "AkCameraScript.h"
#include "AkFade.h"

namespace Ak
{
	DeadState::DeadState()
		: MonsterState(eMonsterState::Death)
		, m_fTime(0.0f)
		, m_fRadianceTime(0.f)
		, m_bDestoryMonster(false)
		, m_bGrimmVoice(true)
		, m_bDestoryRadiance(true)
		, m_bRadianceDeadSound(true)
		, m_fRadianceExit(0.f)
	{

	}

	DeadState::~DeadState()
	{
		
	}

	void DeadState::update()
	{
		
		Monster* pMonster = GetAI()->GetOwner();

		if (m_bDestoryMonster)
		{
			m_fTime += Time::DeltaTime();

			float deadtime = 0.f;

			

			if (pMonster->GetName() == L"Hunter")
			{
				  pMonster->GetComponent<Collider2D>()->SetSize(Vector2::Zero);
				  deadtime = 3.f;


				  if (m_fTime >= deadtime && pMonster->GetName() == L"Hunter")
				  {
					

					  delete pMonster;

					
				  }
				
			}
			else if ((pMonster->GetName() == L"Grimm"))
			{
				 deadtime = 7.f;


				 //Grimm dead voice Ãâ·Â
				 if (m_bGrimmVoice)
				 {
					 if (m_fTime >= 2.f)
					 {
						 std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
						 for (const auto& clip : test)
						 {
							 if (clip->GetKey() == L"Grimm_dead_voice")
							 {
								 pMonster->GetComponent<AudioSource>()->SetClip(clip);
								 pMonster->GetComponent<AudioSource>()->Play();
								 m_bGrimmVoice = false;
							 }
						 }
					 }
				 }


			}
			
			
			if (m_fTime >= deadtime && pMonster->GetName() == L"Grimm")
			{

				Monster* pMonster = GetAI()->GetOwner();
				Vector3 monpos = pMonster->GetComponent<Transform>()->GetPosition();

				if (pMonster->GetName() == L"Grimm")
				{

					pMonster->GetScene()->GetCurSceneAC()->Stop();

					pMonster->GetScene()->GetCurSceneAC()->Load(L"..\\Resources\\Sound\\Grimm_end.mp3");
					pMonster->GetScene()->GetCurSceneAC()->Play();
					delete pMonster->GetGrimmWall();
					delete pMonster->GetBossBG();

					Coin* pcoin = new Coin();
					pcoin->SetName(L"GrimmCoin");
					pcoin->GetComponent<Transform>()->SetPosition(monpos);

					SceneManager::AddGameObject(eLayerType::LayeredObj, pcoin);
				}

				SceneManager::DestoryObj(pMonster);
				delete pMonster;

				m_bDestoryMonster = false;
			}

		}

		if (pMonster->GetName() == L"Radiance")
		{
			GameObject* pPlayer = pMonster->GetScene()->GetPlayer();

			
			m_fRadianceTime += Time::DeltaTime();


			if (m_bDestoryRadiance)
			{
				if (m_fRadianceTime <= 5.f)
				{
					pMonster->GetSceneCamera()->GetComponent<CameraScript>()->BossDeadCamera();
					pMonster->GetRadianceAttack02()->AttackOff();

					if (m_bRadianceDeadSound)
					{
						pMonster->GetMonsterAC()[4]->Play();
						m_bRadianceDeadSound = false;
					}
				}
				else
				{
					pMonster->GetSceneCamera()->GetComponent<CameraScript>()->BossDeadOff();
					pMonster->GetMonsterAC()[8]->Play();
					//pPlayer->GetCurScene()->GetFade()->bInFadeOut();
					//delete pMonster->GetRadianceAttack01();
					//delete pMonster->GetRadianceAttack02();
					//delete pMonster->GetRadianceAttack03();
					//delete pMonster->GetRadianceAttack04_01();
					//delete pMonster->GetRadianceAttack04_02();
					//delete pMonster->GetRadianceAttack04_03();

				

					Fade* fd = new Fade();
					SceneManager::AddGameObject(eLayerType::LayeredObj, fd);
					fd->bFadeTest();
				
					m_bDestoryRadiance = false;
					
				}
			}
			else
			{
				m_fRadianceExit += Time::DeltaTime();


				if(m_fRadianceExit >= 5.f)
				{
					SceneManager::DestoryObj(pMonster);

					delete pMonster;

					SceneManager::LoadScene(L"PlayScene");
				}
			}

		}

		

		
	}

	void DeadState::Enter()
	{
		Monster* pMonster = GetAI()->GetOwner();
	
		

		if (pMonster->GetName() == L"Baldur")
		{
			if (pMonster->GetDir() == 1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"BaldurDeadR", false);
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"BaldurDeadL", false);
			}
		}
	
		if (pMonster->GetName() == L"Hunter")
		{

			if (pMonster->GetDir() == 1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Dead_r", false);
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Dead_l", false);
			}


			RigidBody* rb = pMonster->AddComponent<RigidBody>();
			rb->SetGravity(Vector2(0.f, -60.f));

			//Sound
			std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
			for (const auto& clip : test)
			{
				if (clip->GetKey() == L"HunterDeath")
				{
					pMonster->GetComponent<AudioSource>()->SetClip(clip);
					pMonster->GetComponent<AudioSource>()->Play();
				}
			}

		}

		if (pMonster->GetName() == L"Grimm")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Dead", false);
			ParticleSystem* pss = pMonster->AddComponent<ParticleSystem>();
			pss->GetMaterial()->SetTexture(Resources::Find<Texture>(L"Grimm_particle"));
			pss->SetParticleCount(100);
			pss->SetParticleSpeed(30.f);
			pss->SetParticleDestory(10.f);
			pss->SetParticleRandom(1.f);
			pss->SetSize(5.f);
			pss->SetRandomDirection(true);
			pss->SetRotation(0.f, 90.f);
		}

		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_Dead", true);

			ParticleSystem* pss = pMonster->AddComponent<ParticleSystem>();
			pss->GetMaterial()->SetTexture(Resources::Find<Texture>(L"Radiance_particle"));
			pss->SetParticleCount(100);
			pss->SetParticleSpeed(30.f);
			pss->SetParticleDestory(10.f);
			pss->SetParticleRandom(1.f);
			pss->SetSize(5.f);
			pss->SetRandomDirection(true);
			pss->SetRotation(0.f, 90.f);

		}

		m_bDestoryMonster = true;

	}

	void DeadState::Exit()
	{

	

	}

}
