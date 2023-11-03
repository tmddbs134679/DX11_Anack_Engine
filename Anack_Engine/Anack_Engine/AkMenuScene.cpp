#include "AkMenuScene.h"
#include "AkGameObject.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkInput.h"
#include  "AkResources.h"
#include "AkSceneManager.h"
#include "AkMeshRenderer.h"
#include "AkCameraScript.h"

namespace Ak
{
	MenuScene::MenuScene()
	{
		Initialize();
	}

	MenuScene::~MenuScene()
	{
	}

	void MenuScene::Initialize()
	{

		GameObject* Menu_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Menu_BG);
		MeshRenderer* mr = Menu_BG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Menutexture"));
		Menu_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 0.f));
		Menu_BG->GetComponent<Transform>()->SetScale(Vector3(25.f,22.f,20.f));

		//
		//GameObject* Menu_Title = new GameObject();
		//AddGameObject(eLayerType::BackGround, Menu_Title);
		//MeshRenderer* mrtitle = Menu_Title->AddComponent<MeshRenderer>();
		//mrtitle->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mrtitle->SetMaterial(Resources::Find<Material>(L"MenuTitle"));
		//Menu_Title->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 0.f));
		//Menu_Title->GetComponent<Transform>()->SetScale(Vector3(5.f, 5.f, 5.f));

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

	}

	void MenuScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			SceneManager::LoadScene(L"StartGame");
		}

		Scene::Update();
	}

	void MenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MenuScene::Render()
	{
		Scene::Render();
	}

}