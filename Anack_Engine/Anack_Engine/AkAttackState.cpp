#include "AkAttackState.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkRigidBody.h"

namespace Ak
{
	AttackState::AttackState()
		: MonsterState(eMonsterState::Attack)
		, m_PreColliderSize(Vector2(Vector2::Zero))
	{
	
	}

	AttackState::~AttackState()
	{

	}

	void AttackState::update()
	{

		//MonsterState::update();

		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();


		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

		float vDistanceX = vPlayerPos.x - vMonsterPos.x;
		float vDistanceY = vPlayerPos.y - vMonsterPos.y;

		if (pMonster->GetName() == L"Baldur")
		{
			vMonsterPos.x += vDistanceX * pMonster->GetMonsterInfo().fSpeed * Time::DeltaTime();

			GetMonster()->GetComponent<Transform>()->SetPosition(vMonsterPos);

			float fDiffx = abs(vPlayerPos.x - vMonsterPos.x);

			if (fDiffx >= pMonster->GetMonsterInfo().fDetectRange)
			{
				GetAI()->ChangeState(eMonsterState::Idle);
			}

		}

		if (pMonster->GetName() == L"Hunter")
		{
			
			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				GetAI()->ChangeState(eMonsterState::Death);

				return;
			}

			float fDiffx = abs(vPlayerPos.x - vMonsterPos.x);
			float fDiffy = abs(vPlayerPos.y - vMonsterPos.y);


			if ((fDiffx > pMonster->GetMonsterInfo().fAttackRange || fDiffy > pMonster->GetMonsterInfo().fAttackRange))
				
			{
				GetAI()->ChangeState(eMonsterState::Trace);
			}

			
		}
		


		//MonsterState::update();
	}

	void AttackState::Enter()
	{
		Monster* pMonster = GetMonster();

		pMonster->SetMonsterState(eMonsterState::Attack);

		if (pMonster->GetName() == L"Baldur")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Baldur_Attack", true);

			m_PreColliderSize = pMonster->GetComponent<Collider2D>()->GetSize();

			pMonster->GetComponent<Collider2D>()->SetSize(Vector2(0.35f, 0.35f));
		}

		if (pMonster->GetName() == L"Hunter")
		{
			if (pMonster->GetDir() == -1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Attack_l", true);
			}
			else
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Attack_r", true);
		}
		
	}

	void AttackState::Exit()
	{
		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();

		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();


		if (pMonster->GetName() == L"Baldur")
		{
			//Collider 사이즈 조절
			pMonster->GetComponent<Collider2D>()->SetSize(m_PreColliderSize);
		}

		////Attack 경계에 들어왔을 때 Monster 방향 Setting
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
