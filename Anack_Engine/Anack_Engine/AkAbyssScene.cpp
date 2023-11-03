#include "AkAbyssScene.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkRenderer.h"
#include "AkLight.h"
#include "AkBox.h"
#include "AkGround.h"
#include "AkCollisionManager.h"
#include "AkTrap.h"
#include "AkLight.h"
#include "AkSceneManager.h"
#include "AkInput.h"
#include "AkSceneChangeScript.h"
#include "AkAudioListener.h"
#include "AkBaldur.h"

namespace Ak

{
	AbyssScene::AbyssScene()
	{

	}

	AbyssScene::~AbyssScene()
	{

	}

	void AbyssScene::Initialize()
	{




#pragma region MapTXT
		GameObject* Abyss_BG_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_01);
		Abyss_BG_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_01 = Abyss_BG_01->AddComponent<MeshRenderer>();
		mr_abyss_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_01->SetMaterial(Resources::Find<Material>(L"Menutexture"));
		Abyss_BG_01->GetComponent<Transform>()->SetPosition(Vector3(25.f, 35.f, 1.5002f));
		Abyss_BG_01->GetComponent<Transform>()->SetScale(Vector3(130.f, 100.f, 0.f));



		GameObject* Abyss_BG_black = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black);
		Abyss_BG_black->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black = Abyss_BG_black->AddComponent<MeshRenderer>();
		mr_abyss_bg_black->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black->GetComponent<Transform>()->SetPosition(Vector3(-5.f, 18.5f, 0.99999f));
		Abyss_BG_black->GetComponent<Transform>()->SetScale(Vector3(30.f, 30.f, 0.f));


		GameObject* Abyss_BG_ceil_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_ceil_01);
		Abyss_BG_ceil_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_ceil_01 = Abyss_BG_ceil_01->AddComponent<MeshRenderer>();
		mr_abyss_bg_ceil_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_ceil_01->SetMaterial(Resources::Find<Material>(L"Abyss_BG_ceil_01"));
		Abyss_BG_ceil_01->GetComponent<Transform>()->SetPosition(Vector3(15.f, 8.f, 0.99999f));
		Abyss_BG_ceil_01->GetComponent<Transform>()->SetScale(Vector3(20.f, 10.f, 0.f));


		GameObject* Abyss_BG_ceil_flat_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_ceil_flat_01);
		Abyss_BG_ceil_flat_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_ceil_flat_01 = Abyss_BG_ceil_flat_01->AddComponent<MeshRenderer>();
		mr_abyss_bg_ceil_flat_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_ceil_flat_01->SetMaterial(Resources::Find<Material>(L"Abyss_BG_ceil_flat"));
		Abyss_BG_ceil_flat_01->GetComponent<Transform>()->SetPosition(Vector3(35.f, 13.f, 0.99999f));
		Abyss_BG_ceil_flat_01->GetComponent<Transform>()->SetScale(Vector3(30.f, 10.f, 0.f));

		GameObject* Abyss_BG_ceil_flat_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_ceil_flat_02);
		Abyss_BG_ceil_flat_02->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_ceil_flat_02 = Abyss_BG_ceil_flat_02->AddComponent<MeshRenderer>();
		mr_abyss_bg_ceil_flat_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_ceil_flat_02->SetMaterial(Resources::Find<Material>(L"Abyss_BG_ceil_flat"));
		Abyss_BG_ceil_flat_02->GetComponent<Transform>()->SetPosition(Vector3(-10.f, 6.3f, 0.89999f));
		Abyss_BG_ceil_flat_02->GetComponent<Transform>()->SetScale(Vector3(30.f, 10.f, 0.f));

		GameObject* Abyss_BG_ceil_flat_03 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_ceil_flat_03);
		Abyss_BG_ceil_flat_03->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_ceil_flat_03 = Abyss_BG_ceil_flat_03->AddComponent<MeshRenderer>();
		mr_abyss_bg_ceil_flat_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_ceil_flat_03->SetMaterial(Resources::Find<Material>(L"Abyss_BG_ceil_flat"));
		Abyss_BG_ceil_flat_03->GetComponent<Transform>()->SetPosition(Vector3(0.f, 4.5f, 0.89999f));
		Abyss_BG_ceil_flat_03->GetComponent<Transform>()->SetScale(Vector3(20.f, 5.f, 0.f));

		GameObject* Abyss_BG_ceil_flat_04 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_ceil_flat_04);
		Abyss_BG_ceil_flat_04->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_ceil_flat_04 = Abyss_BG_ceil_flat_04->AddComponent<MeshRenderer>();
		mr_abyss_bg_ceil_flat_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_ceil_flat_04->SetMaterial(Resources::Find<Material>(L"Abyss_BG_ceil_flat"));
		Abyss_BG_ceil_flat_04->GetComponent<Transform>()->SetPosition(Vector3(63.f, 15.5f, 0.89999f));
		Abyss_BG_ceil_flat_04->GetComponent<Transform>()->SetScale(Vector3(30.f, 10.f, 0.f));




		GameObject* Abyss_layered_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_layered_01);
		Abyss_layered_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_layered_01 = Abyss_layered_01->AddComponent<MeshRenderer>();
		mr_abyss_layered_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_layered_01->SetMaterial(Resources::Find<Material>(L"Abyss_layered_01"));
		Abyss_layered_01->GetComponent<Transform>()->SetPosition(Vector3(10.f, 3.7f, 0.89999f));
		Abyss_layered_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 3.f, 0.f));


		Ground* Abyss_flat_bri_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_flat_bri_01);
		Abyss_flat_bri_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_flat_bri_01 = Abyss_flat_bri_01->AddComponent<MeshRenderer>();
		mr_abyss_flat_bri_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_flat_bri_01->SetMaterial(Resources::Find<Material>(L"Abyss_BG_flat_02"));
		Abyss_flat_bri_01->GetComponent<Transform>()->SetPosition(Vector3(62.5f, 5.f, 0.99999f));
		Abyss_flat_bri_01->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.f, 0.f));


		GameObject* Abyss_BG_black_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_02);
		Abyss_BG_black_02->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_02 = Abyss_BG_black_02->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_02->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_02->GetComponent<Transform>()->SetPosition(Vector3(50.f, 10.f, 0.99999f));
		Abyss_BG_black_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 10.f, 0.f));


		GameObject* Abyss_BG_black_03 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_03);
		Abyss_BG_black_03->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_03 = Abyss_BG_black_03->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_03->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_03->GetComponent<Transform>()->SetPosition(Vector3(30.f, -10.f, 0.89f));
		Abyss_BG_black_03->GetComponent<Transform>()->SetScale(Vector3(100.f, 20.f, 0.f));

		GameObject* Abyss_BG_black_04 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_04);
		Abyss_BG_black_04->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_04 = Abyss_BG_black_04->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_04->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_04->GetComponent<Transform>()->SetPosition(Vector3(35.f, -1.f, 0.9f));
		Abyss_BG_black_04->GetComponent<Transform>()->SetScale(Vector3(18.3f, 10.f, 0.f));


		GameObject* Abyss_BG_black_05 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_05);
		Abyss_BG_black_05->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_05 = Abyss_BG_black_05->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_05->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_05->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_05->GetComponent<Transform>()->SetPosition(Vector3(15.f, 21.f, 0.9f));
		Abyss_BG_black_05->GetComponent<Transform>()->SetScale(Vector3(58.3f, 20.f, 0.f));

		GameObject* Abyss_BG_black_06 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_06);
		Abyss_BG_black_06->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_06 = Abyss_BG_black_06->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_06->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_06->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_06->GetComponent<Transform>()->SetPosition(Vector3(45.f, 25.f, 0.9f));
		Abyss_BG_black_06->GetComponent<Transform>()->SetScale(Vector3(65.3f, 20.f, 0.f));



		GameObject* Abyss_BG_black_07 = new GameObject();
		AddGameObject(eLayerType::BackGround, Abyss_BG_black_07);
		Abyss_BG_black_07->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_bg_black_07 = Abyss_BG_black_07->AddComponent<MeshRenderer>();
		mr_abyss_bg_black_07->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_bg_black_07->SetMaterial(Resources::Find<Material>(L"Abyss_bg_black"));
		Abyss_BG_black_07->GetComponent<Transform>()->SetPosition(Vector3(63.f, -30.f, 0.9f));
		Abyss_BG_black_07->GetComponent<Transform>()->SetScale(Vector3(65.3f, 50.f, 0.f));



		Ground* Abyss_wall = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_wall);
		Abyss_wall->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_wall_01 = Abyss_wall->AddComponent<MeshRenderer>();
		mr_abyss_wall_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_wall_01->SetMaterial(Resources::Find<Material>(L"Abyss_Wall"));
		Abyss_wall->GetComponent<Transform>()->SetPosition(Vector3(76.6f, 15.f, 0.99999f));
		Abyss_wall->GetComponent<Transform>()->SetScale(Vector3(3.f, 30.f, 0.f));



		Ground* Abyss_Pricle_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_Pricle_01);
		Abyss_Pricle_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_prickle_01 = Abyss_Pricle_01->AddComponent<MeshRenderer>();
		mr_abyss_prickle_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_prickle_01->SetMaterial(Resources::Find<Material>(L"Abyss_Prickle_01"));
		Abyss_Pricle_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 2.5f, 0.999f));
		Abyss_Pricle_01->GetComponent<Transform>()->SetScale(Vector3(20.f, 1.f, 0.f));
		Abyss_Pricle_01->AddComponent<Collider2D>();


		Ground* Abyss_Pricle_under_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_Pricle_under_01);
		Abyss_Pricle_under_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_prickle_under_01 = Abyss_Pricle_under_01->AddComponent<MeshRenderer>();
		mr_abyss_prickle_under_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_prickle_under_01->SetMaterial(Resources::Find<Material>(L"Abyss_Floor_03"));
		Abyss_Pricle_under_01->GetComponent<Transform>()->SetPosition(Vector3(50.f, 0.f, 0.999f));
		Abyss_Pricle_under_01->GetComponent<Transform>()->SetScale(Vector3(10.f, 2.f, 0.f));
		


		Ground* Abyss_Pricle_right_01 = new Ground();
		AddGameObject(eLayerType::MonsterAttack, Abyss_Pricle_right_01);
		Abyss_Pricle_right_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_prickle_right_01 = Abyss_Pricle_right_01->AddComponent<MeshRenderer>();
		mr_abyss_prickle_right_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_prickle_right_01->SetMaterial(Resources::Find<Material>(L"Abyss_Prickle_right"));
		Abyss_Pricle_right_01->GetComponent<Transform>()->SetPosition(Vector3(55.f, 3.f, 0.99f));
		Abyss_Pricle_right_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 10.f, 0.f));
		Abyss_Pricle_right_01->GetComponent<Collider2D>()->SetSize(Vector2(1.f, 1.f));
		Abyss_Pricle_right_01->GroundTrap();


		Ground* Abyss_Pricle_over_01 = new Ground();
		AddGameObject(eLayerType::MonsterAttack, Abyss_Pricle_over_01);
		Abyss_Pricle_over_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_prickle_over_01 = Abyss_Pricle_over_01->AddComponent<MeshRenderer>();
		mr_abyss_prickle_over_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_prickle_over_01->SetMaterial(Resources::Find<Material>(L"Abyss_Prickle_over"));
		Abyss_Pricle_over_01->GetComponent<Transform>()->SetPosition(Vector3(50.f, 8.f, 0.9999f));
		Abyss_Pricle_over_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 10.f, 0.f));
		Abyss_Pricle_over_01->GetComponent<Collider2D>()->SetSize(Vector2(1.0f, 0.8f));
		Abyss_Pricle_over_01->GroundTrap();


		Ground* Abyss_floor_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_floor_01);
		Abyss_floor_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_floor_01 = Abyss_floor_01->AddComponent<MeshRenderer>();
		mr_abyss_floor_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_floor_01->SetMaterial(Resources::Find<Material>(L"Abyss_Floor_01"));
		Abyss_floor_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.999f));
		Abyss_floor_01->GetComponent<Transform>()->SetScale(Vector3(50.f, 2.f, 0.f));


		Ground* Abyss_floor_03 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_floor_03);
		Abyss_floor_03->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_floor_03 = Abyss_floor_03->AddComponent<MeshRenderer>();
		mr_abyss_floor_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_floor_03->SetMaterial(Resources::Find<Material>(L"Abyss_Floor_03"));
		Abyss_floor_03->GetComponent<Transform>()->SetPosition(Vector3(35.f, 4.f, 0.999f));
		Abyss_floor_03->GetComponent<Transform>()->SetScale(Vector3(20.f, 2.f, 0.f));


		Ground* Abyss_floor_04 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_floor_04);
		Abyss_floor_04->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_floor_04 = Abyss_floor_04->AddComponent<MeshRenderer>();
		mr_abyss_floor_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_floor_04->SetMaterial(Resources::Find<Material>(L"Abyss_Floor_04"));
		Abyss_floor_04->GetComponent<Transform>()->SetPosition(Vector3(70.f, 4.f, 0.999f));
		Abyss_floor_04->GetComponent<Transform>()->SetScale(Vector3(10.f, 10.f, 0.f));



		Ground* Abyss_C_floor_02_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_C_floor_02_01);
		Abyss_C_floor_02_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_c_floor_02_01 = Abyss_C_floor_02_01->AddComponent<MeshRenderer>();
		mr_abyss_c_floor_02_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_c_floor_02_01->SetMaterial(Resources::Find<Material>(L"Abyss_C_Floor_02"));
		Abyss_C_floor_02_01->GetComponent<Transform>()->SetPosition(Vector3(25.f, 2.f, 0.999f));
		Abyss_C_floor_02_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 6.f, 0.f));

		Ground* Abyss_C_floor_02_02 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_C_floor_02_02);
		Abyss_C_floor_02_02->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_c_floor_02_02 = Abyss_C_floor_02_02->AddComponent<MeshRenderer>();
		mr_abyss_c_floor_02_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_c_floor_02_02->SetMaterial(Resources::Find<Material>(L"Abyss_C_Floor_02"));
		Abyss_C_floor_02_02->GetComponent<Transform>()->SetPosition(Vector3(45.f, 1.99f, 0.999f));
		Abyss_C_floor_02_02->GetComponent<Transform>()->SetScale(Vector3(2.f, 6.f, 0.f));


		Ground* Abyss_C_floor_03_01 = new Ground();
		AddGameObject(eLayerType::Ground, Abyss_C_floor_03_01);
		Abyss_C_floor_03_01->SetName(L"Mune_BG");
		MeshRenderer* mr_abyss_c_floor_03_01 = Abyss_C_floor_03_01->AddComponent<MeshRenderer>();
		mr_abyss_c_floor_03_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_abyss_c_floor_03_01->SetMaterial(Resources::Find<Material>(L"Abyss_C_Floor_03"));
		Abyss_C_floor_03_01->GetComponent<Transform>()->SetPosition(Vector3(57.5f, 4.5f, 0.999999f));
		Abyss_C_floor_03_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 10.f, 0.f));


		GameObject* Radiance_in_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Radiance_in_01);
		Radiance_in_01->SetName(L"Mune_BG");
		MeshRenderer* mr_radiance_in_01 = Radiance_in_01->AddComponent<MeshRenderer>();
		mr_radiance_in_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_in_01->SetMaterial(Resources::Find<Material>(L"Radiance_In"));
		Radiance_in_01->GetComponent<Transform>()->SetPosition(Vector3(70.5f, 10.5f, 0.9999999f));
		Radiance_in_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 3.f, 0.f));
		Radiance_in_01->AddComponent<Light>();
		Radiance_in_01->GetComponent<Light>()->SetType(eLightType::Point);
		Radiance_in_01->GetComponent<Light>()->SetColor(Vector4::One);
		Radiance_in_01->GetComponent<Light>()->SetRadius(2.f);
		Radiance_in_01->AddComponent<Collider2D>();
		Radiance_in_01->AddComponent<SceneChangeScript>();
		Radiance_in_01->GetComponent<SceneChangeScript>()->SetTriggerName(L"AbyssToRadiance");

#pragma endregion

		
		UI_HUD* HUB = new UI_HUD();
		HUB->Initialize();
		std::vector<Health*> ob = HUB->GetHUDObj();




		Trap* tTrap = new Trap();
		AddGameObject(eLayerType::Ground, tTrap);
		tTrap->GetComponent<Transform>()->SetPosition(Vector3(63.5f, 0.f, 0.999999f));
		tTrap->GroundTrap();

		Trap* tTrap2 = new Trap();
		AddGameObject(eLayerType::Ground, tTrap2);
		tTrap2->GetComponent<Transform>()->SetPosition(Vector3(67.5f, 0.f, 0.999999f));
		tTrap2->GroundTrap();





		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);

		pPlayer->Initialize();
		pPlayer->GetComponent<PlayerScript>()->SetPlayer(pPlayer);
		pPlayer->GetComponent<Transform>()->SetPosition(Vector3(-20.0f, 15.f, 1.0001f));
		pPlayer->GetComponent<Light>()->SetRadius(3.f);
		//pPlayer->GetComponent<Transform>()->SetPosition(Vector3(-20.0f, 2.f, 1.0001f));
		pPlayer->GetComponent<PlayerScript>()->SetHUD(ob);
		pPlayer->GetComponent<PlayerScript>()->SetPlayerHUD(HUB);
		pPlayer->AddComponent<AudioListener>();
		RegisterPlayer(pPlayer);




		Baldur* Br = new Baldur();
		Br->Initialize();
		Br->GetComponent<Transform>()->SetPosition(Vector3(40.f, 15.f, 1.f));
		Br->SetScene(this);
		AddGameObject(eLayerType::Monster, Br);


		Baldur* Br2 = new Baldur();
		Br2->Initialize();
		Br2->GetComponent<Transform>()->SetPosition(Vector3(52.f, 30.f, 1.f));
		Br2->SetScene(this);
		AddGameObject(eLayerType::Monster, Br2);


		//Main Camera

		GameObject* camera = new GameObject();
		camera->SetName(L"PlayerCamera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cameraSr = camera->AddComponent<CameraScript>();
		cameraSr->SetPlayer(pPlayer);
		//cameraSr->SetBackGround(Start_BG);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		SetMainCamera(cameraComp);

		camera->AddComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"AbyssSound", L"..\\Resources\\Sound\\atrium.mp3"));

		m_SceneAS = camera->GetComponent<AudioSource>();

		SetCameraObj(camera);
		pPlayer->SetCurScene(this);


		//ui camera
		{
			GameObject* pCamera = new GameObject();
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::BackGround, false);
			pCameraComp->TurnLayerMask(eLayerType::Grid, false);
			pCameraComp->TurnLayerMask(eLayerType::Ground, false);
			pCameraComp->TurnLayerMask(eLayerType::LayeredObj, false);
			pCameraComp->TurnLayerMask(eLayerType::Player, false);
			pCameraComp->TurnLayerMask(eLayerType::Light, false);
			pCameraComp->TurnLayerMask(eLayerType::PlayerAttack, false);
			//pCamera->AddComponent<CameraScript>();
		}

		
		Radiance_in_01->GetComponent<SceneChangeScript>()->SetSceneLight(this);
	}

	void AbyssScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			SceneManager::LoadScene(L"BossScene");
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			SceneManager::LoadScene(L"RadianceScene");
		}
		
		Scene::Update();
		
	}

	void AbyssScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void AbyssScene::Render()
	{
		Scene::Render();
	}

	void AbyssScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		renderer::mainCamera = GetMainCamera();

		Scene::OnEnter();
	}

	void AbyssScene::OnExit()
	{
	//	SceneManager::Destory();
		//CollisionManager::Clear();

		Scene::OnExit();
		DestroyAll();

	}

}
