#pragma once

#include "AkStartGameScene.h"
#include "AkMeshRenderer.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkResources.h"
#include "AkSceneManager.h"
#include "AkInput.h"
#include "../Anack_Engine/AkGridScript.h"
#include "../Engine_SOURCE/AkCollider2D.h"
#include "../Anack_Engine/AkPlayerScript.h"
#include "AkObject.h"
#include "AkRenderer.h"
#include "AkCollisionManager.h"
#include "AkAnimator.h"
#include "AkLight.h"
#include "AkRigidBody.h"
#include "../Anack_Engine//AkGroundScript.h"
#include "../Anack_Engine/AkGround.h"
#include "AkCamera.h"
#include "../Anack_Engine/AkSceneChangeTrigger.h"
#include "../Anack_Engine/AkSceneChangeScript.h"
#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkGrass.h"
#include "AkParticleSystem.h"
#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkBaldur.h"
#include "AkAudioClip.h"
#include "AkAudioListener.h"
#include "../Anack_Engine/AkElderbug.h"
#include "../Anack_Engine/AkUI_NPC.h"
#include "../Anack_Engine/AkGrimmTrigger.h"
#include "../Anack_Engine/AkBenchTriggerScript.h"


namespace Ak
{
	using namespace object;

	StartGameScene::StartGameScene()
		
	{
		SetName(L"Start_Scene");
	}

	StartGameScene::~StartGameScene()
	{
	
	}

	void StartGameScene::Initialize()
	{
	
		
#pragma region BackGround

		//==============================================
		//BackGround
		//==============================================
		GameObject* Start_BG = Instantiate<GameObject>(Vector3(0.f, 5.f, 1.5f), Vector3(25.f, 25.f, 20.f), eLayerType::BackGround);
		Start_BG->SetName(L"StartBG");
		Start_BG->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Start_BGMR");



		


		GameObject* Town_BG02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG02);
		MeshRenderer* mr_town_bg02 = Town_BG02->AddComponent<MeshRenderer>();
		mr_town_bg02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg02->SetMaterial(Resources::Find<Material>(L"Town_BG_02"));
		Town_BG02->GetComponent<Transform>()->SetPosition(Vector3(10.f, -1.f, 1.2f));
		Town_BG02->GetComponent<Transform>()->SetScale(Vector3(8.f, 6.f, 0.f));



		GameObject* Town_BG03 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG03);
		MeshRenderer* mr_town_bg03 = Town_BG03->AddComponent<MeshRenderer>();
		mr_town_bg03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg03->SetMaterial(Resources::Find<Material>(L"Town_BG_03"));
		Town_BG03->GetComponent<Transform>()->SetPosition(Vector3(15.f, -2.f, 1.3f));
		Town_BG03->GetComponent<Transform>()->SetScale(Vector3(7.f, 7.f, 0.f));


		GameObject* Town_BG04 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG04);
		MeshRenderer* mr_town_bg04 = Town_BG04->AddComponent<MeshRenderer>();
		mr_town_bg04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg04->SetMaterial(Resources::Find<Material>(L"Town_BG_04"));
		Town_BG04->GetComponent<Transform>()->SetPosition(Vector3(0.f, -2.f, 1.3f));
		Town_BG04->GetComponent<Transform>()->SetScale(Vector3(13.f, 6.f, 0.f));

		GameObject* Town_BG02_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG02_02);
		MeshRenderer* mr_town_bg02_02 = Town_BG02_02->AddComponent<MeshRenderer>();
		mr_town_bg02_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg02_02->SetMaterial(Resources::Find<Material>(L"Town_BG_02"));
		Town_BG02_02->GetComponent<Transform>()->SetPosition(Vector3(-3.7f, -0.8f, 1.30022f));
		Town_BG02_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 3.f, 0.f));

		GameObject* Town_BG01_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG01_02);
		MeshRenderer* mr_town_bg01_02 = Town_BG01_02->AddComponent<MeshRenderer>();
		mr_town_bg01_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg01_02->SetMaterial(Resources::Find<Material>(L"Town_BG_01"));
		Town_BG01_02->GetComponent<Transform>()->SetPosition(Vector3(-1.f, -1.5f, 1.30023f));
		Town_BG01_02->GetComponent<Transform>()->SetScale(Vector3(6.f, 6.f, 0.f));

		GameObject* Town_BG_05 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG_05);
		MeshRenderer* mr_town_bg05 = Town_BG_05->AddComponent<MeshRenderer>();
		mr_town_bg05->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg05->SetMaterial(Resources::Find<Material>(L"Town_BG_05"));
		Town_BG_05->GetComponent<Transform>()->SetPosition(Vector3(30.f, 2.f, 1.30024f));
		Town_BG_05->GetComponent<Transform>()->SetScale(Vector3(6.f, 6.f, 0.f));

		GameObject* Town_BG_06 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG_06);
		MeshRenderer* mr_town_bg06 = Town_BG_06->AddComponent<MeshRenderer>();
		mr_town_bg06->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg06->SetMaterial(Resources::Find<Material>(L"Town_BG_06"));
		Town_BG_06->GetComponent<Transform>()->SetPosition(Vector3(27.f, -2.f, 1.30023f));
		Town_BG_06->GetComponent<Transform>()->SetScale(Vector3(8.f, 10.f, 0.f));


		GameObject* Town_BG_07 = new GameObject();
		AddGameObject(eLayerType::BackGround, Town_BG_07);
		MeshRenderer* mr_town_bg07 = Town_BG_07->AddComponent<MeshRenderer>();
		mr_town_bg07->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bg07->SetMaterial(Resources::Find<Material>(L"Town_BG_07"));
		Town_BG_07->GetComponent<Transform>()->SetPosition(Vector3(33.f, -2.f, 1.30023f));
		Town_BG_07->GetComponent<Transform>()->SetScale(Vector3(6.f, 6.f, 0.f));



#pragma endregion

#pragma region	Grass

		Grass* Grass_01 = new Grass();
		AddGameObject(eLayerType::LayeredObj, Grass_01);
		//MeshRenderer* mr_grass_01 = Grass_01->AddComponent<MeshRenderer>();
		Grass_01->GetComponent<Transform>()->SetPosition(Vector3(-7.f, -3.4f, 0.5f));
		Grass_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 5.f, 0.f));

		Grass* Grass_01_01 = new Grass();
		AddGameObject(eLayerType::LayeredObj, Grass_01_01);
		//MeshRenderer* mr_grass_01 = Grass_01->AddComponent<MeshRenderer>();
		Grass_01_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, -3.4f, 0.5f));
		Grass_01_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 5.f, 0.f));


		Grass* Grass_02 = new Grass();
		AddGameObject(eLayerType::LayeredObj, Grass_02);
		//MeshRenderer* mr_grass_01 = Grass_01->AddComponent<MeshRenderer>();
		Grass_02->GetComponent<Transform>()->SetPosition(Vector3(-6.f, -3.4f, 0.5f));
		Grass_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 5.f, 0.f));
		Grass_02->GetComponent<Animator>()->PlayAnimation(L"Grass_02", true);

		Grass* Grass_02_01 = new Grass();
		AddGameObject(eLayerType::LayeredObj, Grass_02_01);
		//MeshRenderer* mr_grass_01 = Grass_01->AddComponent<MeshRenderer>();
		Grass_02_01->GetComponent<Transform>()->SetPosition(Vector3(22.5f, -3.4f, 0.5f));
		Grass_02_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 5.f, 0.f));
		Grass_02_01->GetComponent<Animator>()->PlayAnimation(L"Grass_02", true);

		Grass* Grass_03 = new Grass();
		AddGameObject(eLayerType::LayeredObj, Grass_03);
		//MeshRenderer* mr_grass_01 = Grass_01->AddComponent<MeshRenderer>();
		Grass_03->GetComponent<Transform>()->SetPosition(Vector3(23.f, -3.0f, 0.5f));
		Grass_03->GetComponent<Transform>()->SetScale(Vector3(2.f, 3.f, 0.f));
		Grass_03->GetComponent<Animator>()->PlayAnimation(L"Grass_03", true);



#pragma endregion

#pragma region Layered


		GameObject* Town_House_Open = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_House_Open);
		MeshRenderer* mr_town_house_open = Town_House_Open->AddComponent<MeshRenderer>();
		mr_town_house_open->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_house_open->SetMaterial(Resources::Find<Material>(L"Town_House_Open"));
		Town_House_Open->GetComponent<Transform>()->SetPosition(Vector3(17.f, -1.f, 1.0003f));
		Town_House_Open->GetComponent<Transform>()->SetScale(Vector3(6.f, 6.f, 0.f));

		GameObject* Town_House_Close = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_House_Close);
		MeshRenderer* mr_town_house_close = Town_House_Close->AddComponent<MeshRenderer>();
		mr_town_house_close->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_house_close->SetMaterial(Resources::Find<Material>(L"Town_House_Close"));
		Town_House_Close->GetComponent<Transform>()->SetPosition(Vector3(17.f, -2.f, 1.00029f));
		Town_House_Close->GetComponent<Transform>()->SetScale(Vector3(6.f, 5.f, 0.f));
		m_GrimmDoor = Town_House_Close;


		GrimmTrigger* GT = new GrimmTrigger();
		GT->GetComponent<Transform>()->SetPosition(Vector3(16.5f,-2.f,1.000029));
		AddGameObject(eLayerType::Trigger, GT);


		GameObject* Town_House_02 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_House_02);
		MeshRenderer* mr_town_house_02 = Town_House_02->AddComponent<MeshRenderer>();
		mr_town_house_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_house_02->SetMaterial(Resources::Find<Material>(L"Town_House_02"));
		Town_House_02->GetComponent<Transform>()->SetPosition(Vector3(21.f, -1.5f, 1.00028f));
		Town_House_02->GetComponent<Transform>()->SetScale(Vector3(6.f, 5.f, 0.f));


		GameObject* Town_Layered_01 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_Layered_01);
		MeshRenderer* mr_town_layered_01 = Town_Layered_01->AddComponent<MeshRenderer>();
		mr_town_layered_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_layered_01->SetMaterial(Resources::Find<Material>(L"Town_layered_01"));
		Town_Layered_01->GetComponent<Transform>()->SetPosition(Vector3(12.f, -4.f, 0.997f));
		Town_Layered_01->GetComponent<Transform>()->SetScale(Vector3(4.5f, 3.5f, 0.f));


		GameObject* Town_Layered_02 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_Layered_02);
		MeshRenderer* mr_town_layered_02 = Town_Layered_02->AddComponent<MeshRenderer>();
		mr_town_layered_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_layered_02->SetMaterial(Resources::Find<Material>(L"Town_layered_02"));
		Town_Layered_02->GetComponent<Transform>()->SetPosition(Vector3(-3.f, -4.f, 0.997f));
		Town_Layered_02->GetComponent<Transform>()->SetScale(Vector3(2.5f, 3.2f, 0.f));

		GameObject* Town_Layered_03 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_Layered_03);
		MeshRenderer* mr_town_layered_03 = Town_Layered_03->AddComponent<MeshRenderer>();
		mr_town_layered_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_layered_03->SetMaterial(Resources::Find<Material>(L"Town_layered_03"));
		Town_Layered_03->GetComponent<Transform>()->SetPosition(Vector3(17.f, -4.f, 0.997f));
		Town_Layered_03->GetComponent<Transform>()->SetScale(Vector3(1.f, 2.f, 0.f));

		GameObject* Town_Layered_03_01 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_Layered_03_01);
		MeshRenderer* mr_town_layered_03_01 = Town_Layered_03_01->AddComponent<MeshRenderer>();
		mr_town_layered_03_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_layered_03_01->SetMaterial(Resources::Find<Material>(L"Town_layered_03"));
		Town_Layered_03_01->GetComponent<Transform>()->SetPosition(Vector3(-6.3f, -3.f, 0.997f));
		Town_Layered_03_01->GetComponent<Transform>()->SetScale(Vector3(0.5f, 2.2f, 0.f));

		GameObject* Town_Layered_04 = new GameObject();
		AddGameObject(eLayerType::LayeredObj, Town_Layered_04);
		MeshRenderer* mr_town_layered_04 = Town_Layered_04->AddComponent<MeshRenderer>();
		mr_town_layered_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_layered_04->SetMaterial(Resources::Find<Material>(L"Town_layered_04"));
		Town_Layered_04->GetComponent<Transform>()->SetPosition(Vector3(25.3f, -5.f, 0.997f));
		Town_Layered_04->GetComponent<Transform>()->SetScale(Vector3(2.5f, 2.f, 0.f));




		GameObject* Town_left_wall_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_left_wall_01);
		MeshRenderer* mr_town_left_01 = Town_left_wall_01->AddComponent<MeshRenderer>();
		mr_town_left_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_left_01->SetMaterial(Resources::Find<Material>(L"Town_left_wall01"));
		Town_left_wall_01->GetComponent<Transform>()->SetPosition(Vector3(-13.3f, -1.3f, 0.997f));
		Town_left_wall_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 5.f, 0.f));
		/*Collider2D* Cr_left_wall = Town_left_wall_01->AddComponent<Collider2D>();
		Cr_left_wall->SetSize(Vector2(0.8, 1.f));*/

		GameObject* Town_left_wall_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_left_wall_02);
		MeshRenderer* mr_town_left_02 = Town_left_wall_02->AddComponent<MeshRenderer>();
		mr_town_left_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_left_02->SetMaterial(Resources::Find<Material>(L"Town_left_wall01"));
		Town_left_wall_02->GetComponent<Transform>()->SetPosition(Vector3(43.f, -2.3f, 1.31f));
		Town_left_wall_02->GetComponent<Transform>()->SetScale(Vector3(5.f, 5.f, 0.f));
		Collider2D* Cr_left_wall_02 = Town_left_wall_02->AddComponent<Collider2D>();


		GameObject* Town_right_wall_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_right_wall_01);
		MeshRenderer* mr_town_right_01 = Town_right_wall_01->AddComponent<MeshRenderer>();
		mr_town_right_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_right_01->SetMaterial(Resources::Find<Material>(L"Town_right_wall_01"));
		Town_right_wall_01->GetComponent<Transform>()->SetPosition(Vector3(40.f, -1.8f, 1.3f));
		Town_right_wall_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 6.f, 0.f));
		

#pragma endregion

#pragma region well

		GameObject* Well_top = new GameObject();
		AddGameObject(eLayerType::Ground, Well_top);
		MeshRenderer* mr_well_top = Well_top->AddComponent<MeshRenderer>();
		mr_well_top->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_well_top->SetMaterial(Resources::Find<Material>(L"Well_top"));
		Well_top->GetComponent<Transform>()->SetPosition(Vector3(30.f, -3.0f, 1.0001f));
		Well_top->GetComponent<Transform>()->SetScale(Vector3(2.5f, 4.f, 0.f));




		GameObject* Well_floor = new GameObject();
		AddGameObject(eLayerType::Ground, Well_floor);
		MeshRenderer* mr_well_floor = Well_floor->AddComponent<MeshRenderer>();
		mr_well_floor->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_well_floor->SetMaterial(Resources::Find<Material>(L"Well_floor"));
		Well_floor->GetComponent<Transform>()->SetPosition(Vector3(30.5f, -6.4f, 0.998f));
		Well_floor->GetComponent<Transform>()->SetScale(Vector3(3.5f, 5.f, 0.f));



		GameObject* Well_back = new GameObject();
		AddGameObject(eLayerType::Ground, Well_back);
		MeshRenderer* mr_well_back = Well_back->AddComponent<MeshRenderer>();
		mr_well_back->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_well_back->SetMaterial(Resources::Find<Material>(L"Well_back"));
		Well_back->GetComponent<Transform>()->SetPosition(Vector3(29.5f, -5.f, 0.999f));
		Well_back->GetComponent<Transform>()->SetScale(Vector3(2.f, 1.f, 0.f));


#pragma endregion

#pragma region floor

		Ground* Town_Floor_long01 = new Ground();
		Town_Floor_long01->SetName(L"Floor01");
		AddGameObject(eLayerType::Ground, Town_Floor_long01);
		MeshRenderer* mr_floor_long01 = Town_Floor_long01->AddComponent<MeshRenderer>();
		mr_floor_long01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long01->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long01->GetComponent<Transform>()->SetPosition(Vector3(-8.2f, -4.23f, 0.999f));
		Town_Floor_long01->GetComponent<Transform>()->SetScale(Vector3(15.f, 1.f, 0.f));
		


		Ground* Town_Floor_long02 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_long02);
		MeshRenderer* mr_floor_long02 = Town_Floor_long02->AddComponent<MeshRenderer>();
		mr_floor_long02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long02->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long02->GetComponent<Transform>()->SetPosition(Vector3(6.5f, -4.27f, 0.999f));
		Town_Floor_long02->GetComponent<Transform>()->SetScale(Vector3(15.f, 1.f, 0.f));
		

		Ground* Town_Floor_long03 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_long03);
		MeshRenderer* mr_floor_long03 = Town_Floor_long03->AddComponent<MeshRenderer>();
		mr_floor_long03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long03->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long03->GetComponent<Transform>()->SetPosition(Vector3(15.5f, -4.27f, 0.999f));
		Town_Floor_long03->GetComponent<Transform>()->SetScale(Vector3(15.f, 1.f, 0.f));
		

		Ground* Town_Floor_long04 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_long04);
		MeshRenderer* mr_floor_long04 = Town_Floor_long04->AddComponent<MeshRenderer>();
		mr_floor_long04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long04->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long04->GetComponent<Transform>()->SetPosition(Vector3(39.f, -5.f, 0.999f));
		Town_Floor_long04->GetComponent<Transform>()->SetScale(Vector3(15.f, 1.f, 0.f));



		Ground* Town_Floor_size06_01 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_size06_01);
		MeshRenderer* mr_floor_size06_01 = Town_Floor_size06_01->AddComponent<MeshRenderer>();
		mr_floor_size06_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_size06_01->SetMaterial(Resources::Find<Material>(L"Town_Floor_size06"));
		Town_Floor_size06_01->GetComponent<Transform>()->SetPosition(Vector3(26.f, -5.f, 0.999f));
		Town_Floor_size06_01->GetComponent<Transform>()->SetScale(Vector3(6.f, 1.f, 0.f));


		GameObject* Town_Under_Wall_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_Under_Wall_01);
		MeshRenderer* mr_town_under_wall01 = Town_Under_Wall_01->AddComponent<MeshRenderer>();
		mr_town_under_wall01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_under_wall01->SetMaterial(Resources::Find<Material>(L"Town_Under_Wall01"));
		Town_Under_Wall_01->GetComponent<Transform>()->SetPosition(Vector3(3.5f, -7.2f, 0.998f));
		Town_Under_Wall_01->GetComponent<Transform>()->SetScale(Vector3(42.f, 6.f, 0.f));

		GameObject* Town_Under_Wall_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_Under_Wall_02);
		MeshRenderer* mr_town_under_wall02 = Town_Under_Wall_02->AddComponent<MeshRenderer>();
		mr_town_under_wall02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_under_wall02->SetMaterial(Resources::Find<Material>(L"Town_Under_Wall01"));
		Town_Under_Wall_02->GetComponent<Transform>()->SetPosition(Vector3(25.f, -7.2f, 0.998f));
		Town_Under_Wall_02->GetComponent<Transform>()->SetScale(Vector3(8.f, 6.f, 0.f));

		GameObject* Town_Under_Wall_03 = new GameObject();
		AddGameObject(eLayerType::Ground, Town_Under_Wall_03);
		MeshRenderer* mr_town_under_wall03 = Town_Under_Wall_03->AddComponent<MeshRenderer>();
		mr_town_under_wall03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_under_wall03->SetMaterial(Resources::Find<Material>(L"Town_Under_Wall01"));
		Town_Under_Wall_03->GetComponent<Transform>()->SetPosition(Vector3(40.f, -7.3f, 0.998f));
		Town_Under_Wall_03->GetComponent<Transform>()->SetScale(Vector3(18.f, 6.f, 0.f));

#pragma endregion

#pragma region bench


		GameObject* town_bench = new GameObject();
		AddGameObject(eLayerType::Trigger, town_bench);
		MeshRenderer* mr_town_bench = town_bench->AddComponent<MeshRenderer>();
		mr_town_bench->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_bench->SetMaterial(Resources::Find<Material>(L"town_bench"));
		town_bench->GetComponent<Transform>()->SetPosition(Vector3(5.f, -3.3f, 1.0002f));
		town_bench->GetComponent<Transform>()->SetScale(Vector3(2.2f, 1.f, 0.f));
		town_bench->AddComponent<Collider2D>();
		//town_bench->AddComponent<BenchTriggerScript>();
		town_bench->GetComponent<Collider2D>()->SetName(L"Bench_Trigger");




		GameObject* town_lamp = new GameObject();
		AddGameObject(eLayerType::Ground, town_lamp);
		MeshRenderer* mr_town_lamp = town_lamp->AddComponent<MeshRenderer>();
		mr_town_lamp->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_lamp->SetMaterial(Resources::Find<Material>(L"town_lamp"));
		town_lamp->GetComponent<Transform>()->SetPosition(Vector3(6.3f, -1.1f, 1.000f));
		town_lamp->GetComponent<Transform>()->SetScale(Vector3(1.7f, 5.5f, 0.f));


		GameObject* town_lamp02 = new GameObject();
		AddGameObject(eLayerType::Ground, town_lamp02);
		MeshRenderer* mr_town_lamp02 = town_lamp02->AddComponent<MeshRenderer>();
		mr_town_lamp02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_town_lamp02->SetMaterial(Resources::Find<Material>(L"town_lamp02"));
		town_lamp02->GetComponent<Transform>()->SetPosition(Vector3(-9.3f, -2.f, 1.000f));
		town_lamp02->GetComponent<Transform>()->SetScale(Vector3(1.7f, 5.5f, 0.f));




#pragma endregion

#pragma region Light

		GameObject* Start_Light_01 = new GameObject();
		Start_Light_01->SetName(L"Light");
		AddGameObject(eLayerType::Light, Start_Light_01);
		MeshRenderer* mr_start_light_01 = Start_Light_01->AddComponent<MeshRenderer>();
		mr_start_light_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_start_light_01->SetMaterial(Resources::Find<Material>(L"Start_Light"));
		Start_Light_01->GetComponent<Transform>()->SetPosition(Vector3(-8.65f, -0.13f, 1.0001f));
		Start_Light_01->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 0.f));

		Light* smileLight = Start_Light_01->AddComponent<Light>();
		smileLight->SetType(eLightType::Point);
		smileLight->SetColor(Vector4(0.0f, 0.0f, 1.0f, 0.6f));
		smileLight->SetRadius(2.0f);


		GameObject* Start_Light_02 = new GameObject();
		Start_Light_02->SetName(L"Light02");
		AddGameObject(eLayerType::Light, Start_Light_02);
		MeshRenderer* mr_start_light_02 = Start_Light_02->AddComponent<MeshRenderer>();
		mr_start_light_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_start_light_02->SetMaterial(Resources::Find<Material>(L"Start_Light"));
		Start_Light_02->GetComponent<Transform>()->SetPosition(Vector3(-10.f, -1.f, 1.0001f));
		Start_Light_02->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 0.f));

		Light* smileLight02 = Start_Light_02->AddComponent<Light>();
		smileLight02->SetType(eLightType::Point);
		smileLight02->SetColor(Vector4(0.0f, 0.0f, 1.0f, 0.6f));
		smileLight02->SetRadius(2.0f);



#pragma endregion

#pragma region frog


		GameObject* pParticle1 = new GameObject();
		pParticle1->GetComponent<Transform>()->SetPosition(0.0f, -3.f, 1.00f);
		pParticle1->GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);
		pParticle1->AddComponent<Collider2D>();
		ParticleSystem* ps2 = pParticle1->AddComponent<ParticleSystem>();

		ps2->GetMaterial()->SetTexture(Resources::Find<Texture>(L"Default_Particle"));
		ps2->SetParticleCount(60);
		ps2->SetParticleSpeed(3.f);
		ps2->SetParticleDirection(Vector4(1.f, 0.5f, 0.f, 0.f));
		ps2->SetParticleDestory(30.f);
		ps2->SetParticleRandom(100.f);
		ps2->SetRandomZ(true);
		ps2->SetSize(2);
		AddGameObject(eLayerType::LayeredObj, pParticle1);



		//GameObject* pfrog = new GameObject();
		//pfrog->GetComponent<Transform>()->SetPosition(-18.0f, 0.f, 1.00f);
		//pfrog->GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);
		//pfrog->AddComponent<Collider2D>();
		//ParticleSystem* ps1 = pfrog->AddComponent<ParticleSystem>();

		//ps1->GetMaterial()->SetTexture(Resources::Find<Texture>(L"hot_spring_smoke"));
		//ps1->SetParticleCount(3);
		//ps1->SetParticleSpeed(10.f);
		//ps1->SetParticleDirection(Vector4(1.f, 0.f, 0.f, 0.f));
		//ps1->SetParticleDestory(20.f);
		//ps1->SetParticleRandom(100.f);
		////ps1->SetRandomZ(true);
		//ps1->SetRotation(0.f, 30.f);
		//ps1->SetSize(20);
		//AddGameObject(eLayerType::LayeredObj, pfrog);




#pragma endregion


		UI_HUD* HUB = new UI_HUD();
		HUB->Initialize();
		std::vector<Health*> ob = HUB->GetHUDObj();

		Elderbug* pElderbug = new Elderbug();
		AddGameObject(eLayerType::NPC, pElderbug);


		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);
		
		pPlayer->Initialize();
		pPlayer->GetComponent<Transform>()->SetPosition(Vector3(-8.0f, 3.7f, 1.0001f));
		Light* PlayerLight = pPlayer->AddComponent<Light>();
		PlayerLight->SetType(eLightType::Point);
		PlayerLight->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.6f));
		PlayerLight->SetRadius(8.0f);
		
		pPlayer->AddComponent<AudioListener>();
		pPlayer->GetComponent<PlayerScript>()->SetHUD(ob);
		pPlayer->GetComponent<PlayerScript>()->SetPlayerHUD(HUB);
		pPlayer->SetPlayerHud(HUB);

		RegisterPlayer(pPlayer);


		//Main Camera

		GameObject* camera = new GameObject();
		camera->SetName(L"PlayerCamera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		Camera*  cameraComp = camera->AddComponent<Camera>();
		CameraScript* cameraSr = camera->AddComponent<CameraScript>();
		cameraSr->SetPlayer(pPlayer);
		cameraSr->SetBackGround(Start_BG);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		SetMainCamera(cameraComp);
		
		camera->AddComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Abyss", L"..\\Resources\\Sound\\Crossroads.mp3"));
		m_SceneAS = camera->GetComponent<AudioSource>();



	
	
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
			pCameraComp->TurnLayerMask(eLayerType::NPC, false);
			pCameraComp->TurnLayerMask(eLayerType::Trigger, false);
			//pCamera->AddComponent<CameraScript>();
		}

		
#pragma region Trigger

		SceneChangeTrigger* pSceneChagneTrigger = new SceneChangeTrigger();
		pSceneChagneTrigger->SetName(L"StartTrigger");
		pSceneChagneTrigger->Initialize();
		AddGameObject(eLayerType::Trigger, pSceneChagneTrigger);


		pSceneChagneTrigger->GetComponent<Transform>()->SetScale(5.f, 10.f, 0.f);
		pSceneChagneTrigger->GetComponent<Transform>()->SetPosition(30.f, -11.f, 1.00f);
		pSceneChagneTrigger->GetComponent<SceneChangeScript>()->SetSceneLight(this);
		


#pragma endregion

	}

	void StartGameScene::HUDInitialize()
	{
		

	
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

	void StartGameScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trigger, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::NPC, true);

		renderer::mainCamera = GetMainCamera();

		std::wstring Pre_S = SceneManager::GetPreSceneName();

		Scene::OnEnter();

		if (Pre_S == L"BattleScene")
		{
			mPlayer->GetComponent<Transform>()->SetPositionXY(Vector2(33.f, 3.f));
		}
		else if (Pre_S == L"BossScene")
		{
			mPlayer->GetComponent<Transform>()->SetPositionXY(Vector2(16.5f, -3.f));
		}


		//Scene Enter 시 코인을 보유하고 있으면 GrimmDoorOpen
		if (mPlayer->GetCoin())
		{
			SceneManager::DestoryObj(m_GrimmDoor);
			delete m_GrimmDoor;
			m_GrimmDoor = nullptr;
		}

		if (SceneManager::GetDeadState())
		{
			mPlayer->GetComponent<PlayerScript>()->RestToggleOn();
		}

	}

	void StartGameScene::OnExit()
	{
		
		//SceneManager::Destory();
		//SceneManager::Release();
		Scene::OnExit();
		DestroyAll();
		
		//CollisionManager::Clear();

		

	}

}