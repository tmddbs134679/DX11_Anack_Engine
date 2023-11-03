#include "AkSkill4State.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkMonsterScript.h"
#include "AkRigidBody.h"
#include "AkRG_Long.h"
#include "AkRG_Short.h"


namespace Ak
{
	Skill4State::Skill4State()
		: MonsterState(eMonsterState::Skill4)
		, m_bSkill04_02(false)
		, m_bSkill04_03(false)
		, m_bSkill04Ch(false)
		, m_bSkillDis(false)
		, m_bReskill04_02(false)
		, m_bSkill04_01(false)
	{

	}

	Skill4State::~Skill4State()
	{

	}

	void Skill4State::update()
	{
		

		Monster* pMonster = GetMonster();

		if (pMonster->GetName() == L"Grimm")
		{
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Skill4_01")
			{


				if (!pMonster->GetComponent<MonsterScript>()->bCollisionGround())
				{

					GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
					Vector2 vMonPos = pMonster->GetComponent<Transform>()->GetPostionXY();
					Vector2 vPlayerPosXY = pPlayer->GetComponent<Transform>()->GetPostionXY();




					if (vMonPos.x - vPlayerPosXY.x < 0)
					{
						static Vector2 normalizePos = vMonPos - vPlayerPosXY;

						float MonUpdatePosX = pMonster->GetComponent<Transform>()->GetPosition().x - normalizePos.x * 0.001f;
						float MonUpdatePosY = pMonster->GetComponent<Transform>()->GetPosition().y - normalizePos.y * 0.001f;


						pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(MonUpdatePosX, MonUpdatePosY));

						//기울이기
						static float fChTime = 0.f;
						fChTime += Time::DeltaTime();

						if (fChTime >= 0.3f)
						{
							pMonster->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.6f));
							fChTime = 0.f;
						}
					}
					else
					{
						static Vector2 normalizePos = vMonPos - vPlayerPosXY;

						float MonUpdatePosX = pMonster->GetComponent<Transform>()->GetPosition().x - normalizePos.x * 0.001f;
						float MonUpdatePosY = pMonster->GetComponent<Transform>()->GetPosition().y - normalizePos.y * 0.001f;

						pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(MonUpdatePosX, MonUpdatePosY));

						//기울이기
						static float fChTime = 0.f;
						fChTime += Time::DeltaTime();

						if (fChTime >= 0.3f)
						{
							pMonster->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, -0.6f));
							fChTime = 0.f;
						}

					}

				}
				else
				{
					pMonster->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.f));
					m_bSkill04_02 = true;

				}
			}

			if (m_bSkill04_02)
			{
				if (pMonster->GetDir() == -1)
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_02_r", false);
				}
				else
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_02", false);
				}
				m_bSkill04_03 = true;
				m_bSkill04_02 = false;

			}

			if (m_bSkill04_03)
			{
				static float fChTime = 0.f;
				fChTime += Time::DeltaTime();

				if (fChTime >= 0.5f)
				{
					if (pMonster->GetDir() == -1)
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_03_r", false);
					}
					else
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_03", false);
					}
					fChTime = 0.f;
					m_bSkill04_03 = false;
				}
			}

			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Skill4_03"
				|| pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Skill4_03_r")
			{

				pMonster->GetComponent<Collider2D>()->SetSize(Vector2(0.8f, 0.2f));

				static float fChTime = 0.f;
				fChTime += Time::DeltaTime();

				if (fChTime <= 0.5f)
				{
					Vector2 vMonPos = pMonster->GetComponent<Transform>()->GetPostionXY();
					if (pMonster->GetDir() == -1)
					{
						float fMonPos = vMonPos.x + 0.008f;
						static float fMonPosY = vMonPos.y - 1.f;
						pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fMonPos, fMonPosY));
					}
					else
					{
						float fMonPos = vMonPos.x - 0.008f;
						static float fMonPosY = vMonPos.y - 1.f;
						pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(fMonPos, fMonPosY));
					}
				}

				if (fChTime >= 0.6f)
				{
					m_bReskill04_02 = true;
					fChTime = 0.f;
				}

			}
			else
			{
				pMonster->GetComponent<Collider2D>()->SetSize(Vector2(0.5f, 1.f));
			}

			if (m_bReskill04_02)
			{
				static float fChTime2 = 0.f;
				fChTime2 += Time::DeltaTime();

				if (fChTime2 <= 0.3f)
				{
					if (pMonster->GetDir() == -1)
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_02", false);
					}
					else
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_02_r", false);
					}

					m_bSkillDis = true;
					m_bReskill04_02 = false;
					fChTime2 = 0.f;
				}
			}

			if (m_bSkillDis)
			{

				static float fdisTime = 0.f;
				fdisTime += Time::DeltaTime();

				if (fdisTime >= 0.3f)
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_disappear", false);
					pMonster->GetMonsterAC()[5]->Play();
					fdisTime = 0.f;
					m_bSkillDis = false;
					m_bSkill04Ch = true;
				}

			}

			if (m_bSkill04Ch)
			{
				static float fchTime = 0.f;
				fchTime += Time::DeltaTime();

				if (fchTime >= 1.f)
				{
					GetAI()->ChangeState(eMonsterState::Skill5);
					m_bSkill04Ch = false;
					fchTime = 0.f;
				}
			}
		}

		if (pMonster->GetName() == L"Radiance")
		{
			//Radiance stage 2
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_lie"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				static float fTime = 0.f;
				fTime += Time::DeltaTime();


				if (fTime <= 3.f)
				{
					//2초전까지 몬스터 흰색 설정 
					if (!pMonster->GetBoolDamageMonster())
						pMonster->DamageMonster();

				}
				else
				{

					pMonster->GetComponent<RigidBody>()->SetGravity(Vector2(0.f, 0.f));
					RG_Long* RL0 = new RG_Long();
					RL0->GetComponent<Transform>()->SetPosition(Vector3(0.f, 1.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RL0);

					RG_Long* RL2 = new RG_Long();
					RL2->GetComponent<Transform>()->SetPosition(Vector3(-7.f, 4.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RL2);

					RG_Long* RL3 = new RG_Long();
					RL3->GetComponent<Transform>()->SetPosition(Vector3(1.f, 11.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RL3);

					RG_Short* RS0 = new RG_Short();
					RS0->GetComponent<Transform>()->SetPosition(Vector3(6.f, 5.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RS0);


					RG_Short* RS2 = new RG_Short();
					RS2->GetComponent<Transform>()->SetPosition(Vector3(9.5f, 10.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RS2);

					RG_Short* RS3 = new RG_Short();
					RS3->GetComponent<Transform>()->SetPosition(Vector3(-9.5f, 9.f, 0.99f));
					SceneManager::AddGameObject(eLayerType::Ground, RS3);


					pMonster->GetComponent<RigidBody>()->SetGravity(Vector2(0.f, 0.f));
					GetAI()->ChangeState(eMonsterState::Skill2);
				}


			}

		}

		MonsterState::update();
	}

	void Skill4State::Enter()
	{
		
		Monster* pMonster = GetMonster();


		if (pMonster->GetName() == L"Grimm")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Skill4_01", false);

			if (pMonster->GetDir() == -1)
			{

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x - 5.f, 3.f));

			}
			else
			{

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x + 5.f, 3.f));

			}
		}
	
		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_lie", false);

			pMonster->GetComponent<RigidBody>()->SetGravity(Vector2(0.f, -70.f));
		}

	}

	void Skill4State::Exit()
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

		pMonster->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.f));

		m_bSkill04_02 = false;
		m_bSkill04_03 = false;
		m_bSkill04Ch = false;
		m_bSkillDis = false;
		m_bReskill04_02 = false;
	


		

		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->AddComponent<RigidBody>()->SetGravity(Vector2::Zero);
		}

	}

}