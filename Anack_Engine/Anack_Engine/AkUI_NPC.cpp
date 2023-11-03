#include "AkUI_NPC.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkSceneManager.h"
#include "AkFontWrapper.h"

namespace Ak
{
	UI_NPC::UI_NPC()
		:m_bGrimmGrigger(false)
	{
		SetName(L"UI_NPC");




	}

	UI_NPC::~UI_NPC()
	{
		SceneManager::DestoryObj(this);
	
		for (GameObject* obj : m_vObj)
		{
			SceneManager::DestoryObj(obj);
			delete obj;
		}

		m_vObj.clear();
	
	}

	void UI_NPC::Initialize()
	{

		GameObject* TopUI_obj = new GameObject();
		MeshRenderer* mr_top_ui = TopUI_obj->AddComponent<MeshRenderer>();
		mr_top_ui->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_top_ui->SetMaterial(Resources::Find<Material>(L"Top_UI"));
		TopUI_obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.5f, -3.0f));
		TopUI_obj->GetComponent<Transform>()->SetScale(Vector3(3.f, 0.5f, 0.f));
		SceneManager::AddGameObject(eLayerType::UI, TopUI_obj);

		m_vObj.push_back(TopUI_obj);


		if (!m_bGrimmGrigger)
		{
			if (SceneManager::GetGrimmCoin())
			{
				GameObject* BG_UI = new GameObject();
				MeshRenderer* mr_bg_ui = BG_UI->AddComponent<MeshRenderer>();
				mr_bg_ui->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr_bg_ui->SetMaterial(Resources::Find<Material>(L"BG_UI03"));
				BG_UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.2f, -2.999f));
				BG_UI->GetComponent<Transform>()->SetScale(Vector3(6.f, 3.f, 0.f));
				SceneManager::AddGameObject(eLayerType::UI, BG_UI);

				m_vObj.push_back(BG_UI);


				Light* smileLight = BG_UI->AddComponent<Light>();
				smileLight->SetType(eLightType::Point);
				smileLight->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
				smileLight->SetRadius(5.0f);
			}
			else
			{
				GameObject* BG_UI = new GameObject();
				MeshRenderer* mr_bg_ui = BG_UI->AddComponent<MeshRenderer>();
				mr_bg_ui->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr_bg_ui->SetMaterial(Resources::Find<Material>(L"BG_UI"));
				BG_UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.2f, -2.999f));
				BG_UI->GetComponent<Transform>()->SetScale(Vector3(6.f, 3.f, 0.f));
				SceneManager::AddGameObject(eLayerType::UI, BG_UI);

				m_vObj.push_back(BG_UI);


				Light* smileLight = BG_UI->AddComponent<Light>();
				smileLight->SetType(eLightType::Point);
				smileLight->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
				smileLight->SetRadius(5.0f);
			}
		}
		else
		{
			GameObject* BG_UI = new GameObject();
			MeshRenderer* mr_bg_ui = BG_UI->AddComponent<MeshRenderer>();
			mr_bg_ui->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr_bg_ui->SetMaterial(Resources::Find<Material>(L"BGUI_02"));
			BG_UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.2f, -2.999f));
			BG_UI->GetComponent<Transform>()->SetScale(Vector3(6.f, 3.f, 0.f));
			SceneManager::AddGameObject(eLayerType::UI, BG_UI);

			m_vObj.push_back(BG_UI);


			Light* smileLight = BG_UI->AddComponent<Light>();
			smileLight->SetType(eLightType::Point);
			smileLight->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
			smileLight->SetRadius(5.0f);
		}






		GameObject* Bottom_obj = new GameObject();
		MeshRenderer* mr_bottom_ui = Bottom_obj->AddComponent<MeshRenderer>();
		mr_bottom_ui->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bottom_ui->SetMaterial(Resources::Find<Material>(L"Bottom_UI"));
		Bottom_obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -1.1f, -3.0));
		Bottom_obj->GetComponent<Transform>()->SetScale(Vector3(2.f, 0.4f, 0.f));
		SceneManager::AddGameObject(eLayerType::UI, Bottom_obj);

		m_vObj.push_back(Bottom_obj);

	}

	void UI_NPC::Update()
	{
		GameObject::Update();
	}

	void UI_NPC::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void UI_NPC::Render()
	{
		GameObject::Render();
	}

}