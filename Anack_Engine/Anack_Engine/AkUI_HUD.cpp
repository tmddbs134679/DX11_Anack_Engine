#include "AkUI_HUD.h"
#include "AkGameObject.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkScene.h"
#include "AkSceneManager.h"
#include "AkLight.h"
#include "AkHealth.h"
#include "AkHudScript.h"
#include "AkHP_Ball.h"
#include "AkAnimator.h"

namespace Ak
{
	UI_HUD::UI_HUD()
		:m_iHealthCNT(4)
	{
		
		m_iHealthCNT = SceneManager::GetHealth();
	

#pragma region UP_CNT
		Health* HP_HUD_CNT0 = new Health();
	
		HP_HUD_CNT0->GetComponent<Transform>()->SetPosition(Vector3(-4.8f, 3.2f, -3.0f));
	

		SceneManager::AddGameObject(eLayerType::UI, HP_HUD_CNT0);
		m_objHUDCount.push_back(HP_HUD_CNT0);



		Health* HP_HUD_CNT1 = new Health();
		HP_HUD_CNT1->GetComponent<Transform>()->SetPosition(Vector3(-4.2f, 3.2f, -3.0f));


		SceneManager::AddGameObject(eLayerType::UI, HP_HUD_CNT1);
		m_objHUDCount.push_back(HP_HUD_CNT1);


		Health* HP_HUD_CNT2 = new Health();
		HP_HUD_CNT2->GetComponent<Transform>()->SetPosition(Vector3(-3.6f, 3.2f, -3.0f));
	

		SceneManager::AddGameObject(eLayerType::UI, HP_HUD_CNT2);
		m_objHUDCount.push_back(HP_HUD_CNT2);

		Health* HP_HUD_CNT3 = new Health();
		HP_HUD_CNT3->GetComponent<Transform>()->SetPosition(Vector3(-3.f, 3.2f, -3.0f));
	

		SceneManager::AddGameObject(eLayerType::UI, HP_HUD_CNT3);
		m_objHUDCount.push_back(HP_HUD_CNT3);



		Health* HP_HUD_CNT4 = new Health();
		HP_HUD_CNT4->GetComponent<Transform>()->SetPosition(Vector3(-2.4f, 3.2f, -3.0f));

		SceneManager::AddGameObject(eLayerType::UI, HP_HUD_CNT4);
		m_objHUDCount.push_back(HP_HUD_CNT4);

#pragma endregion

		


		GameObject* COIN_HUD = new GameObject();
		MeshRenderer* mrHpHudCoin = COIN_HUD->AddComponent<MeshRenderer>();
		mrHpHudCoin->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrHpHudCoin->SetMaterial(Resources::Find<Material>(L"Coin_HUD"));
		COIN_HUD->GetComponent<Transform>()->SetPosition(Vector3(-4.8f, 2.5f, -3.0f));
		COIN_HUD->GetComponent<Transform>()->SetScale(Vector3(0.6f, 0.6f, 0.f));

		SceneManager::AddGameObject(eLayerType::UI, COIN_HUD);
		m_HUD_Coin = COIN_HUD;


		GameObject* HP_HUD = new GameObject();
		MeshRenderer* mrHpHud = HP_HUD->AddComponent<MeshRenderer>();
		mrHpHud->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrHpHud->SetMaterial(Resources::Find<Material>(L"HP_HUD"));

		HP_HUD->GetComponent<Transform>()->SetPosition(Vector3(-5.3f, 3.0f, -2.99f));
		HP_HUD->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.5f, 0.f));

		SceneManager::AddGameObject(eLayerType::UI, HP_HUD);


		m_HUD = HP_HUD;


		HP_Ball* pHp_Ball = new HP_Ball();
		
		SceneManager::AddGameObject(eLayerType::UI, pHp_Ball);
		m_HPBall = pHp_Ball;
		
		
	}

	UI_HUD::~UI_HUD()
	{
		for (GameObject* obj : m_objHUDCount)
		{
			SceneManager::DestoryObj(obj);
			delete obj;
		}
		m_objHUDCount.clear();

		SceneManager::DestoryObj(m_HUD);
		delete m_HUD;
		m_HUD = nullptr;

		SceneManager::DestoryObj(m_HUD_Coin);
		delete m_HUD_Coin;
		m_HUD_Coin = nullptr;


	}

	void UI_HUD::Initialize()
	{
		switch (SceneManager::GetHealth())
		{
		case 0:
			m_objHUDCount[1]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[2]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[3]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[4]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			break;

		case 1:
			
			m_objHUDCount[2]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[3]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[4]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			break;

		case 2:
			
			m_objHUDCount[3]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			m_objHUDCount[4]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			break;

		case 3:
			
			m_objHUDCount[4]->GetComponent<Animator>()->PlayAnimation(L"Health_Empty", false);
			break;

		case 4:

			for (auto& Heal : m_objHUDCount)
			{
				Heal->GetComponent<Animator>()->PlayAnimation(L"Health_Life", true);
			}
			break;

		default:
			break;
		}

	}

	void UI_HUD::Update()
	{
		GameObject::Update();
	}

	void UI_HUD::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void UI_HUD::Render()
	{
	/*	renderer::AnimatorCB AnimatorCB;
		AnimatorCB.bUI = m_bUI;


		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&AnimatorCB);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);*/ 
		GameObject::Render();

	}

}