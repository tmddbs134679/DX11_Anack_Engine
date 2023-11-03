#include "AkSkill3State.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkMonsterScript.h"
#include "AkGrimm_Projectile_02.h"
#include "AkRG_Long.h"
#include "AkRG_Short.h"


namespace Ak
{
	Skill3State::Skill3State()
		: MonsterState(eMonsterState::Skill3)
		, m_bDis(false)
		, m_bChangeSkill(false)
		, m_fTime(0.f)
		, m_iCNT(0)
		, m_bRadianceAttack(false)
		, m_fMoveTime(0.f)
		, m_bPlayerOn(false)
		, m_bRadianceSkill03(true)
	{
		m_bSkill[0] = false;
		m_bSkill[1] = false;

		m_bMakeOBJ[0] = false;
		m_bMakeOBJ[1] = false;
		m_bMakeOBJ[2] = false;
	}

	Skill3State::~Skill3State()
	{

	}

	void Skill3State::update()
	{
		

		Monster* pMonster = GetMonster();


		if (m_bSkill[0])
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill3", true);
			m_bSkill[0] = false;
			m_bMakeOBJ[0] = true;
		}


		if (m_bMakeOBJ[0])
		{
			m_fTime += Time::DeltaTime();

			static int m_iCreatePJ = 0;
			Vector2 m_vMonPos = pMonster->GetComponent<Transform>()->GetPostionXY();
			

			if (m_iCNT < 3)
			{
				if (m_fTime >= 0.5f)
				{
					for (m_iCreatePJ; m_iCreatePJ < 8; ++m_iCreatePJ)
					{
						static float angleIncrement = 360.0f / 8.0f;

						Grimm_Projectile_02* GP2 = new Grimm_Projectile_02();

						float angle = m_iCreatePJ * angleIncrement;

						GP2->SetAngle(angle);
						GP2->SetMonPos(pMonster->GetComponent<Transform>()->GetPostionXY());

						SceneManager::AddGameObject(eLayerType::MonsterAttack, GP2);
					}

					if (m_iCreatePJ == 8)
					{
						//m_bMakeOBJ[0] = false;
						m_iCreatePJ = 0;
						m_bDis = true;
						++m_iCNT;
						m_fTime = 0.f;
					}
				}
			}
			else
			{
				m_bMakeOBJ[0] = false;
				m_bDis = true;
				m_iCNT = 0;
			}
		
		}
		if (m_bDis)
		{
			static float fDisTime = 0.f;
			fDisTime += Time::DeltaTime();

			if (fDisTime >= 3.f)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_disappear", false);
				pMonster->GetMonsterAC()[5]->Play();
				m_bDis = false;
				m_bChangeSkill = true;
				fDisTime = 0.f;
			}
		}

		if (m_bChangeSkill)
		{
			static float fChTime = 0.f;
			fChTime += Time::DeltaTime();

			if (fChTime >= 0.5f)
			{
				GetAI()->ChangeState(eMonsterState::Skill1);
				fChTime = 0.f;
			}

		}

		////Radiance
		if (pMonster->GetName() == L"Radiance")
		{
			if (m_bRadianceAttack)
			{
				if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_dis"
					&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);
					pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(0.f, 88.f));

					pMonster->GetRadianceAttack04_03()->Initialize();
					
					m_bRadianceAttack = false;

				}
			}
			else
			{
				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();

				if (pPlayer->GetComponent<Transform>()->GetPosition().y >= 70.f)
				{
					m_bPlayerOn = true;
					if (m_bRadianceSkill03)
					{
						pMonster->GetRadianceAttack04_03()->AttackOff();
						m_bRadianceSkill03 = false;
					}
				}
				else
				{
					m_bPlayerOn = false;
				}


				if (m_bPlayerOn)
				{
					m_fMoveTime += Time::DeltaTime();

					if (m_fMoveTime >= 5.f)
					{
						if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_attack"
							&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
						{
							pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_dis", false);

						}
					}
				}
			
			}


			//Radiance 순간이동 
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_dis"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start", false);
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(RandomX(3), 88.f));
			}

			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_start"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);

				if (!(pMonster->GetRadianceAttack02()->GetAttackOn()))
				{
					pMonster->GetRadianceAttack02()->AttackOn();
				}
				m_fMoveTime = 0.f;
			}

			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				//pMonster->GetRadianceAttack02()->AttackOff();
				GetAI()->ChangeState(eMonsterState::Death);
			}

			
			
		}

		MonsterState::update();
	}
	
	void Skill3State::Enter()
	{
		Monster* pMonster = GetMonster();


		if (pMonster->GetName() == L"Grimm")
		{
			Vector3 pMonPos = pMonster->GetComponent<Transform>()->GetPosition();
			pMonster->GetComponent<Transform>()->SetPosition(Vector3(0.f, 3.f, 0.997f));
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill3_start", false);
			m_bSkill[0] = true;
			pMonster->GetMonsterAC()[4]->Play();

		}

		if (pMonster->GetName() == L"Radiance")
		{

#pragma region Ground

			//UP4
			RG_Long* RL4 = new RG_Long();
			RL4->GetComponent<Transform>()->SetPosition(Vector3(4.f, 16.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RL4);


			RG_Long* RL5 = new RG_Long();
			RL5->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 35.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RL5);

			RG_Long* RL6 = new RG_Long();
			RL6->GetComponent<Transform>()->SetPosition(Vector3(4.f, 46.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RL6);


			RG_Long* RL7 = new RG_Long();
			RL7->GetComponent<Transform>()->SetPosition(Vector3(1.f, 67.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RL7);

			RG_Long* RL8 = new RG_Long();
			RL8->GetComponent<Transform>()->SetPosition(Vector3(0.f, 80.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RL8);


			//UP4
			RG_Short* RS4 = new RG_Short();
			RS4->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 20.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS4);

			RG_Short* RS5 = new RG_Short();
			RS5->GetComponent<Transform>()->SetPosition(Vector3(4.f, 24.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS5);

			RG_Short* RS6 = new RG_Short();
			RS6->GetComponent<Transform>()->SetPosition(Vector3(4.5f, 29.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS6);

			RG_Short* RS7 = new RG_Short();
			RS7->GetComponent<Transform>()->SetPosition(Vector3(-4.f, 39.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS7);

			RG_Short* RS8 = new RG_Short();
			RS8->GetComponent<Transform>()->SetPosition(Vector3(0.f, 42.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS8);


			RG_Short* RS9 = new RG_Short();
			RS9->GetComponent<Transform>()->SetPosition(Vector3(0.f, 52.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS9);


			RG_Short* RS10 = new RG_Short();
			RS10->GetComponent<Transform>()->SetPosition(Vector3(3.f, 56.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS10);


			RG_Short* RS11 = new RG_Short();
			RS11->GetComponent<Transform>()->SetPosition(Vector3(4.f, 61.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS11);

			RG_Short* RS12 = new RG_Short();
			RS12->GetComponent<Transform>()->SetPosition(Vector3(-2.f, 73.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS12);

			RG_Short* RS13 = new RG_Short();
			RS13->GetComponent<Transform>()->SetPosition(Vector3(-5.f, 85.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS13);

			RG_Short* RS14 = new RG_Short();
			RS14->GetComponent<Transform>()->SetPosition(Vector3(5.f, 85.f, 0.99f));
			SceneManager::AddGameObject(eLayerType::Ground, RS14);

#pragma endregion
			
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_dis", false);
			m_bRadianceAttack = true;
			
		}


	}

	void Skill3State::Exit()
	{
		
		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();

		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();


		if (vMonsterPos.x > vPlayerPos.x)
		{
			pMonster->SetDir(-1);
		}
		else
		{
			pMonster->SetDir(1);
		}

		m_bSkill[0] = false;
		m_bSkill[1] = false;

		m_bMakeOBJ[0] = false;
		m_bMakeOBJ[1] = false;
		m_bMakeOBJ[2] = false;

		m_bDis = false;
		m_bChangeSkill  = false;

		if (pMonster->GetName() == L"Grimm")
		{
			pMonster->GetMonsterAC()[4]->Stop();
		}
	}
	
}
