#include "AkBattleScene01.h"
#include "AkMeshRenderer.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkResources.h"

namespace Ak
{
	BattleScene01::BattleScene01()
	{
		Initialize();
	}

	BattleScene01::~BattleScene01()
	{
	}

	void BattleScene01::Initialize()
	{
		GameObject* Battle_BG01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Battle_BG01);
		MeshRenderer* mr = Battle_BG01->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BG01"));
		Battle_BG01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Battle_BG01->GetComponent<Transform>()->SetScale(Vector3(25.f, 11.5f, 10.f));

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}

	void BattleScene01::Update()
	{
		Scene::Update();
	}

	void BattleScene01::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BattleScene01::Render()
	{
		Scene::Render();
	}

}