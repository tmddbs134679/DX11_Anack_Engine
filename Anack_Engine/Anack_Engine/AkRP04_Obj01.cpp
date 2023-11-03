#include "AkRP04_Obj01.h"

#include "AkSceneManager.h"
#include "AkTime.h"


namespace Ak
{
	RP04_Obj01::RP04_Obj01()
		: m_bAttack(false)
		, fmove(0.f)
	{

	}

	RP04_Obj01::~RP04_Obj01()
	{
		SceneManager::DestoryObj(this);
		for (const auto& test : m_vRP)
		{
			//test->GetComponent<Animator>()->PlayAnimation(L"Attack_particle3", false);
			SceneManager::DestoryObj(test);
			delete test;

		}

		m_vRP.clear();
	}

	void RP04_Obj01::Initialize()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();


		//beam 2
		Radiance_Projectile_04* PJ4_01 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_01);
		PJ4_01->GetComponent<Transform>()->SetPosition(pos.x + 5.f, pos.y + 3.f, 1.31f);


		Radiance_Projectile_04* PJ4_02 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_02);
		PJ4_02->GetComponent<Transform>()->SetPosition(pos.x + 5.5f, pos.y + 3.f, 1.31f);

		Radiance_Projectile_04* PJ4_03 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_03);
		PJ4_03->GetComponent<Transform>()->SetPosition(pos.x + 4.f, pos.y + 3.f, 1.31f);
		PJ4_03->GetComponent<Animator>()->PlayAnimation(L"attack04_set", true);

		Radiance_Projectile_04* PJ4_04 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_04);
		PJ4_04->GetComponent<Transform>()->SetPosition(pos.x + 3.5f, pos.y + 3.f, 1.31f);
		PJ4_04->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);

		Radiance_Projectile_04* PJ4_05 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_05);
		PJ4_05->GetComponent<Transform>()->SetPosition(pos.x + 6.5f, pos.y + 3.f, 1.31f);
		PJ4_05->GetComponent<Animator>()->PlayAnimation(L"attack04_set", true);


		Radiance_Projectile_04* PJ4_06 = new Radiance_Projectile_04;
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_06);
		PJ4_06->GetComponent<Transform>()->SetPosition(pos.x + 7.f, pos.y + 3.f, 1.31f);
		PJ4_06->GetComponent<Animator>()->PlayAnimation(L"attack04_001", true);


		m_vRP.push_back(PJ4_01);
		m_vRP.push_back(PJ4_02);
		m_vRP.push_back(PJ4_03);
		m_vRP.push_back(PJ4_04);
		m_vRP.push_back(PJ4_05);
		m_vRP.push_back(PJ4_06);
		

		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_01);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_02);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_03);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_04);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_05);
		SceneManager::AddGameObject(eLayerType::MonsterAttack, PJ4_06);


	}

	void RP04_Obj01::Update()
	{

		if (!m_vRP.empty())
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();

			if (m_bAttack)
			{
				

				fmove += 0.02;


				//Attack trueÀÏ‹š
				m_vRP[0]->GetComponent<Transform>()->SetPosition(pos.x + 5.f + fmove, pos.y + 3.f, 1.31f);
				m_vRP[1]->GetComponent<Transform>()->SetPosition(pos.x + 5.5f + fmove, pos.y + 3.f, 1.31f);
				m_vRP[2]->GetComponent<Transform>()->SetPosition(pos.x + 4.f + fmove, pos.y + 3.f, 1.31f);
				m_vRP[3]->GetComponent<Transform>()->SetPosition(pos.x + 3.5f + fmove, pos.y + 3.f, 1.31f);
				m_vRP[4]->GetComponent<Transform>()->SetPosition(pos.x + 6.5f + fmove, pos.y + 3.f, 1.31f);
				m_vRP[5]->GetComponent<Transform>()->SetPosition(pos.x + 7.f + fmove, pos.y + 3.f, 1.31f);


				if (m_vRP[0]->GetComponent<Transform>()->GetPosition().x >= 20.f)
				{
					m_bAttack = false;
				}
			}
			else
			{
				fmove = 0.f;
				m_vRP[0]->GetComponent<Transform>()->SetPosition(-40.f, pos.y + 3.f, 1.31f);
				m_vRP[1]->GetComponent<Transform>()->SetPosition(-40.f, pos.y + 3.f, 1.31f);
				m_vRP[2]->GetComponent<Transform>()->SetPosition(-40, pos.y + 3.f, 1.31f);
				m_vRP[3]->GetComponent<Transform>()->SetPosition(-40.f, pos.y + 3.f, 1.31f);
				m_vRP[4]->GetComponent<Transform>()->SetPosition(-40.f, pos.y + 3.f, 1.31f);
				m_vRP[5]->GetComponent<Transform>()->SetPosition(-40.f, pos.y + 3.f, 1.31f);
			
			}


			
		}
	
		GameObject::Update();
	}

	void RP04_Obj01::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RP04_Obj01::Render()
	{
		GameObject::Render();
	}

}