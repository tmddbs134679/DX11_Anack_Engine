#include "AkRP01_Obj.h"
#include "AkTime.h"
#include "AkSceneManager.h"
#include "AkTime.h"

namespace Ak
{
	RP01_Obj::RP01_Obj()
		: m_fTime03(0.f)
		, radius(3.f)
		, angleStep(360.0f / 12)
		, AttackCNT(0)
		, m_fPatternEndTime(0.f)
		, m_bParrernEnd(false)
		, m_bAttack(false)
	{
		m_vRandoms.resize(8);
	}

	RP01_Obj::~RP01_Obj()
	{
		SceneManager::DestoryObj(this);

		for (const auto& test : m_vRP)
		{
			SceneManager::DestoryObj(test);
			delete test;
		}

		m_vRP.clear();
	}

	void RP01_Obj::Initialize()
	{

		

		for (int i = 0; i < 8; ++i) 
		{
			m_vRandoms[i] = i;
		}

		Suffle();

		m_EPattern = pattern01;


		Radiance_Proejctile_01* RP01 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP02 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP03 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP04 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP05 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP06 = new Radiance_Proejctile_01();
		
		Radiance_Proejctile_01* RP07 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP08 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP09 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP10 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP11 = new Radiance_Proejctile_01();

		Radiance_Proejctile_01* RP12 = new Radiance_Proejctile_01();


		m_vRP.push_back(RP01);
		m_vRP.push_back(RP02);
		m_vRP.push_back(RP03);
		m_vRP.push_back(RP04);
		m_vRP.push_back(RP05);
		m_vRP.push_back(RP06);
		m_vRP.push_back(RP07);
		m_vRP.push_back(RP08);
		m_vRP.push_back(RP09);
		m_vRP.push_back(RP10);
		m_vRP.push_back(RP11);
		m_vRP.push_back(RP12);

		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP01);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP02);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP03);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP04);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP05);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP06);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP07);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP08);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP09);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP10);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP11);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP12);


		m_fPattern01 = -20.f;
		m_fPattern02 = 20.f;
		m_fPattern03 = 20.f;
	}

	void RP01_Obj::Update()
	{

		if (m_bAttack)
		{
			Vector3 pos = m_Owner->GetComponent<Transform>()->GetPosition();

			static float fTime = 0.f;
			fTime += Time::DeltaTime();

			switch (m_EPattern)
			{

			case Ak::RP01_Obj::pattern01:


				if (AttackCNT < 3)
				{
					std::vector<int> selectedRandoms(m_vRandoms.begin(), m_vRandoms.begin() + 3);

					//왼쪽 -> 오른쪽 공격 
					for (int i = 0; i < 12; ++i)
					{

						m_fPattern01 += 0.0015f;
						if (i < 8)
						{

							if (std::find(selectedRandoms.begin(), selectedRandoms.end(), i) == selectedRandoms.end())
							{
								// selectedRandoms 벡터에 'i'가 없는 경우에 수행할 작업
								m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_fPattern01, pos.y - (i * 1.5f) + 50.f, 1.f));
							}
							else
							{
								// selectedRandoms 벡터에 'i'가 포함된 경우에 수행할 작업
								m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_fPattern01, pos.y - (i * 1.5f) + 5.f, 1.f));
							}
						}
						else
						{
							m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_fPattern01, pos.y - (i * 1.5f) + 50.f, 1.f));
						}

						m_vRP[i]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 1.55f));

						if (m_fPattern01 >= 20.f)
						{
							m_fPattern01 = -20.f;
							AttackCNT++;
						}
					}
				}
				else
				{
					m_fPatternEndTime += Time::DeltaTime();

					if (m_fPatternEndTime >= 2.f)
					{
						m_bParrernEnd = true;
						m_bAttack = false;
					}
				}
				break;

			case Ak::RP01_Obj::pattern02:


				if (AttackCNT < 3)
				{
					std::vector<int> selectedRandoms(m_vRandoms.begin(), m_vRandoms.begin() + 3);

					//오른쪽 -> 왼쪽 공격 
					for (int i = 0; i < 12; ++i)
					{

						m_fPattern02 -= 0.0015f;
						if (std::find(selectedRandoms.begin(), selectedRandoms.end(), i) == selectedRandoms.end())
						{
							// selectedRandoms 벡터에 'i'가 없는 경우에 수행할 작업
							m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_fPattern02, pos.y - (i * 1.5f) + 50.f, 1.f));
						}
						else
						{
							// selectedRandoms 벡터에 'i'가 포함된 경우에 수행할 작업
							m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_fPattern02, pos.y - (i * 1.5f) + 5.f, 1.f));
						}

						m_vRP[i]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, -1.55f));

						if (m_fPattern02 <= -20.f)
						{
							m_fPattern02 = 20.f;
							AttackCNT++;
						}
					}
				}
				else
				{
					m_fPatternEndTime += Time::DeltaTime();

					if (m_fPatternEndTime >= 2.f)
					{
						m_bParrernEnd = true;
						m_bAttack = false;
					}
				}
				break;

			case Ak::RP01_Obj::pattern03:

				if (AttackCNT < 3)
				{
					std::vector<int> selectedRandoms(m_vRandoms.begin(), m_vRandoms.begin() + 3);

					for (int i = 0; i < 12; ++i)
					{
						m_fPattern03 -= 0.0015f;

						if (std::find(selectedRandoms.begin(), selectedRandoms.end(), i) == selectedRandoms.end())
						{
							m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(-10.f + i * 2.f, pos.y + m_fPattern03, 1.f));
						}
						else
						{
							m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(-50.f + i * 2.f, pos.y + m_fPattern03, 1.f));
						}

						m_vRP[i]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.f));
					}

					if (pos.y + m_fPattern03 < pos.y - 20)
					{
						m_fPattern03 = 20.f;
						AttackCNT++;
					}

				}
				else
				{
					m_fPatternEndTime += Time::DeltaTime();

					if (m_fPatternEndTime >= 2.f)
					{
						m_bParrernEnd = true;
						m_bAttack = false;
					}
				}
				break;

			case Ak::RP01_Obj::pattern04:

				m_fTime03 += Time::DeltaTime();

				if (m_fTime03 <= 2)
				{
					for (int i = 0; i <= 11; ++i)
					{
						radius = 3.f;

						angleStep = 360.0f / 12;

						angle = i * angleStep;
						radians = angle * (3.141592f / 180.f);

						x = radius * std::cos(radians);
						y = radius * std::sin(radians);

						m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(pos.x + x, pos.y + 1.5 + y, 1.f));

					}
				}
				else if (m_fTime03 > 2.f)
				{
					static Vector3 vPlayerPos = m_Player->GetComponent<Transform>()->GetPosition();
					static Vector3 vMonPos = m_vRP[0]->GetComponent<Transform>()->GetPosition();

					int dir = 0;
					if (vPlayerPos.x - vMonPos.x < 0)
					{
						dir = -1;
					}
					else
					{
						dir = 1;
					}

					for (int i = 0; i <= 11; ++i)
					{

						static float testTime = 0.f;

						testTime += Time::DeltaTime();

						if (testTime <= 1.f)
						{
							m_vRP[i]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, testTime * -0.6f));
						}
					}


					//if (m_fTime03 >= 3.f)
					//{
					//	for (int i = 0; i <= 11; ++i)
					//	{
					//		radius = 3.f;

					//		angleStep = 360.0f / 12;

					//		angle = i * angleStep;
					//		radians = angle * (3.141592f / 180.f);

					//		x = radius * std::cos(radians);
					//		y = radius * std::sin(radians);

					//		m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(pos.x + x - m_fTime03 * 4, pos.y + 1.5 + y - m_fTime03 * 4, 1.f));

					//	}
					//}

				}

				break;
			default:
				break;
			}

		}
		else
		{
			for (auto& test : m_vRP)
			{
				test->GetComponent<Transform>()->SetPositionXY(Vector2(-40.f, 0.f));
				AttackCNT = 0;
			}
		}
	

		GameObject::Update();
	}

	void RP01_Obj::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RP01_Obj::Render()
	{
		GameObject::Render();
	}
	Vector2 RP01_Obj::RP01_CalculateDirection(float _angle)
	{
		// 각도를 라디안으로 변환 (라디안 = 각도 * (π / 180))
		float radians = _angle * (3.14159265359f / 180.0f);

		// 방향 벡터 계산 (사인과 코사인을 사용)
		float x = std::cos(radians); // x 방향
		float y = std::sin(radians); // y 방향

		return math::Vector2(x, y); // 방향 벡터 반환
	}

	void RP01_Obj::Suffle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::shuffle(m_vRandoms.begin(), m_vRandoms.end(), gen);

		m_vRandoms;

	}
}