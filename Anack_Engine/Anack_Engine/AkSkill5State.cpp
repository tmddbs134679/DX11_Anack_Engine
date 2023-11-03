#include "AkSkill5State.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkMonsterScript.h"


namespace Ak
{
	Skill5State::Skill5State()
		: MonsterState(eMonsterState::Skill5)
	{
		m_bSkill[0] = false;
		m_bSkill[1] = false;
		m_bSkill[2] = false;
		m_bSkill[3] = false;
	}

	Skill5State::~Skill5State()
	{

	}

	void Skill5State::update()
	{
		

		Monster* pMonster = GetMonster();

		if (m_bSkill[0])
		{
			static float fSkillTime = 0.f;

			fSkillTime += Time::DeltaTime();

			
			if (fSkillTime >= 0.3f)
			{
				if (pMonster->GetDir() == -1)
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_01_l", false);
				}
				else
				{ 
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_01_r", false);
				}
				fSkillTime = 0.f;
				m_bSkill[0] = false;
				m_bSkill[1] = true;
				
			}
		}

		if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Skill5_01_r"
			|| pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Skill5_01_l")
		{
			if (m_bSkill[1])
			{
				if (pMonster->GetDir() == -1)
				{
					Vector3 vMonPos = pMonster->GetComponent<Transform>()->GetPosition();

					float fUpdate = vMonPos.x - 0.008f;
					pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fUpdate, vMonPos.y));
				}
				else
				{
					Vector3 vMonPos = pMonster->GetComponent<Transform>()->GetPosition();

					float fUpdate = vMonPos.x + 0.008f;
					pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fUpdate, vMonPos.y));
				}

				static float fSkillTime = 0.f;

				fSkillTime += Time::DeltaTime();

				if (fSkillTime >= 0.5f)
				{
				
					if (pMonster->GetDir() == -1)
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_03_l", false);
					}
					else
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_03_r", false);
					}

					fSkillTime = 0.f;
					m_bSkill[1] = false;
					m_bSkill[2] = true;

				}
			}
			MonsterState::update();
		}

		if (m_bSkill[2])
		{

			if (pMonster->GetDir() == -1)
			{
				Vector3 vMonPos = pMonster->GetComponent<Transform>()->GetPosition();

				float fUpdateX = vMonPos.x - 0.002f;
				float fUpdateY = vMonPos.y + 0.008f;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fUpdateX, fUpdateY));
			}
			else
			{
				Vector3 vMonPos = pMonster->GetComponent<Transform>()->GetPosition();

				float fUpdateX = vMonPos.x + 0.002f;
				float fUpdateY = vMonPos.y + 0.008f;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fUpdateX, fUpdateY));
			}

			static float fDisTime = 0.f;

			fDisTime += Time::DeltaTime();

			if (fDisTime >= 0.7f)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_disappear", false);
				pMonster->GetMonsterAC()[5]->Play();
				m_bSkill[2] = false;
				m_bSkill[3] = true;
				fDisTime = 0.f;
			}
		}

		if (m_bSkill[3])
		{
			static float fChangeSkillTime = 0.f;

			fChangeSkillTime += Time::DeltaTime();

			if (fChangeSkillTime >= 0.3f)
			{
				GetAI()->ChangeState(eMonsterState::Skill3);
				fChangeSkillTime = 0.f;
			}
		
		}

	}

	void Skill5State::Enter()
	{
			Monster* pMonster = GetMonster();

			if (pMonster->GetDir() == -1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_01_ready_l", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x + 5.f, MonsterY));
				m_bSkill[0] = true;
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill5_01_ready_r", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x - 5.f, MonsterY));
				m_bSkill[0] = true;
			}

		

	}

	void Skill5State::Exit()
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
		 m_bSkill[2] = false;
		 m_bSkill[3] = false;
	}


}