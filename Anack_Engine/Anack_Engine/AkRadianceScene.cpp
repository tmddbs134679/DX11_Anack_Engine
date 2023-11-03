#include "AkRadianceScene.h"
#include "AkResources.h"
#include "AkCameraScript.h"
#include "AkGround.h"
#include "AkAudioListener.h"
#include "AkCollisionManager.h"
#include "AkRadiance.h"
#include "AkHunter.h"
#include "AkRadianceBG.h"
#include "AkRG_Long.h"
#include "AkRG_Short.h"
#include "AkRadiance_Particle.h"
#include "AkRadiance_Proejctile_01.h"
#include "AkRadiance_Projectile_02.h"
#include "AkRadiance_Projectile_03.h"
#include "AkRadiance_Projectile_04.h"
#include "AkRP03_OBj.h"
#include "AkRP01_Obj.h"
#include "AkRP04_Obj01.h"
#include "AkRP04_Obj02.h"
#include "AkRP04_Obj03.h"
#include "AkRP02_Obj.h"
#include "AkRadiance_Light.h"
#include "AkRadiance_Trigger.h"
#include "AkInput.h"
#include "AkSceneManager.h"



namespace Ak
{
	RadianceScene::RadianceScene()
	{
		SetName(L"RadianceScene");
	}

	RadianceScene::~RadianceScene()
	{

	}

	void RadianceScene::Initialize()
	{

		GameObject* Menu_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Menu_BG);
		Menu_BG->SetName(L"Mune_BG");
		MeshRenderer* mrbackGround = Menu_BG->AddComponent<MeshRenderer>();
		mrbackGround->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrbackGround->SetMaterial(Resources::Find<Material>(L"Menutexture"));
		Menu_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 1.5002f));
		Menu_BG->GetComponent<Transform>()->SetScale(Vector3(200.f, 200.f, 20.f));




		RadianceBG* radian_bg = new RadianceBG();
		radian_bg->GetComponent<Transform>()->SetPosition(Vector3(0.f, 10.f, 1.502f));
		AddGameObject(eLayerType::Ground, radian_bg);

		GameObject* radiance_bg_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, radiance_bg_02);
		MeshRenderer* mr_radiacne_bg_02 = radiance_bg_02->AddComponent<MeshRenderer>();
		mr_radiacne_bg_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiacne_bg_02->SetMaterial(Resources::Find<Material>(L"Radiance_BG2"));
		radiance_bg_02->GetComponent<Transform>()->SetPosition(Vector3(0.f, 77.5f, 1.502f));
		radiance_bg_02->GetComponent<Transform>()->SetScale(Vector3(50.f, 60.f, 0.f));



		Ground* Radiance_Gd = new Ground();
		AddGameObject(eLayerType::Ground, Radiance_Gd);
		Radiance_Gd->SetName(L"Radiance_BG");
		MeshRenderer* mr_radiance_gd = Radiance_Gd->AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Ground"));
		Radiance_Gd->GetComponent<Transform>()->SetPosition(Vector3(0.f, -5.f, 1.002f));
		Radiance_Gd->GetComponent<Transform>()->SetScale(Vector3(20.f, 4.f, 20.f));


		GameObject* cloud01_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, cloud01_01);
		MeshRenderer* mr_cloud01_01 = cloud01_01->AddComponent<MeshRenderer>();
		mr_cloud01_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_cloud01_01->SetMaterial(Resources::Find<Material>(L"Cloud_01"));
		cloud01_01->GetComponent<Transform>()->SetPosition(Vector3(20.f, 2.f, 1.3f));
		cloud01_01->GetComponent<Transform>()->SetScale(Vector3(15.f, 10.f, 0.f));


		UI_HUD* HUB = new UI_HUD();
		HUB->Initialize();
		std::vector<Health*> ob = HUB->GetHUDObj();

		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);

		pPlayer->Initialize();
		pPlayer->GetComponent<PlayerScript>()->SetPlayer(pPlayer);
		pPlayer->GetComponent<Transform>()->SetPosition(-6.f, 20.f, 1.000f);
		//pPlayer->GetComponent<Transform>()->SetPosition(-6.f, 150.f, 1.000f);

		pPlayer->AddComponent<AudioListener>();
		pPlayer->SetCurScene(this);

		pPlayer->GetComponent<PlayerScript>()->SetHUD(ob);
		pPlayer->GetComponent<PlayerScript>()->SetPlayerHUD(HUB);
		RegisterPlayer(pPlayer);


		Radiance_Light* RL = new Radiance_Light();
		AddGameObject(eLayerType::Monster, RL);

		Radiance_Trigger* RT = new Radiance_Trigger();
		AddGameObject(eLayerType::Trigger, RT);
		RT->SetRadianceLight(RL);
		RT->SetPlayer(pPlayer);

		//RL->SetTrigger(RT);



		RP03_OBj* rp03 = new RP03_OBj();
		AddGameObject(eLayerType::MonsterAttack, rp03);
		
		RP01_Obj* rp01 = new RP01_Obj();
		AddGameObject(eLayerType::MonsterAttack, rp01);

		RP02_Obj* rp02 = new RP02_Obj();
		AddGameObject(eLayerType::MonsterAttack, rp02);


		RP04_Obj01* rp04_01 = new RP04_Obj01();
		rp04_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		AddGameObject(eLayerType::MonsterAttack, rp04_01);

		RP04_Obj02* rp04_02 = new RP04_Obj02();
		AddGameObject(eLayerType::MonsterAttack, rp04_02);

		RP04_Obj03* rp04_03 = new RP04_Obj03();
		AddGameObject(eLayerType::MonsterAttack, rp04_03);

		Radiance* rd = new Radiance();
		rd->GetComponent<Transform>()->SetPosition(Vector3(-5.f, -50.f, 1.3f));
		AddGameObject(eLayerType::Monster, rd);

		rd->Initialize();
		rd->SetScene(this);

		rd->SetRadianceAttack01(rp01);
		rd->SetRadianceAttack02(rp02);
		rd->SetRadianceAttack03(rp03);
		rd->SetRadianceAttack04_01(rp04_01);
		rd->SetRadianceAttack04_02(rp04_02);
		rd->SetRadianceAttack04_03(rp04_03);
		

		rp01->SetOwner(rd);
		rp01->SetPlayer(pPlayer);
		rp02->SetOwner(rd);
		rp02->SetPlayer(pPlayer);

		rp04_02->SetOwner(rd);
		

		rp04_03->SetOwner(rd);
		rp04_03->SetPlayer(pPlayer);


		RT->SetRadiance(rd);

		m_SceneAC = Resources::Load<AudioClip>(L"Radiance", L"..\\Resources\\Sound\\Radiance\\Radiance.mp3");
		m_SceneAC->SetLoop(true);
		m_SceneAC->SetSoundDistance(Vector2(1000.f,1000.f));

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light); 
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

		}



		Camera* cameraComp = nullptr;

		//Main Camera

		GameObject* camera = new GameObject();
		camera->SetName(L"PlayerCamera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		cameraComp = camera->AddComponent<Camera>();
		CameraScript* cameraSr = camera->AddComponent<CameraScript>();
		cameraSr->SetPlayer(pPlayer);
		//cameraSr->SetBackGround(Start_BG);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		SetMainCamera(cameraComp);

		SetCameraObj(camera);

		rd->SetSceneCamera(camera);

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
			cameraComp->TurnLayerMask(eLayerType::PlayerAttack, false);
			cameraComp->TurnLayerMask(eLayerType::Light, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			cameraComp->TurnLayerMask(eLayerType::MonsterAttack, false);
			//camera->AddComponent<CameraScript>();
		}




	}

	void RadianceScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
		Scene::Update();
	}

	void RadianceScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void RadianceScene::Render()
	{
		Scene::Render();
	}

	void RadianceScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trigger, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Ground, true);


		Scene::OnEnter();
	}

	void RadianceScene::OnExit()
	{
	
		Scene::OnExit();
		DestroyAll();

	}

}