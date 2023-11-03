#include "AkRP02_Obj.h"
#include "AkSceneManager.h"
#include "AkTime.h"
#include "AkRigidBody.h"

namespace Ak
{
	RP02_Obj::RP02_Obj()
		: m_bAttack(true)
		, m_fTime(0.f)
		, m_bAttackSetting(true)
		, m_bAC(true)
	{

	}

	RP02_Obj::~RP02_Obj()
	{
		SceneManager::DestoryObj(this);

		for (const auto& test : m_vRP)
		{
			SceneManager::DestoryObj(test);
			delete test;

		}

		m_vRP.clear();

	}

	void RP02_Obj::Initialize()
	{
		Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();


		Radiance_Projectile_02* RP01 = new Radiance_Projectile_02();
		RP01->GetComponent<Transform>()->SetPosition(Vector3(monpos.x + 3.5f, monpos.y + 1.f, 1.f));

		

		Radiance_Projectile_02* RP02 = new Radiance_Projectile_02();
		RP02->GetComponent<Transform>()->SetPosition(Vector3(monpos.x - 3.f, monpos.y + 1.f, 1.f));

		m_vRP.push_back(RP01);
		m_vRP.push_back(RP02);

		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP01);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, RP02);


	}

	void RP02_Obj::Update()
	{
	
		
		if (!m_vRP.empty())
		{


			if (m_bAttack)
			{

				//Sound
				if (m_bAC)
				{
					m_vRP[0]->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.f));
					m_vRP[1]->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.f));
					m_vRP[0]->GetAc()->Play();
					m_bAC = false;
				}

				if (m_vRP[1]->GetComponent<Transform>()->GetScale().x > 0.f)
				{

					Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();
					m_fTime += Time::DeltaTime();

					if (m_fTime <= 1.f)
					{
						

						m_vRP[0]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x + 3.f, monpos.y + 1.f, 1.f));
						m_vRP[1]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x - 3.f, monpos.y + 1.f, 1.f));

						m_vRP[0]->GetComponent<Transform>()->SetScale(Vector3(m_fTime + 1.f, m_fTime + 1.f, 0.f));
						m_vRP[1]->GetComponent<Transform>()->SetScale(Vector3(m_fTime + 1.f, m_fTime + 1.f, 0.f));
					}

					Vector3 playerPos = m_Player->GetComponent<Transform>()->GetPosition();

				

					if (m_fTime >= 2.f)
					{

						Vector3 scale = m_vRP[0]->GetComponent<Transform>()->GetScale();

						

						if (m_vRP[0] != nullptr)
						{

							if (scale.x > 0)
							{
								m_vRP[0]->GetComponent<Transform>()->SetScale(Vector3(scale.x - Time::DeltaTime(), scale.y - Time::DeltaTime(), 0));

							}
							Vector3 ObjPos = m_vRP[0]->GetComponent<Transform>()->GetPosition();


							float vDistanceX = playerPos.x - ObjPos.x;
							float vDistanceY = playerPos.y - ObjPos.y;

							ObjPos.x += vDistanceX * Time::DeltaTime() * 2;
							ObjPos.y += vDistanceY * Time::DeltaTime() * 2;

							m_vRP[0]->GetComponent<Transform>()->SetPositionXY(Vector2(ObjPos.x, ObjPos.y));

						}


					}


					if (m_fTime >= 4.f)
					{
						if (m_vRP[1] != nullptr)
						{

							Vector3 scale = m_vRP[1]->GetComponent<Transform>()->GetScale();

							if (scale.x > 0)
							{
								m_vRP[1]->GetComponent<Transform>()->SetScale(Vector3(scale.x - Time::DeltaTime(), scale.y - Time::DeltaTime(), 0));
							}


							Vector3 Obj2Pos = m_vRP[1]->GetComponent<Transform>()->GetPosition();

							float vDistanceX2 = playerPos.x - Obj2Pos.x;
							float vDistanceY2 = playerPos.y - Obj2Pos.y;


							Obj2Pos.x += vDistanceX2 * Time::DeltaTime() * 2;
							Obj2Pos.y += vDistanceY2 * Time::DeltaTime() * 2;

							m_vRP[1]->GetComponent<Transform>()->SetPositionXY(Vector2(Obj2Pos.x, Obj2Pos.y));
						}
					
					}
				}
				else
				{
					Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();

					//m_vRP[0]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x + 3.5f, monpos.y, 1.f));
					//m_vRP[0]->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.f));
					//m_vRP[1]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x - 3.5f, monpos.y, 1.f));
					//m_vRP[1]->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.f));
					m_bAttack = false;
					m_fTime = 0.f;


					m_vRP[0]->GetComponent<Collider2D>()->SetCenter(Vector2(100.f, 0.f));
					m_vRP[1]->GetComponent<Collider2D>()->SetCenter(Vector2(-100.f, 0.f));
			
				}
			}
			else
			{
				m_bAC = true;

				Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();

				m_vRP[0]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x + 3.5f, monpos.y + 1.f, 1.f));
				m_vRP[0]->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.f));
				
				m_vRP[1]->GetComponent<Transform>()->SetPosition(Vector3(monpos.x - 3.5f, monpos.y + 1.f, 1.f));
				m_vRP[1]->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.f));

			}

			

		}
	


		GameObject::Update();
	}

	void RP02_Obj::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}

	void RP02_Obj::Render()
	{
		GameObject::Render();
	}

}