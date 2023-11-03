#include "AkIdleState.h"
#include "AkTime.h"
#include "func.h"
#include "AkPlayerScript.h"
#include "AkRigidBody.h"
#include "AkTransform.h"
#include "AkMonster.h"
#include "AkPlayer.h"
#include "AkScene.h"
#include "AkAI.h"
#include "AkBaldur.h"
#include "AkGrimm.h"
#include "AkBossTriggerScript.h"


namespace Ak
{
	IdleState::IdleState()
		: MonsterState(eMonsterState::Idle)
		, m_fCurTime(0.f)
		, m_fTime(2.f)
		, m_bhit(false)
		, m_fHunterTime(0)
		, m_bHunterRand(false)
	
	{
	
	}

	IdleState::~IdleState()
	{

	}

	void IdleState::update()
	{
		

		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();

		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

		//범위 감지를 위한 거리 차이
		Vector3 vDiff = vPlayerPos - vMonsterPos;
		float fLen = vDiff.Length();



		//벽에 충돌되기 전까지 정해진 방향으로 계속 이동 함수
		////Hunter Idle random patrol
		if (pMonster->GetName() == L"Hunter")
		{
			int MonX = GetAI()->GetOwner()->GetMonsterDirX();
			int MonY = GetAI()->GetOwner()->GetMonsterDirY();

				float fMoveX = 0.f;
				fMoveX += MonX * Time::DeltaTime();

				float fMoveY = 0.f;
				fMoveY += MonY * Time::DeltaTime();

				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vMonsterPos.x + fMoveX, vMonsterPos.y + fMoveY));

				//MonsterState::update();
		}

		//Detect 범위 감지
		if (fLen < pMonster->GetMonsterInfo().fDetectRange)
		{
			if (pMonster->GetName() == L"Baldur")
			{
				GetAI()->ChangeState(eMonsterState::AttackStart);
			}

			 if(pMonster->GetName() == L"Hunter")
			{
				GetAI()->ChangeState(eMonsterState::Trace);
			}
		}

		if (pMonster->GetName() == L"Grimm")
		{
			//BossTrigger에 들어왔을 때 
			if (pMonster->GetBossTrigger()->GetComponent<BossTriggerScript>()->GetTriggerState())
			{
				GetAI()->ChangeState(eMonsterState::AttackStart);
			}
		}

		if (pMonster->GetName() == L"Radiance")
		{
			//애니메이션 끝낫을 경우 넘어가기
			if (pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				//GetAI()->ChangeState(eMonsterState::AttackStart);
			}
		}


		MonsterState::update();

	}

	void IdleState::Enter()
	{
		
		//Hunter Random dir setting

		Monster* pMonster = GetAI()->GetOwner();

		int randomX = RandomDir();
		int randomY = RandomDir();

		pMonster->SetMonsterDirX(randomX);
		pMonster->SetMonsterDirY(randomY);
		
		
		pMonster->SetMonsterState(eMonsterState::Idle);

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

		if (pMonster->GetName() == L"Grimm")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_idle", true);
		}

		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start2", false);
			pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(0.f, -50.8f));
		}



		if (pMonster->GetName() == L"Hunter")
		{
			pMonster->GetMonsterAC()[2]->Play();

		}
	}

	void IdleState::Exit()
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

	
	}



}
