#include "AkRP04_Obj02.h"
#include "AkSceneManager.h"
#include "AkTime.h"
#include "AkResources.h"


namespace Ak
{
	RP04_Obj02::RP04_Obj02()
		: m_bAttack(false)
		, m_iAttackCnt(0)
		, m_bACPre0(true)
		, m_bACBeam0(true)
		, m_bACPre1(true)
		, m_bACBeam1(true)
		, fTime(0.f)
		, m_bSound(true)
	{

	}

	RP04_Obj02::~RP04_Obj02()
	{
		SceneManager::DestoryObj(this);
		for (const auto& test : m_vRP)
		{
			SceneManager::DestoryObj(test);
			delete test;

		}

		m_vRP.clear();
	}

	void RP04_Obj02::Initialize()
	{


		//beam 2
		float x = 0.4f;
		Radiance_Projectile_04* PJ4_01 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_01);
		PJ4_01->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 1));
		PJ4_01->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);
		

		Radiance_Projectile_04* PJ4_02 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_02);
		PJ4_02->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 2));
		PJ4_02->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_03 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_03);
		PJ4_03->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 3));
		PJ4_03->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_04 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_04);
		PJ4_04->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 4));
		PJ4_04->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_05 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_05);
		PJ4_05->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 5));
		PJ4_05->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_06 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_06);
		PJ4_06->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 6));
		PJ4_06->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_07 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_07);
		PJ4_07->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 7));
		PJ4_07->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_08 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_08);
		PJ4_08->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, x * 8));
		PJ4_08->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);


		m_vRP.push_back(PJ4_01);
		m_vRP.push_back(PJ4_02);
		m_vRP.push_back(PJ4_03);
		m_vRP.push_back(PJ4_04);
		m_vRP.push_back(PJ4_05);
		m_vRP.push_back(PJ4_06);
		m_vRP.push_back(PJ4_07);
		m_vRP.push_back(PJ4_08);

		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_01);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_02);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_03);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_04);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_05);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_06);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_07);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_08);
	}

	void RP04_Obj02::Update()
	{
		if (!m_vRP.empty())
		{

			if (m_bAttack)
			{

				for (auto test : m_vRP)
				{
					Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();

					test->GetComponent<Transform>()->SetPosition(Vector3(monpos.x, monpos.y + 1.2f, 1.3f));
				}


				
				fTime += Time::DeltaTime();

				int interval = 3;  // 0.3초 간격으로 변경
				int animationIndex = static_cast<int>(floor(fTime / interval)) % 2;
				float animationTime = fTime - (interval * animationIndex);

				std::wstring beamAnimation = L"attack04_beam";
				std::wstring beamdis = L"attack04_dis";
				std::wstring beamready = L"attack04_001";
				std::wstring beamEmpty = L"attack04_emp";


				//짝수 초
				if (animationIndex == 0)
				{
					for (int i = 0; i < 8; ++i)
					{
						// 짝수 오브젝트
						if (i % 2 == 0)
						{

							if (animationTime < 0.2f)
							{

								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_001"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamready, true);

								}

							}
							else if (animationTime >= 0.2f && animationTime < 0.4f)
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_beam"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamAnimation, false);
									m_vRP[0]->GetAC()[1]->Play();

								}


							}
							else
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamdis, false);


									if ((m_vRP[6]->GetComponent<Animator>()->GetPlayAnimationName() == beamdis))
									{
										++m_iAttackCnt;
									}
								}


							}
						}
						// 홀수 오브젝트
						else
						{
							if (!(m_iAttackCnt == 3))
							{
								if (animationTime < 0.2f)
								{
									if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_emp"))
										m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamEmpty, false);

								}
								else
								{
									if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_001"))
									{
										m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamready, true);
									}
								}
							}
							else
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_emp"))
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamEmpty, false);
							}

						}


					}

				}
				//홀수 초
				else
				{
					for (int i = 0; i < 8; ++i)
					{
						if (i % 2 == 1)
						{
							// 홀수 오브젝트
							if (animationTime < 0.2f)
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_001"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamready, true);
								}


							}
							else if (animationTime >= 0.2f && animationTime < 0.4f)
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_beam"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamAnimation, false);
									m_vRP[1]->GetAC()[1]->Play();

								}

							}
							else
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamdis, false);


									if ((m_vRP[7]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"))
									{
										++m_iAttackCnt;

									}
								}
							}
						}
						else
						{
							// 짝수 오브젝트
							if (!(m_iAttackCnt == 3))
							{
								if (animationTime < 0.2f)
								{
									if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_emp"))
										m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamEmpty, false);

								}
								else
								{
									if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_001"))
									{
										m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamready, true);

									}
								}
							}
							else
							{
								if (!(m_vRP[i]->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_emp"))
								{
									m_vRP[i]->GetComponent<Animator>()->PlayAnimation(beamEmpty, false);

								}

							}
						}
					}

				}

				if (m_iAttackCnt == 3)
				{
					if (m_bSound)
					{
						m_vRP[0]->GetAC()[1]->Play();
						m_bSound = false;
					}
					
					
				}

				if (m_iAttackCnt >= 4)
				{
					
					m_iAttackCnt = 0;
					m_bAttack = false;
					m_bACBeam0 = true;
					m_bSound = true;
				}
			}
			else
			{
				for (auto test : m_vRP)
				{
					if (!(test->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_emp"))
					{
						test->GetComponent<Animator>()->PlayAnimation(L"attack04_emp", false); 
					}
				}
				
				fTime = 0.f;

			}


	
		
		}
	}

	void RP04_Obj02::LateUpdate()
	{
		
	}

	void RP04_Obj02::Render()
	{

	}
}