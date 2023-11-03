#include "AkTraceState.h"
#include "AkMonster.h"
#include "AkTime.h"
#include "AkAI.h"
#include "AkAnimator.h"

namespace Ak
{
	TraceState::TraceState()
		: MonsterState(eMonsterState::Trace)
		, m_fTraceSound(0.f)
	{

	}

	TraceState::~TraceState()
	{

	}

	void TraceState::update()
	{
	
		
		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();

		//Scene* CurScene = pMonster->GetScene();

		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

		float vDistanceX = vPlayerPos.x - vMonsterPos.x;
		float vDistanceY = vPlayerPos.y - vMonsterPos.y;

		if (pMonster->GetName() == L"Hunter")
		{
		
			vMonsterPos.x += vDistanceX * pMonster->GetMonsterInfo().fSpeed * Time::DeltaTime();
			vMonsterPos.y += vDistanceY * pMonster->GetMonsterInfo().fSpeed * Time::DeltaTime();


			GetMonster()->GetComponent<Transform>()->SetPositionXY(Vector2(vMonsterPos.x, vMonsterPos.y));

			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				GetAI()->ChangeState(eMonsterState::Death);

				return;
			}

			float vDiffx = abs(vPlayerPos.x - vMonsterPos.x);

			if (vDiffx >= pMonster->GetMonsterInfo().fDetectRange)
			{
				GetAI()->ChangeState(eMonsterState::Idle);
			}

			if (vDiffx <= pMonster->GetMonsterInfo().fAttackRange)
			{
				GetAI()->ChangeState(eMonsterState::Attack);
			}

			

		}

		if (pMonster->GetName() == L"Baldur")
		{
			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				GetAI()->ChangeState(eMonsterState::Death);

				return;
			}
		}

		if (pMonster->GetName() == L"Hunter")
		{
			m_fTraceSound += Time::DeltaTime();

			if (m_fTraceSound >= 0.3f)
			{
				m_fTraceSound = 0.f;
			}

		}
	
	}

	void TraceState::Enter()
	{
		Monster* pMonster = GetMonster();

		pMonster->SetMonsterState(eMonsterState::Trace);

		if (pMonster->GetDir() == 1)
		{
			if (pMonster->GetName() == L"Hunter")
			{
 				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Detect_r", true);
			}
		}
		else
		{
			if (pMonster->GetName() == L"Hunter")
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Hunter_Detect_l", true);
			}
		}

		if (pMonster->GetName() == L"Hunter")
		{

			if(m_fTraceSound <=0.f)
			pMonster->GetMonsterAC()[1]->Play();
			pMonster->GetMonsterAC()[2]->Stop();
		}
	}

	void TraceState::Exit()
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
