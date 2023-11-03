#include "AkStartGameScene.h"
#include "AkMeshRenderer.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkResources.h"
#include "AkSceneManager.h"
#include "AkInput.h"

namespace Ak
{
	StartGameScene::StartGameScene()
	{
		Initialize();
	}

	StartGameScene::~StartGameScene()
	{
	}

	void StartGameScene::Initialize()
	{

		GameObject* Start_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Start_BG);
		MeshRenderer* mr = Start_BG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Start_BGMR"));
		Start_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 0.f));
		Start_BG->GetComponent<Transform>()->SetScale(Vector3(25.f, 25.f, 20.f));

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();


		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -1.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 0.0f, -2.0f));
			//player->AddComponent<CameraScript>();
		}

	}

	void StartGameScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			SceneManager::LoadScene(L"Battle_BG01");
		}

		Scene::Update();
	}

	void StartGameScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void StartGameScene::Render()
	{
		Scene::Render();
	}
}