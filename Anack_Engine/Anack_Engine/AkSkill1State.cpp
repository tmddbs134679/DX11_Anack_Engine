#include "AkSkill1State.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkGrimm_Projectile_01.h"
#include "AkRP03_OBj.h"

namespace Ak
{
	Skill1State::Skill1State()
		: MonsterState(eMonsterState::Skill1)
		, m_bChangeSkill(false)
		, m_bEndSkill(false)
		, m_bRadiacneAttack(true)
		, m_bAttack03Change(false)
		, m_RP3InIt(true)
		, m_fMoveTime(0.f)
	{
		Attack01Cnt = 0;
	}
	Skill1State::~Skill1State()
	{

	}

	void Skill1State::update()
	{
		
		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();


		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

		if (pMonster->GetName() == L"Grimm")
		{
			//Attack Skill1번 공격
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Attack_01_start"
				|| pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Attack_01_start_r")
			{

				static float fAttackTime = 0.f;
				fAttackTime += Time::DeltaTime();

				

				if (fAttackTime >= 0.7f)
				{
					 
					if (Attack01Cnt < 3)
					{
						Vector3 vPos = pMonster->GetComponent<Transform>()->GetPosition();

						if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Attack_01_start")
						{
							
							std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
							for (const auto& clip : test)
							{
								if (clip->GetKey() == L"Grimm_fireBall")
								{
									pMonster->GetComponent<AudioSource>()->SetClip(clip);
									pMonster->GetComponent<AudioSource>()->Play();
								}
							}

							Grimm_Projectile_01* GP = new Grimm_Projectile_01();
							SceneManager::AddGameObject(eLayerType::MonsterAttack, GP);
							GP->GetComponent<Transform>()->SetPosition(Vector3(vPos.x - 1.f, vPos.y - 1.f, vPos.z));
							GP->ChoosesAnim(-1);
							fAttackTime = 0.f;
							Attack01Cnt++;
							
						}
						else if(pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Grimm_Attack_01_start_r")
						{

							std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
							for (const auto& clip : test)
							{
								if (clip->GetKey() == L"Grimm_fireBall")
								{
									pMonster->GetComponent<AudioSource>()->SetClip(clip);
									pMonster->GetComponent<AudioSource>()->Play();
								}
							}

							Grimm_Projectile_01* GP = new Grimm_Projectile_01();
							SceneManager::AddGameObject(eLayerType::MonsterAttack, GP);
							GP->GetComponent<Transform>()->SetPosition(Vector3(vPos.x + 1.f, vPos.y - 1.f, vPos.z));
							GP->ChoosesAnim(1);
							fAttackTime = 0.f;
							Attack01Cnt++;
						}
					
					}
					else
					{
						m_bEndSkill = true;
					}
					
				}
			}

			if (m_bEndSkill)
			{
				static float Skill1EndTime = 0.f;
 				Skill1EndTime += Time::DeltaTime();

				if (Skill1EndTime >= 1.5f)
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_disappear", false);
					pMonster->GetMonsterAC()[5]->Play();
					m_bEndSkill = false;
					m_bChangeSkill = true;
					Skill1EndTime = 0.f;
				}
			}

			if (m_bChangeSkill)
			{
				static float Skill1EndTime = 0.f;
				Skill1EndTime += Time::DeltaTime();

				if (Skill1EndTime >= 1.f)
				{
					GetAI()->ChangeState(eMonsterState::Skill2);
					Skill1EndTime = 0.f;
				}
			}
		}

		/////Radiance//////
		if (pMonster->GetName() == L"Radiance")
		{
			//초기 시작
			if (m_bRadiacneAttack)
			{
				if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_start2"
					&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);
					m_bRadiacneAttack = false;
				}
			}
			else
			{

				m_fMoveTime += Time::DeltaTime();


				if (m_fMoveTime >= 8.f)
				{
					if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_attack"
						&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_dis", false);
						m_fMoveTime = 0.f;
					}
				}

			}



			//Radiance 순간이동 
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_dis"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start", false);
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(RandomX(1), 2.8f));
			}

			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_start"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);
			}


			if (pMonster->GetMonsterInfo().iHP_Count < 70)
			{
			 	GetAI()->ChangeState(eMonsterState::Skill4);
			}



			//공격
			if (!pMonster->GetRadianceAttack01()->GetAttack())
			{
				pMonster->GetRadianceAttack01()->ChangePattern();
			
				if (pMonster->GetRadianceAttack01()->GetPatternI() == 2)
				{
					pMonster->GetRadianceAttack02()->AttackOn();
				}
				else
				{
					pMonster->GetRadianceAttack01()->AttackOn();

				}
			}
			
		}

		
		MonsterState::update();

	}

	void Skill1State::Enter()
 	{
		Monster* pMonster = GetMonster();

		pMonster->SetMonsterState(eMonsterState::Skill1);

		if (pMonster->GetName() == L"Grimm")
		{
			if (pMonster->GetDir() == -1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Attack_01_start", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x + 10.f, -3.f));
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Attack_01_start_r", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x - 10.f, -3.f));
			}

		}

		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(RandomX(1), 2.8f));
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start2", false);



			if (m_RP3InIt)
			{
				pMonster->GetRadianceAttack03()->Initialize();
				pMonster->GetRadianceAttack03()->ChangePattern();
				std::vector<Radiance_Projectile_03*> rp3 = pMonster->GetRadianceAttack03()->GetRP3();

				for (const auto& test : rp3)
				{
					test->AttackOn();
				}
				m_RP3InIt = false;
			}
		

			pMonster->GetRadianceAttack01()->Initialize();
			pMonster->GetRadianceAttack01()->AttackOn();

			pMonster->GetRadianceAttack02()->Initialize();
			pMonster->GetRadianceAttack04_01()->Initialize();
			pMonster->GetRadianceAttack04_01()->GetComponent<Transform>()->SetPositionXY(Vector2(-40.f, -1.f));
			pMonster->GetRadianceAttack04_02()->Initialize();
		}

	}

	void Skill1State::Exit()
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

		m_bChangeSkill = false;
		m_bEndSkill = false;
		Attack01Cnt = 0;


	}



}