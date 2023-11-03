#include "AkAttackStartState.h"
#include "AkMonster.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkAI.h"
#include "AkSceneManager.h"
#include "AkResources.h"
#include "AkGround.h"
#include "AkMeshRenderer.h"

namespace Ak
{

	AttackStartState::AttackStartState()
		: MonsterState(eMonsterState::AttackStart)
		, mTime(0.f)
		, bEnter(false)
		, m_grimmTime(0.f)
		, m_bGrimmEnter(false)
		, m_bGrimmSecEnter(false)
		, m_grimmsecTime(0.f)
		, m_bGrimmThiEnter(false)
		, m_bAttackChange(false)
		, m_bRadianceCh(true)
	{

	}

	AttackStartState::~AttackStartState()
	{

	}

	void AttackStartState::update()
	{
		//MonsterState::update();

		if (bEnter)
		{
			Monster* pMonster = GetMonster();
			if (pMonster->GetName() == L"Baldur")
			{
				mTime += Time::DeltaTime();

				if (mTime >= 0.5f)
				{
					GetAI()->ChangeState(eMonsterState::Attack);
				}
			}
		
		}


	

#pragma region Grimm

		if (m_bGrimmEnter)
		{
			m_grimmTime += Time::DeltaTime();
			m_grimmsecTime += Time::DeltaTime();

			if (m_grimmTime >= 2.f)
			{
				Monster* pMonster = GetMonster();

				if (pMonster->GetName() == L"Grimm")
				{

					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_start_01", false);
					m_grimmTime = -1.f;

					Ground* Boss_wall_l = new Ground();
					SceneManager::AddGameObject(eLayerType::Ground, Boss_wall_l);
					MeshRenderer* mr_boss_wall_l = Boss_wall_l->AddComponent<MeshRenderer>();
					mr_boss_wall_l->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr_boss_wall_l->SetMaterial(Resources::Find<Material>(L"Boss_wall_L_01"));
					Boss_wall_l->GetComponent<Transform>()->SetPosition(Vector3(-17.5f, -1.6f, 0.996f));
					Boss_wall_l->GetComponent<Transform>()->SetScale(Vector3(3.f, 8.f, 0.f));
					
					pMonster->SetGrimmWall(Boss_wall_l);
				}
			}
		}

		if (m_grimmsecTime >= 4.f)
		{
			Monster* pMonster = GetMonster();
			if (pMonster->GetName() == L"Grimm")
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_start_01_02", false);
				Vector3 vPreBGPos = pMonster->GetBossBG()->GetComponent<Transform>()->GetPosition();

				pMonster->GetBossBG()->GetComponent<Transform>()->SetPosition(Vector3(vPreBGPos.x, vPreBGPos.y, 1.4f));


				//BG->Light 같이 제거
				for (GameObject* lightObj : pMonster->GetLightObj()) 
				{
					SceneManager::DestoryObj(lightObj);
					delete lightObj;
				}
				pMonster->GetLightObj().clear();


				m_grimmsecTime = 0.f;
				m_bGrimmThiEnter = true;
				m_bGrimmEnter = false;
				
			}
		}

		if (m_bGrimmThiEnter)
		{
			static float thrTime = 0.f;
			thrTime += Time::DeltaTime();

			if (thrTime >= 1.f)
			{
				Monster* pMonster = GetMonster();
				if (pMonster->GetName() == L"Grimm")
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_start_02", false);
					m_bGrimmForEnter = true;
					m_bGrimmThiEnter = false;
					pMonster->GetScene()->GetCurSceneAC()->Play();
					

				}
			}
		}

		if (m_bGrimmForEnter)
		{
			static float forTime = 0.f;
			forTime += Time::DeltaTime();

			if (forTime >= 2.f)
			{
				Monster* pMonster = GetMonster();
				if (pMonster->GetName() == L"Grimm")
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_start_03", false);
					m_bGrimmForEnter = false;
					m_bAttackChange = true;
					
				}
			}
		}

		//AttackChange
		if (m_bAttackChange)
		{
			static float fAttackChange = 0.f;
			fAttackChange += Time::DeltaTime();

			if (fAttackChange >= 2.f)
			{
				GetAI()->ChangeState(eMonsterState::Skill1);

			}
		}

		Monster* pMonster = GetMonster();

		if (pMonster->GetName() == L"Radiance")
		{
			static float sfTime = 0.f;
			sfTime += Time::DeltaTime();

			if (m_bRadianceCh)
			{
				if (sfTime >= 5.f)
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_dis", false);
					m_bRadianceCh = false;
				}

			}
		
			//dis anim 종료시 skill1로 이동
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_dis"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				//GetAI()->ChangeState(eMonsterState::Death);
				GetAI()->ChangeState(eMonsterState::Skill1);
			}
		}

#pragma endregion

		
		MonsterState::update();

	}

	void AttackStartState::Enter()
	{
		bEnter = true;

		Monster* pMonster = GetMonster();

		pMonster->SetMonsterState(eMonsterState::AttackStart);

		if (pMonster->GetName() == L"Baldur")
		{
			if (pMonster->GetDir() == 1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Baldur_Attack_start_l", false);
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Baldur_Attack_start_r", false);
			}
		}
	
		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start", true);
			pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(0.f, 5.f));
		}
	
		m_bGrimmEnter = true;
	}

	void AttackStartState::Exit()
	{
		mTime = 0.f;
		bEnter = false;


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

	}
}