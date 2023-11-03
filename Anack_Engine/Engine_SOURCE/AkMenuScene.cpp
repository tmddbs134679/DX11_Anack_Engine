#pragma once

#include "AkMenuScene.h"
#include "AkGameObject.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkInput.h"
#include  "AkResources.h"
#include "AkSceneManager.h"
#include "AkMeshRenderer.h"
#include "AkCameraScript.h"
//#include "AkGridScript.h"
#include "..\Anack_Engine\AkGridScript.h"
#include "AkRenderer.h"
#include "AkCollider2D.h"
#include "AkObject.h"
#include "AkAnimator.h"
#include "..\Anack_Engine\AkPlayerScript.h"
#include "../Anack_Engine/AkGround.h"
#include "../Anack_Engine/AkSceneChangeTrigger.h"
#include "AkPaintShader.h"
#include "AkParticleSystem.h"
#include "../Anack_Engine/AkHunter.h"
#include "../Anack_Engine/AkBaldur.h"
#include "../Anack_Engine/AkPlayerWeapon.h"
#include "../Anack_Engine/AkGameTrigger.h"
#include "../Anack_Engine/AkGameStartEffect.h"
#include "../Anack_Engine/AkGrass.h"
#include "../Anack_Engine/AkHealth.h"
#include "AkAudioClip.h"
#include "AkAudioListener.h"
//#include "AkAudioSource.h"


namespace Ak
{
	MenuScene::MenuScene()
	{
		
	}

	MenuScene::~MenuScene()
	{
		
	}

	void MenuScene::Initialize()
	{
	

		//floor
		Ground* floor = new Ground();
		AddGameObject(eLayerType::Ground, floor);
		floor->GetComponent<Transform>()->SetPosition(Vector3(0.f, -6.f, 0.99f));
		floor->GetComponent<Transform>()->SetScale(25.f, 1.f, 0.f);
		

		ParticleSystem* ps = floor->AddComponent<ParticleSystem>();
		ps->GetMaterial()->SetTexture(Resources::Find<Texture>(L"black_soul"));
		ps->SetParticleCount(30);
		ps->SetParticleSpeed(2.f);
		ps->SetParticleDirection(Vector4(0.f, 1.f, 0.f, 0.f));
		ps->SetParticleDestory(10.f);
		ps->SetParticleRandom(8.f);
		//ps->SetParticleOffset(Vector3(0.f, -2.f, 0.f));
		ps->SetRandomZ(true);
		ps->SetRotation(0.f, 30.f);
		//ps->SetRandomDirection(true);

		//ps->SetAngle(0.f, 90.f);



		//ParticleSystem* ps = floor->AddComponent<ParticleSystem>();
		//ps->GetMaterial()->SetTexture(Resources::Find<Texture>(L"black_soul"));
		//ps->SetParticleCount(30);
		//ps->SetParticleSpeed(2.f);
		//ps->SetParticleDirection(Vector4(0.f, 1.f, 0.f, 0.f));
		//ps->SetParticleDestory(10.f);
		//ps->SetParticleRandom(8.f);
		////ps->SetParticleOffset(Vector3(0.f, -2.f, 0.f));
		//ps->SetRandomZ(true);
		//ps->SetRotation(0.f, 30.f);
		//ps->SetAngle(0.f, 90.f);

		
		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);
	
		pPlayer->Initialize();
		pPlayer->GetComponent<PlayerScript>()->SetPlayer(pPlayer);
		pPlayer->GetComponent<Transform>()->SetPosition(0.f, 100.f, 1.000f);

		pPlayer->AddComponent<AudioListener>();
		pPlayer->SetCurScene(this);

		Light* PlayerLight = pPlayer->AddComponent<Light>();
		PlayerLight->SetType(eLightType::Point);
		PlayerLight->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.6f));
		PlayerLight->SetRadius(3.0f);


		RegisterPlayer(pPlayer);

		// 
		//Baldur* mBaldur = new Baldur();
		//AddGameObject(eLayerType::Monster, mBaldur);
		//mBaldur->Initialize();
		//mBaldur->GetComponent<Transform>()->SetPosition(4.f, 30.f, 1.0001);
		//mBaldur->SetScene(this);



#pragma region BackGround

		GameObject* Menu_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Menu_BG);
		Menu_BG->SetName(L"Mune_BG");
		MeshRenderer* mrbackGround = Menu_BG->AddComponent<MeshRenderer>();
		mrbackGround->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrbackGround->SetMaterial(Resources::Find<Material>(L"Menutexture"));
		Menu_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 1.5002f));
		Menu_BG->GetComponent<Transform>()->SetScale(Vector3(25.f, 24.f, 20.f));



		Ground* Menu_Logo = new Ground();
		AddGameObject(eLayerType::Ground, Menu_Logo);
		MeshRenderer* mr_Menu_logo = Menu_Logo->AddComponent<MeshRenderer>();
		mr_Menu_logo->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_Menu_logo->SetMaterial(Resources::Find<Material>(L"Menu_Logo"));
		Menu_Logo->GetComponent<Transform>()->SetPosition(Vector3(-8.f, -3.f, 1.0003f));
		Menu_Logo->GetComponent<Transform>()->SetScale(Vector3(2.5f, 0.5f, 0.f));
	


		GameTrigger* Game_Start = new GameTrigger();
		Game_Start->Initialize();
		Game_Start->SetName(L"Game_Start");
		AddGameObject(eLayerType::Ground, Game_Start);
		MeshRenderer* mr_gamestart = Game_Start->AddComponent<MeshRenderer>();
		mr_gamestart->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_gamestart->SetMaterial(Resources::Find<Material>(L"Game_Start01"));
		Game_Start->GetComponent<Transform>()->SetPosition(Vector3(-3.f, -0.5f, 1.0003f));
		Game_Start->GetComponent<Transform>()->SetScale(Vector3(1.5f, 0.75f, 0.f));






		GameTrigger* Game_Exit = new GameTrigger();
		Game_Exit->SetName(L"Game_Exit");
		AddGameObject(eLayerType::Ground, Game_Exit);
		MeshRenderer* mr_gameexit = Game_Exit->AddComponent<MeshRenderer>();
		mr_gameexit->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_gameexit->SetMaterial(Resources::Find<Material>(L"Game_Exit01"));
		Game_Exit->GetComponent<Transform>()->SetPosition(Vector3(3.f, -0.5f, 1.0003f));
		Game_Exit->GetComponent<Transform>()->SetScale(Vector3(1.4f, 0.7f, 0.f));


		GameObject* Menu_Title = new GameObject();
		Menu_Title->SetName(L"Menu_Title");
		AddGameObject(eLayerType::UI, Menu_Title);
		MeshRenderer* mrtitle = Menu_Title->AddComponent<MeshRenderer>();
		mrtitle->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrtitle->SetMaterial(Resources::Find<Material>(L"Menu_Title"));
		Menu_Title->GetComponent<Transform>()->SetPosition(Vector3(0.f, 2.5f, 1.2f));
		Menu_Title->GetComponent<Transform>()->SetScale(Vector3(13.f, 5.5f, 1.f));

#pragma endregion

		

		//////Particle////////////

	

		


		Camera* cameraComp = nullptr;

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			SetMainCamera(cameraComp);

			camera->AddComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\Title.mp3"));
			m_SceneAS = camera->GetComponent<AudioSource>();

		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			cameraComp->TurnLayerMask(eLayerType::Grid, false);
			cameraComp->TurnLayerMask(eLayerType::Ground, false);
			cameraComp->TurnLayerMask(eLayerType::LayeredObj, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Light, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			//camera->AddComponent<CameraScript>();
		}

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

	void MenuScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Ground, true);



		Scene::OnEnter();
	}

	void MenuScene::OnExit()
	{
		
		SceneManager::Destory();
		CollisionManager::Clear();

	
		Scene::OnExit();

		
		DestroyAll();

	}

}