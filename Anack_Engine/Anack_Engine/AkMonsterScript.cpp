#include "AkMonsterScript.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkGameObject.h"
#include "AkAnimator.h"
#include "AkTime.h"
#include "AkRigidBody.h"
#include "AkSceneManager.h"

namespace Ak
{

	MonsterScript::MonsterScript()
		: m_Monster(nullptr)
		, m_pAI(nullptr)
		, m_fKnockBackTime(0.f)
		, m_bDestoryMonster(false)
		, m_fTimeDestory(0.0f)
		, m_AIDestory(nullptr)
	{

	}

	MonsterScript::~MonsterScript()
	{
		if (m_pAI)
		{
			delete m_pAI;
			m_pAI = nullptr;
		}
	}

	void MonsterScript::Initialize()
	{

	
	}

	void MonsterScript::Update()
	{
		m_pAI->Update();

	}

	void MonsterScript::LateUpdate()
	{

	}

	void MonsterScript::Render()
	{

	}

	void MonsterScript::OnCollisionEnter(Collider2D* _other)
	{
		
		Monster* pMonster = m_pAI->GetOwner();

		GameObject* pGameObj = _other->GetOwner();

		//몬스터 헌터 그라운드 충돌
		if (pGameObj->GetLayerType() == eLayerType::Ground && m_pAI->GetOwner()->GetName() == L"Hunter")
		{
			//Death 상태면 Death상태 유지
			if (m_pAI->GetActiveState()->GetType() != eMonsterState::Death)
			{
				
				//그라운드랑 충돌 시 방향 랜덤으로 setting 후 랜덤 방향으로 헌터 이동
				
				int dirX = pMonster->GetComponent<MonsterState>()->RandomDir();
				int dirY = pMonster->GetComponent<MonsterState>()->RandomDir();


				pMonster->SetMonsterDirX(-dirX);
				pMonster->SetMonsterDirY(-dirY);

				if (pMonster->GetMonsterDirX() == 1)
				{
					if (pMonster->GetName() == L"Baldur")
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Baldur_idle_r", true);
					}
					else if (pMonster->GetName() == L"Hunter")
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Patrol_r", true);
					}
				}
				else
				{
					if (pMonster->GetName() == L"Baldur")
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Baldur_idle_l", true);
					}
					else if (pMonster->GetName() == L"Hunter")
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Patrol_l", true);
					}
				}
			}
		}

		//Player에게 공격받을 시
		if (pGameObj->GetLayerType() == eLayerType::PlayerAttack && m_pAI->GetOwner()->GetName() == L"Hunter")
		{
				int MonsterHPCount = m_pAI->GetOwner()->GetMonsterInfo().iHP_Count;

				MonsterHPCount--;

				pMonster->SetMonsterHPCount(MonsterHPCount);

				float pushForce = 10.f;
				Vector2 Direction = pMonster->GetComponent<Transform>()->GetPostionXY() - pGameObj->GetComponent<Transform>()->GetPostionXY();
				Direction.Normalize();

				pMonster->GetComponent<RigidBody>()->SetVelocity(Direction * pushForce);
				
				pMonster->DamageMonster();
		}

		if (pGameObj->GetLayerType() == eLayerType::PlayerAttack && m_pAI->GetOwner()->GetName() == L"Baldur")
		{
			int MonsterHPCount = m_pAI->GetOwner()->GetMonsterInfo().iHP_Count;

			MonsterHPCount--;

			pMonster->SetMonsterHPCount(MonsterHPCount);

			pMonster->DamageMonster();

		}


		//Player에게 공격받을 시
		if (pGameObj->GetLayerType() == eLayerType::PlayerAttack && m_pAI->GetOwner()->GetName() == L"Grimm")
		{
			
			int MonsterHPCount = m_pAI->GetOwner()->GetMonsterInfo().iHP_Count;

			MonsterHPCount--;

			pMonster->SetMonsterHPCount(MonsterHPCount);
			pMonster->DamageMonster();


			//Vector에서 맞는 이름 찾기 
			std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
			for (const auto& clip : test)
			{
				if (clip->GetKey() == L"GrimmAttack")
				{
					pMonster->GetComponent<AudioSource>()->SetClip(clip);
					pMonster->GetComponent<AudioSource>()->Play();
				}
			}

		}

		if (pGameObj->GetLayerType() == eLayerType::PlayerAttack && m_pAI->GetOwner()->GetName() == L"Radiance")
		{
			int MonsterHPCount = m_pAI->GetOwner()->GetMonsterInfo().iHP_Count;

			MonsterHPCount--;

			pMonster->SetMonsterHPCount(MonsterHPCount);
			pMonster->DamageMonster();

		}

		if (pGameObj->GetLayerType() == eLayerType::PlayerAttack)
		{
			AudioSource* as =  pGameObj->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"MonsterDamage", L"..\\Resources\\Sound\\enemy_damage.mp3"));
			as->Play();
		}

		if (pGameObj->GetLayerType() == eLayerType::Ground)
		{
			m_bCollisionGround = true;
		}



		
	}

	void MonsterScript::OnCollision(Collider2D* _other)
	{
		
	
	}

	void MonsterScript::OnCollisionExit(Collider2D* _other)
	{
		GameObject* pGameObj = _other->GetOwner();

		m_fKnockBackTime = 0.f;

		if (pGameObj->GetLayerType() == eLayerType::Ground)
		{
			m_bCollisionGround = false;
		}
	}

}
