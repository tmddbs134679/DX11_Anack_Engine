#include "AkSkill2State.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkSceneManager.h"
#include "AkCameraScript.h"
#include "AkRigidBody.h"



namespace Ak
{
	Skill2State::Skill2State()
		: MonsterState(eMonsterState::Skill2)
		, m_bSkill2(false)
		, m_bCreateSkillObj01(false)
		, m_bCreateSkillObj02(false)
		, m_bDestorySkillObj(false)
		, m_bDissapear(false)
		, m_bChangeSkill(false)
		, m_bRadianceSkill2Start(true)
		, m_fMoveTime(0.f)
		, m_bRadiance1(true)
		, m_bRadiance2(true)
		, m_bRadiance3(true)
		, m_bRadiance4(true)

	{

	}

	Skill2State::~Skill2State()
	{

	}

	void Skill2State::update()
	{

		
		Monster* pMonster = GetMonster();

		if (m_bSkill2)
		{
		
			static float Skill2Time = 0.f;
			Skill2Time += Time::DeltaTime();

			if (Skill2Time >= 1.f)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Attack_02_02", true);
				m_bSkill2 = false;
				m_bCreateSkillObj01 = true;
				Skill2Time = 0.f;
			}
		}

#pragma region SkillObj

		if (m_bCreateSkillObj01)
		{
			Vector3 vMonPos = pMonster->GetComponent<Transform>()->GetPosition();

			for (int i = 0; i < 11; ++i) {
				Grimm_Projectile_03* GP3 = new Grimm_Projectile_03();
				SceneManager::AddGameObject(eLayerType::MonsterAttack, GP3);
				GP3->GetComponent<Transform>()->SetPosition(Vector3(-15.f + 3.f * i, vMonPos.y - 2.f, 0.9998f));
				GP3->GetComponent<Animator>()->PlayAnimation(L"Attack_03", false);
				m_vSkillObj.push_back(GP3);
			}


			m_bCreateSkillObj01 = false;
			m_bCreateSkillObj02 = true;
		}

		if (m_bCreateSkillObj02)
		{
			static float Skill2Time = 0.f;
			Skill2Time += Time::DeltaTime();

			if (Skill2Time >= 1.f)
			{
				std::vector<std::shared_ptr<AudioClip>> test = pMonster->GetMonsterAC();
				for (const auto& clip : test)
				{
					if (clip->GetKey() == L"grimm_Attack_sharp")
					{
						pMonster->GetComponent<AudioSource>()->SetClip(clip);
						pMonster->GetComponent<AudioSource>()->Play();
					}
				}

				for (int i = 0; i < 11; ++i)
				{
					m_vSkillObj[i]->GetComponent<Animator>()->PlayAnimation(L"Attack_03_02", false);
				}
				m_bCreateSkillObj02 = false;
				m_bDestorySkillObj = true;
				Skill2Time = 0.f;
			}
		}

		if (m_bDestorySkillObj)
		{
			static float Skill2Time = 0.f;
			Skill2Time += Time::DeltaTime();

			if (Skill2Time >= 1.5f)
			{
				for (int i = 0; i < 11; ++i)
				{
					m_vSkillObj[i]->GetComponent<Animator>()->PlayAnimation(L"Attack_03_03", false);
				}

				m_bDestorySkillObj = false;
				m_bDissapear = true;
				Skill2Time = 0.f;
			}
		}

		if (m_bDissapear)
		{
			static float fDisTime = 0.f;
			fDisTime += Time::DeltaTime();

			if (fDisTime >= 1.f)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_disappear", false);
				pMonster->GetMonsterAC()[5]->Play();
				m_bDissapear = false;
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
				GetAI()->ChangeState(eMonsterState::Skill4);
				fChTime = 0.f;
			}

		}

#pragma endregion

#pragma region Radiance


		if (pMonster->GetName() == L"Radiance")
		{
			//초기 시작
			if (m_bRadianceSkill2Start)
			{
				if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_start2"
					&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
				{
					pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);
					m_bRadianceSkill2Start = false;
				}
			}
			else
			{

				m_fMoveTime += Time::DeltaTime();


				if (m_fMoveTime >= 5.f)
				{
					if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_attack"
						&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
					{
						pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_dis", false);
						//m_fMoveTime = 0.f;
					}
				}

			}


			//Radiance 순간이동 
			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_dis"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start", false);
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(RandomX(2), RandomY()));
			}

			if (pMonster->GetComponent<Animator>()->GetPlayAnimationName() == L"Radiance_start"
				&& pMonster->GetComponent<Animator>()->GetAnimation()->isComplete())
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_attack", true);
				m_fMoveTime = 0.f;
			}


			//공격 패턴
			//rp01(창 공격), rp04-01(좌우 레이저공격), rp04-02(보스 중앙 레이저공격), rp02(원 공격)

			if (!(pMonster->GetRadianceAttack01()->GetAttack()))
			{
				if (m_bRadiance1)
				{
					pMonster->GetRadianceAttack04_01()->AttackOn();
					m_bRadiance1 = false;
				}

				if (!(pMonster->GetRadianceAttack04_01()->GetAttack()))
				{
					if (m_bRadiance2)
					{
						pMonster->GetRadianceAttack04_02()->AttackOn();
						m_bRadiance2 = false;
					}


					if (!(pMonster->GetRadianceAttack04_02()->GetAttack()))
					{
						if (m_bRadiance3)
						{
							pMonster->GetRadianceAttack02()->AttackOn();
							m_bRadiance3 = false;
						}

						if (!(pMonster->GetRadianceAttack02()->GetAttackOn()))
						{
							m_bRadiance1 = true;
							m_bRadiance2 = true;
							m_bRadiance3 = true;

							pMonster->GetRadianceAttack01()->ChangePattern();
							pMonster->GetRadianceAttack01()->AttackOn();


						}
					}
				}
			}


			//Next stage

			if (pMonster->GetMonsterInfo().iHP_Count < 30)
			{
				for (auto& test : pMonster->GetMonsterAC())
				{
					if (test->GetKey() == L"Radiance_Scream_short")
					{
						test->Play();
					}
				}
				
				GetAI()->ChangeState(eMonsterState::Skill3);
				
			}



		}







#pragma endregion

	

		MonsterState::update();
	}

	void Skill2State::Enter()
	{
		Monster* pMonster = GetMonster();

		if (pMonster->GetName() == L"Grimm")
		{
			if (pMonster->GetDir() == -1)
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Attack_02_01", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x + 10.f, -3.f));
				m_bSkill2 = true;
			}
			else
			{
				pMonster->GetComponent<Animator>()->PlayAnimation(L"Grimm_Attack_02_01", false);

				GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
				Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();

				float MonsterY = pMonster->GetComponent<Transform>()->GetPosition().y;
				pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(vPlayerPos.x - 10.f, -3.f));
				m_bSkill2 = true;
			}

		}

		if (pMonster->GetName() == L"Radiance")
		{
			pMonster->GetComponent<Transform>()->SetPositionXY(Vector2(RandomX(2), RandomY()));
			pMonster->GetComponent<Animator>()->PlayAnimation(L"Radiance_start2", false);
			
			pMonster->GetRadianceAttack01()->AttackOn();
	
		}

	}

	void Skill2State::Exit()
	{

		Monster* pMonster = GetMonster();
		Vector3 vMonsterPos = pMonster->GetComponent<Transform>()->GetPosition();

		GameObject* pPlayer = pMonster->GetScene()->GetPlayer();
		Vector3	vPlayerPos = pPlayer->GetComponent<Transform>()->GetPosition();


		m_vSkillObj.clear();

		if (vMonsterPos.x > vPlayerPos.x)
		{
			pMonster->SetDir(-1);
		}
		else
		{
			pMonster->SetDir(1);
		}
		 m_bSkill2 = false;
		 m_bCreateSkillObj01 = false;
		 m_bCreateSkillObj02 = false;
		 m_bDestorySkillObj = false;

		 m_bDissapear = false;
		 m_bChangeSkill = false;

		
	}
}