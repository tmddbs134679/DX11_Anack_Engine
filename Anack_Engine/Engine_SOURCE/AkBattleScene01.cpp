#pragma once

#include "AkBattleScene01.h"
#include "AkMeshRenderer.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkResources.h"
#include "../Anack_Engine/AkPlayerScript.h"
#include "AkRenderer.h"
#include "AkInput.h"
#include "AkSceneManager.h"
#include "AkAnimator.h"
#include "AkCollisionManager.h"
#include "../Anack_Engine/AkGround.h"
#include "../Anack_Engine/AkGround.h"
#include "../Anack_Engine/AkBaldur.h"
#include "../Anack_Engine/AkHunter.h"
#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkBox.h"
#include "../Anack_Engine/AkCoin.h"
#include "../Anack_Engine/AkSceneChangeTrigger.h"
#include "../Anack_Engine//AkSceneChangeScript.h"
#include "AkAudioClip.h"
#include "AkAudioListener.h"
#include "../Anack_Engine/AkBattleToStartTrigger.h"



namespace Ak
{
	BattleScene01::BattleScene01()
	{
		SetName(L"BattleScene");
	}

	BattleScene01::~BattleScene01()
	{
	}

	void BattleScene01::Initialize()
	{

#pragma region BackGround

		GameObject* Battle_BG01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Battle_BG01);
		Battle_BG01->SetName(L"Battle_bg"); 
		MeshRenderer* mr = Battle_BG01->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BG01"));
		Battle_BG01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.5f));
		Battle_BG01->GetComponent<Transform>()->SetScale(Vector3(25.f, 13.5f, 10.f));
		

		GameObject* BT_layered_bg_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_layered_bg_01);
		MeshRenderer* mr_layered_bg_01 = BT_layered_bg_01->AddComponent<MeshRenderer>();
		mr_layered_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_layered_bg_01->SetMaterial(Resources::Find<Material>(L"BT_Layered_01"));
		BT_layered_bg_01->GetComponent<Transform>()->SetPosition(Vector3(1.f, -23.f, 0.99f));
		BT_layered_bg_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 35.f, 0.f));


		GameObject* BT_layered_bg_02 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_layered_bg_02);
		MeshRenderer* mr_layered_bg_02 = BT_layered_bg_02->AddComponent<MeshRenderer>();
		mr_layered_bg_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_layered_bg_02->SetMaterial(Resources::Find<Material>(L"BT_Layered_01"));
		BT_layered_bg_02->GetComponent<Transform>()->SetPosition(Vector3(-35.5f, -15.f, 0.8f));
		BT_layered_bg_02->GetComponent<Transform>()->SetScale(Vector3(5.f, 40.f, 0.f));


		GameObject* BG_Chain_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BG_Chain_01);
		MeshRenderer* mr_bg_chain_01 = BG_Chain_01->AddComponent<MeshRenderer>();
		mr_bg_chain_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bg_chain_01->SetMaterial(Resources::Find<Material>(L"BT_BG_Chain"));
		BG_Chain_01->GetComponent<Transform>()->SetPosition(Vector3(-10.f, 0.f, 0.999f));
		BG_Chain_01->GetComponent<Transform>()->SetScale(Vector3(0.5f, 25.f, 0.f));

		GameObject* BG_Chain_02 = new GameObject();
		AddGameObject(eLayerType::Ground, BG_Chain_02);
		MeshRenderer* mr_bg_chain_02 = BG_Chain_02->AddComponent<MeshRenderer>();
		mr_bg_chain_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bg_chain_02->SetMaterial(Resources::Find<Material>(L"BT_BG_Chain"));
		BG_Chain_02->GetComponent<Transform>()->SetPosition(Vector3(-15.f, 0.f, 0.999f));
		BG_Chain_02->GetComponent<Transform>()->SetScale(Vector3(0.5f, 25.f, 0.f));



#pragma endregion



#pragma region Battle_wall


		Ground* BT_Wall_01 = new Ground();
		AddGameObject(eLayerType::Ground, BT_Wall_01);
		MeshRenderer* mr_bt_wall_01 = BT_Wall_01->AddComponent<MeshRenderer>();
		mr_bt_wall_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_wall_01->SetMaterial(Resources::Find<Material>(L"Bt_wall01"));
		BT_Wall_01->GetComponent<Transform>()->SetPosition(Vector3(4.f, 4.2f, 0.99f));
		BT_Wall_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 5.5f, 0.f));


		Ground* BT_Wall_02 = new Ground();
		AddGameObject(eLayerType::Ground, BT_Wall_02);
		MeshRenderer* mr_bt_wall_02 = BT_Wall_02->AddComponent<MeshRenderer>();
		mr_bt_wall_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_wall_02->SetMaterial(Resources::Find<Material>(L"Bt_wall_bg02"));
		BT_Wall_02->GetComponent<Transform>()->SetPosition(Vector3(-4.f, 3.9f, 0.79f));
		BT_Wall_02->GetComponent<Transform>()->SetScale(Vector3(5.f, 5.f, 0.f));



		GameObject* BT_Wall_BG_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_Wall_BG_01);
		MeshRenderer* mr_bt_wall_bg_01 = BT_Wall_BG_01->AddComponent<MeshRenderer>();
		mr_bt_wall_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_wall_bg_01->SetMaterial(Resources::Find<Material>(L"Bt_wall_bg01"));
		BT_Wall_BG_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.0f, 1.000f));
		BT_Wall_BG_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 7.f, 0.f));


		Ground* BT_Wall_first = new Ground();
		AddGameObject(eLayerType::Ground, BT_Wall_first);
		MeshRenderer* mr_bt_wall_first = BT_Wall_first->AddComponent<MeshRenderer>();
		mr_bt_wall_first->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_wall_first->SetMaterial(Resources::Find<Material>(L"BT_Wall_right_02"));
		BT_Wall_first->GetComponent<Transform>()->SetPosition(Vector3(5.7f, -1.f, 0.8f));
		BT_Wall_first->GetComponent<Transform>()->SetScale(Vector3(1.4f, 5.f, 0.f));



		GameObject* BT_Chain_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_Chain_01);
		MeshRenderer* mr_bt_chain_01 = BT_Chain_01->AddComponent<MeshRenderer>();
		mr_bt_chain_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_chain_01->SetMaterial(Resources::Find<Material>(L"BT_Chain"));
		BT_Chain_01->GetComponent<Transform>()->SetPosition(Vector3(0.f, 1.9f, 0.999f));
		BT_Chain_01->GetComponent<Transform>()->SetScale(Vector3(0.2f, 12.f, 0.f));

		Ground* Town_Floor_long01 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_long01);
		MeshRenderer* mr_floor_long01 = Town_Floor_long01->AddComponent<MeshRenderer>();
		mr_floor_long01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long01->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long01->GetComponent<Transform>()->SetPosition(Vector3(0.2f, -4.f, 0.999f));
		Town_Floor_long01->GetComponent<Transform>()->SetScale(Vector3(15.f, 1.f, 0.f));

		Town_Floor_long01->AddComponent<Collider2D>();


		//아래 바닥
		Ground* Town_Floor_long02 = new Ground();
		AddGameObject(eLayerType::Ground, Town_Floor_long02);
		MeshRenderer* mr_floor_long02 = Town_Floor_long02->AddComponent<MeshRenderer>();
		mr_floor_long02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_long02->SetMaterial(Resources::Find<Material>(L"Town_Floor_long"));
		Town_Floor_long02->GetComponent<Transform>()->SetPosition(Vector3(-17.f, -36.f, 0.999f));
		Town_Floor_long02->GetComponent<Transform>()->SetScale(Vector3(30.f, 2.f, 0.f));

		Ground* wall_cd = new Ground();
		AddGameObject(eLayerType::Ground, wall_cd);
		wall_cd->GetComponent<Transform>()->SetPosition(Vector3(-1.8f, -34.2f, 0.8999f));
		wall_cd->GetComponent<Transform>()->SetScale(Vector3(1.f, 3.f, 0.f));
		wall_cd->AddComponent<Collider2D>();



		GameObject* Black_BG01 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG01);
		MeshRenderer* mr_black_bg_01 = Black_BG01->AddComponent<MeshRenderer>();
		mr_black_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_01->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG01->GetComponent<Transform>()->SetPosition(Vector3(-18.f, -40.f, 0.9998f));
		Black_BG01->GetComponent<Transform>()->SetScale(Vector3(32.f, 10.f, 0.f));



		GameObject* Black_BG02 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG02);
		MeshRenderer* mr_black_bg_02 = Black_BG02->AddComponent<MeshRenderer>();
		mr_black_bg_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_02->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG02->GetComponent<Transform>()->SetPosition(Vector3(2.f, -25.f, 0.999f));
		Black_BG02->GetComponent<Transform>()->SetScale(Vector3(13.f, 42.f, 0.f));

		GameObject* Black_BG03 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG03);
		MeshRenderer* mr_black_bg_03 = Black_BG03->AddComponent<MeshRenderer>();
		mr_black_bg_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_03->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG03->GetComponent<Transform>()->SetPosition(Vector3(-38.f, -15.f, 0.99999f));
		Black_BG03->GetComponent<Transform>()->SetScale(Vector3(10.f, 60.f, 0.f));


		GameObject* Black_BG04 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG04);
		MeshRenderer* mr_black_bg_04 = Black_BG04->AddComponent<MeshRenderer>();
		mr_black_bg_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_04->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG04->GetComponent<Transform>()->SetPosition(Vector3(-20.f, 15.f, 0.99998f));
		Black_BG04->GetComponent<Transform>()->SetScale(Vector3(50.f, 10.f, 0.f));

		GameObject* Black_BG05 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG05);
		MeshRenderer* mr_black_bg_05 = Black_BG05->AddComponent<MeshRenderer>();
		mr_black_bg_05->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_05->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG05->GetComponent<Transform>()->SetPosition(Vector3(10.f, 16.f, 0.9999f));
		Black_BG05->GetComponent<Transform>()->SetScale(Vector3(30.f, 20.f, 0.f));



		GameObject* BT_right_wall_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_right_wall_01);
		MeshRenderer* mr_right_wall_01 = BT_right_wall_01->AddComponent<MeshRenderer>();
		mr_right_wall_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_right_wall_01->SetMaterial(Resources::Find<Material>(L"BT_Wall_right_01"));
		BT_right_wall_01->GetComponent<Transform>()->SetPosition(Vector3(-5.6f, -6.f, 0.999f));
		BT_right_wall_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 3.f, 0.f));


		Ground* BT_right_wall_02 = new Ground();
		BT_right_wall_02->GetComponent<Collider2D>()->SetCenter(Vector2(0.2f, 0.f));
		BT_right_wall_02->GetComponent<Collider2D>()->Initialize();
		AddGameObject(eLayerType::Ground, BT_right_wall_02);
		MeshRenderer* mr_right_wall_02 = BT_right_wall_02->AddComponent<MeshRenderer>();
		mr_right_wall_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_right_wall_02->SetMaterial(Resources::Find<Material>(L"BT_Wall_right_03"));
		BT_right_wall_02->GetComponent<Transform>()->SetPosition(Vector3(-3.4f, -17.8f, 0.998f));
		BT_right_wall_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 28.f, 0.f));

		Ground* Bt_floor_01 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_floor_01);
		MeshRenderer* mr_floor_01 = Bt_floor_01->AddComponent<MeshRenderer>();
		mr_floor_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_01->SetMaterial(Resources::Find<Material>(L"BT_floor_01"));
		Bt_floor_01->GetComponent<Transform>()->SetPosition(Vector3(-16.4f, -6.8f, 0.998f));
		Bt_floor_01->GetComponent<Transform>()->SetScale(Vector3(13.f, 3.f, 0.f));



		Ground* BT_right_wall_03 = new Ground();
		
		AddGameObject(eLayerType::Ground, BT_right_wall_03);
		MeshRenderer* mr_right_wall_03 = BT_right_wall_03->AddComponent<MeshRenderer>();
		mr_right_wall_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_right_wall_03->SetMaterial(Resources::Find<Material>(L"BT_Wall_right_03"));
		BT_right_wall_03->GetComponent<Transform>()->SetPosition(Vector3(-32.4f, -10.8f, 0.998f));
		BT_right_wall_03->GetComponent<Transform>()->SetScale(Vector3(3.f, 50.f, 0.f));



		GameObject* BT_Temple_01 = new GameObject();
		AddGameObject(eLayerType::Ground, BT_Temple_01);
		MeshRenderer* mr_temple_01 = BT_Temple_01->AddComponent<MeshRenderer>();
		mr_temple_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_temple_01->SetMaterial(Resources::Find<Material>(L"BT_Temple_01"));
		BT_Temple_01->GetComponent<Transform>()->SetPosition(Vector3(-16.4f, -3.9f, 0.998f));
		BT_Temple_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 3.f, 0.f));


		//왼쪽 floor
		Ground* Bt_homes_floor_01 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_01);
		MeshRenderer* mr_homes_01 = Bt_homes_floor_01->AddComponent<MeshRenderer>();
		mr_homes_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_01->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -10.9f, 0.998f));
		Bt_homes_floor_01->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));


		GameObject* Bt_homes_floor_01_1 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_01_1);
		MeshRenderer* mr_homes_01_1 = Bt_homes_floor_01_1->AddComponent<MeshRenderer>();
		mr_homes_01_1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_01_1->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_01_1->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -11.7f, 0.997f));
		Bt_homes_floor_01_1->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));




		Ground* Bt_homes_floor_02 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_02);
		MeshRenderer* mr_homes_02 = Bt_homes_floor_02->AddComponent<MeshRenderer>();
		mr_homes_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_02->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_02->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -20.9f, 0.998f));
		Bt_homes_floor_02->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));

		GameObject* Bt_homes_floor_02_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_02_01);
		MeshRenderer* mr_homes_02_01 = Bt_homes_floor_02_01->AddComponent<MeshRenderer>();
		mr_homes_02_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_02_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_02_01->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -21.7f, 0.997f));
		Bt_homes_floor_02_01->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));



		Ground* Bt_homes_floor_03 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_03);
		MeshRenderer* mr_homes_03 = Bt_homes_floor_03->AddComponent<MeshRenderer>();
		mr_homes_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_03->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_03->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -30.9f, 0.998f));
		Bt_homes_floor_03->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));


		GameObject* Bt_homes_floor_03_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_03_01);
		MeshRenderer* mr_homes_03_01 = Bt_homes_floor_03_01->AddComponent<MeshRenderer>();
		mr_homes_03_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_03_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_03_01->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -31.7f, 0.997f));
		Bt_homes_floor_03_01->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));



		////////////////////오른쪽 floor/////////////////////////////////////////////

		Ground* Bt_homes_floor_04 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_04);
		MeshRenderer* mr_homes_04 = Bt_homes_floor_04->AddComponent<MeshRenderer>();
		mr_homes_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_04->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_04->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -10.9f, 0.998f));
		Bt_homes_floor_04->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));

		GameObject* Bt_homes_floor_04_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_04_01);
		MeshRenderer* mr_homes_04_01 = Bt_homes_floor_04_01->AddComponent<MeshRenderer>();
		mr_homes_04_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_04_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_04_01->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -11.7f, 0.997f));
		Bt_homes_floor_04_01->GetComponent<Transform>()->SetScale(Vector3(3.9f, 1.f, 0.f));




		Ground* Bt_homes_floor_05 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_05);
		MeshRenderer* mr_homes_05 = Bt_homes_floor_05->AddComponent<MeshRenderer>();
		mr_homes_05->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_05->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_05->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -15.9f, 0.998f));
		Bt_homes_floor_05->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));


		GameObject* Bt_homes_floor_05_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_05_01);
		MeshRenderer* mr_homes_05_01 = Bt_homes_floor_05_01->AddComponent<MeshRenderer>();
		mr_homes_05_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_05_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_05_01->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -16.7f, 0.997f));
		Bt_homes_floor_05_01->GetComponent<Transform>()->SetScale(Vector3(3.9f, 1.f, 0.f));


		Ground* Bt_homes_floor_06 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_06);
		MeshRenderer* mr_homes_06 = Bt_homes_floor_06->AddComponent<MeshRenderer>();
		mr_homes_06->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_06->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_06->GetComponent<Transform>()->SetPosition(Vector3(-7.2f , -22.9f, 0.998f));
		Bt_homes_floor_06->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));


		GameObject* Bt_homes_floor_06_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_06_01);
		MeshRenderer* mr_homes_06_01 = Bt_homes_floor_06_01->AddComponent<MeshRenderer>();
		mr_homes_06_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_06_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_06_01->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -23.7f, 0.998f));
		Bt_homes_floor_06_01->GetComponent<Transform>()->SetScale(Vector3(3.9f, 1.f, 0.f));



		Ground* Bt_homes_floor__07 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor__07);
		MeshRenderer* mr_homes__07 = Bt_homes_floor__07->AddComponent<MeshRenderer>();
		mr_homes__07->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes__07->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor__07->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -30.9f, 0.998f));
		Bt_homes_floor__07->GetComponent<Transform>()->SetScale(Vector3(4.f, 1.f, 0.f));


		GameObject* Bt_homes_floor__07_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor__07_01);
		MeshRenderer* mr_homes__07_01 = Bt_homes_floor__07_01->AddComponent<MeshRenderer>();
		mr_homes__07_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes__07_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor__07_01->GetComponent<Transform>()->SetPosition(Vector3(-7.2f, -31.7f, 0.997f));
		Bt_homes_floor__07_01->GetComponent<Transform>()->SetScale(Vector3(3.9f, 1.f, 0.f));


		/////////////////////////////////////////////////////////////////////


		/////////
		//CENTER right Floor/////////////////////////////////////////////


		Ground* Bt_homes_floor_07 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_07);
		MeshRenderer* mr_homes_07 = Bt_homes_floor_07->AddComponent<MeshRenderer>();
		mr_homes_07->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_07->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_07->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -13.9f, 0.998f));
		Bt_homes_floor_07->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));


		GameObject* Bt_homes_floor_07_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_07_01);
		MeshRenderer* mr_homes_07_01 = Bt_homes_floor_07_01->AddComponent<MeshRenderer>();
		mr_homes_07_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_07_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_07_01->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -14.4f, 0.997f));
		Bt_homes_floor_07_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));



		Ground* Bt_homes_floor_08 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_08);
		MeshRenderer* mr_homes_08 = Bt_homes_floor_08->AddComponent<MeshRenderer>();
		mr_homes_08->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_08->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_08->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -18.9f, 0.998f));
		Bt_homes_floor_08->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));


		GameObject* Bt_homes_floor_08_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_08_01);
		MeshRenderer* mr_homes_08_01 = Bt_homes_floor_08_01->AddComponent<MeshRenderer>();
		mr_homes_08_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_08_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_08_01->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -19.4f, 0.997f));
		Bt_homes_floor_08_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));




		Ground* Bt_homes_floor_09 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_09);
		MeshRenderer* mr_homes_09 = Bt_homes_floor_09->AddComponent<MeshRenderer>();
		mr_homes_09->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_09->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_09->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -25.9f, 0.998f));
		Bt_homes_floor_09->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));


		GameObject* Bt_homes_floor_09_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_09_01);
		MeshRenderer* mr_homes_09_01 = Bt_homes_floor_09_01->AddComponent<MeshRenderer>();
		mr_homes_09_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_09_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_09_01->GetComponent<Transform>()->SetPosition(Vector3(-13.2f, -26.4f, 0.997f));
		Bt_homes_floor_09_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));

		//////////////////////////////////////


		//////////////////center left floor/////////////////////////////////////////



		Ground* Bt_homes_floor_10 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_10);
		MeshRenderer* mr_homes_10 = Bt_homes_floor_10->AddComponent<MeshRenderer>();
		mr_homes_10->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_10->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_10->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -15.9f, 0.998f));
		Bt_homes_floor_10->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));



		GameObject* Bt_homes_floor_10_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_10_01);
		MeshRenderer* mr_homes_10_01 = Bt_homes_floor_10_01->AddComponent<MeshRenderer>();
		mr_homes_10_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_10_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_10_01->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -16.4f, 0.997f));
		Bt_homes_floor_10_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));



		Ground* Bt_homes_floor_11 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_11);
		MeshRenderer* mr_homes_11 = Bt_homes_floor_11->AddComponent<MeshRenderer>();
		mr_homes_11->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_11->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_11->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -22.9f, 0.998f));
		Bt_homes_floor_11->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));



		GameObject* Bt_homes_floor_11_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_11_01);
		MeshRenderer* mr_homes_11_01 = Bt_homes_floor_11_01->AddComponent<MeshRenderer>();
		mr_homes_11_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_11_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_11_01->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -23.4f, 0.997f));
		Bt_homes_floor_11_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));

		Ground* Bt_homes_floor_12 = new Ground();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_12);
		MeshRenderer* mr_homes_12 = Bt_homes_floor_12->AddComponent<MeshRenderer>();
		mr_homes_12->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_12->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_01"));
		Bt_homes_floor_12->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -28.9f, 0.998f));
		Bt_homes_floor_12->GetComponent<Transform>()->SetScale(Vector3(4.7f, 0.7f, 0.f));


		GameObject* Bt_homes_floor_12_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_homes_floor_12_01);
		MeshRenderer* mr_homes_12_01 = Bt_homes_floor_12_01->AddComponent<MeshRenderer>();
		mr_homes_12_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_homes_12_01->SetMaterial(Resources::Find<Material>(L"Bt_homes_floor_02"));
		Bt_homes_floor_12_01->GetComponent<Transform>()->SetPosition(Vector3(-19.2f, -29.4f, 0.997f));
		Bt_homes_floor_12_01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 0.9f, 0.f));



		/////////////////////////////////////////////////////////////////////////////////


		GameObject* Bt_rope_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_rope_01);
		MeshRenderer* mr_bt_rope_01 = Bt_rope_01->AddComponent<MeshRenderer>();
		mr_bt_rope_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_rope_01->SetMaterial(Resources::Find<Material>(L"BT_rope"));
		Bt_rope_01->GetComponent<Transform>()->SetPosition(Vector3(-26.4f, -15.9f, 1.f));
		Bt_rope_01->GetComponent<Transform>()->SetScale(Vector3(3.5f, 60.f, 0.f));

		GameObject* Bt_rope_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_rope_02);
		MeshRenderer* mr_bt_rope_02 = Bt_rope_02->AddComponent<MeshRenderer>();
		mr_bt_rope_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_rope_02->SetMaterial(Resources::Find<Material>(L"BT_rope"));
		Bt_rope_02->GetComponent<Transform>()->SetPosition(Vector3(-7.1f, -15.9f, 1.f));
		Bt_rope_02->GetComponent<Transform>()->SetScale(Vector3(3.5f, 60.f, 0.f));


		GameObject* Bt_rope_03 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_rope_03);
		MeshRenderer* mr_bt_rope_03 = Bt_rope_03->AddComponent<MeshRenderer>();
		mr_bt_rope_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_rope_03->SetMaterial(Resources::Find<Material>(L"BT_rope"));
		Bt_rope_03->GetComponent<Transform>()->SetPosition(Vector3(-13.1f, -24.9f, 1.f));
		Bt_rope_03->GetComponent<Transform>()->SetScale(Vector3(4.f, 35.f, 0.f));


		GameObject* Bt_rope_04 = new GameObject();
		AddGameObject(eLayerType::Ground, Bt_rope_04);
		MeshRenderer* mr_bt_rope_04 = Bt_rope_04->AddComponent<MeshRenderer>();
		mr_bt_rope_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_rope_04->SetMaterial(Resources::Find<Material>(L"BT_rope"));
		Bt_rope_04->GetComponent<Transform>()->SetPosition(Vector3(-19.15f, -23.9f, 1.f));
		Bt_rope_04->GetComponent<Transform>()->SetScale(Vector3(4.f, 35.f, 0.f));

		GameObject* BT_Hang = new GameObject();
		AddGameObject(eLayerType::Ground, BT_Hang);
		MeshRenderer* mr_bt_hang = BT_Hang->AddComponent<MeshRenderer>();
		mr_bt_hang->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_bt_hang->SetMaterial(Resources::Find<Material>(L"BT_Hang"));
		BT_Hang->GetComponent<Transform>()->SetPosition(Vector3(-18.45f, 7.f, 0.8f));
		BT_Hang->GetComponent<Transform>()->SetScale(Vector3(30.f, 10.f, 0.f));



		GameObject* Floor_layered02 = new GameObject();
		AddGameObject(eLayerType::Ground, Floor_layered02);
		MeshRenderer* mr_floor_layered02 = Floor_layered02->AddComponent<MeshRenderer>();
		mr_floor_layered02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_layered02->SetMaterial(Resources::Find<Material>(L"BT_floor_layered"));
		Floor_layered02->GetComponent<Transform>()->SetPosition(Vector3(-20.f, -36.f, 0.9f));
		Floor_layered02->GetComponent<Transform>()->SetScale(Vector3(30.f, 7.f, 0.f));





		GameObject* Low_floor_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Low_floor_01);
		MeshRenderer* mr_low_floor_01 = Low_floor_01->AddComponent<MeshRenderer>();
		mr_low_floor_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_low_floor_01->SetMaterial(Resources::Find<Material>(L"bt_low_floor_01"));
		Low_floor_01->GetComponent<Transform>()->SetPosition(Vector3(-37.f, -36.f, 0.5f));
		Low_floor_01->GetComponent<Transform>()->SetScale(Vector3(7.f, 7.f, 0.f));


		GameObject* Low_floor_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Low_floor_02);
		MeshRenderer* mr_low_floor_02 = Low_floor_02->AddComponent<MeshRenderer>();
		mr_low_floor_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_low_floor_02->SetMaterial(Resources::Find<Material>(L"bt_low_floor_01"));
		Low_floor_02->GetComponent<Transform>()->SetPosition(Vector3(-3.f, -38.f, 0.5f));
		Low_floor_02->GetComponent<Transform>()->SetScale(Vector3(7.f, 7.f, 0.f));



		//////////broke//////////////////////////////////////////


		GameObject* Broke_layered_01 = new GameObject();
		AddGameObject(eLayerType::Ground, Broke_layered_01);
		MeshRenderer* mr_broke_layered_01 = Broke_layered_01->AddComponent<MeshRenderer>();
		mr_broke_layered_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_broke_layered_01->SetMaterial(Resources::Find<Material>(L"Broke_layered_01"));
		Broke_layered_01->GetComponent<Transform>()->SetPosition(Vector3(-19.f, -14.7f, 0.99997f));
		Broke_layered_01->GetComponent<Transform>()->SetScale(Vector3(1.5f, 2.3f, 0.f));


		GameObject* Broke_layered_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Broke_layered_02);
		MeshRenderer* mr_broke_layered_02 = Broke_layered_02->AddComponent<MeshRenderer>();
		mr_broke_layered_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_broke_layered_02->SetMaterial(Resources::Find<Material>(L"Broke_layered_02"));
		Broke_layered_02->GetComponent<Transform>()->SetPosition(Vector3(-13.f, -24.7f, 0.99997f));
		Broke_layered_02->GetComponent<Transform>()->SetScale(Vector3(1.5f, 2.3f, 0.f));


		//collider wall

		Ground* floor = new Ground();
		AddGameObject(eLayerType::Ground, floor);
		floor->GetComponent<Transform>()->SetPosition(Vector3(-10.f, 6.7f, 0.99f));
		floor->GetComponent<Transform>()->SetScale(40.f, 1.f, 0.f);


		Ground* wall_break = new Ground();
		AddGameObject(eLayerType::Ground, wall_break);
		MeshRenderer* mr_wall_break = wall_break->AddComponent<MeshRenderer>();
		mr_wall_break->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_wall_break->SetMaterial(Resources::Find<Material>(L"Wall_Break"));
		wall_break->GetComponent<Transform>()->SetPosition(Vector3(-3.3f, -34.3f, 0.89997f));
		wall_break->GetComponent<Transform>()->SetScale(Vector3(3.f, 5.3f, 0.f));
		wall_break->GetComponent<Collider2D>()->SetSize(Vector2(1.f, 0.5f));
		wall_break->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 2.f));


		//Grimm처치시 open
		Ground* wall_break2 = new Ground();
		AddGameObject(eLayerType::Ground, wall_break2);
		MeshRenderer* mr_wall_break2 = wall_break2->AddComponent<MeshRenderer>();
		mr_wall_break2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_wall_break2->SetMaterial(Resources::Find<Material>(L"Wall_Break2"));
		wall_break2->GetComponent<Transform>()->SetPosition(Vector3(-3.3f, -34.3f, 0.89997f));
		wall_break2->GetComponent<Transform>()->SetScale(Vector3(3.f, 1.5f, 0.f));
		wall_break2->GetComponent<Collider2D>()->SetSize(Vector2(1.f, 1.f));
		wall_break2->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.f));

		m_AbyssDoor = wall_break2;

		SceneChangeTrigger* Sct = new SceneChangeTrigger();
		AddGameObject(eLayerType::Trigger, Sct);
		Sct->SetName(L"BattleTrigger");
		Sct->GetComponent<Transform>()->SetPosition(Vector3(-3.3f, -34.3f, 0.89997f));
		Sct->GetComponent<Transform>()->SetScale(Vector3(3.f, 3.f, 0.f));
		Sct->GetComponent<Collider2D>()->SetSize(Vector2(0.5f, 0.5f));
		Sct->Initialize();
		Sct->GetComponent<SceneChangeScript>()->SetSceneLight(this);

#pragma endregion



		BattleToStartTrigger* BToS_Trigger = new BattleToStartTrigger();

		BToS_Trigger->GetComponent<Transform>()->SetPosition(Vector3(0.f, -3.f, 1.f));
		SceneManager::AddGameObject(eLayerType::Trigger, BToS_Trigger);



		Box* mBox = new Box();
		AddGameObject(eLayerType::LayeredObj, mBox);
		mBox->GetComponent<Transform>()->SetPosition(Vector3(-16.4f, -4.7f, 1.01f));
		mBox->SetOpenCount(GetMonsterCnt());
		mBox->SetScene(this);
	
	
		UI_HUD* HUB = new UI_HUD();
		HUB->Initialize();
		std::vector<Health*> ob = HUB->GetHUDObj();
		
		//Baldur* mBaldur = new Baldur();
		//AddGameObject(eLayerType::Monster, mBaldur);
		//mBaldur->Initialize();
		//mBaldur->GetComponent<Transform>()->SetPosition(4.f, 0.f, 1.0001);
		//mBaldur->SetScene(this);
	
		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);
		
		pPlayer->Initialize();
		pPlayer->GetComponent<Transform>()->SetPosition(0.f, 5.f, 1.0001);
		pPlayer->GetComponent<PlayerScript>()->SetState(PlayerScript::EPlayerState::Jump);
		pPlayer->GetComponent<PlayerScript>()->SetPlayer(pPlayer);

		//카메라 애니메이션을 위한 박스세팅
		pPlayer->SetBattleBox(mBox);

		Light* PlayerLight = pPlayer->AddComponent<Light>();
		PlayerLight->SetType(eLightType::Point);
		PlayerLight->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.6f));
		PlayerLight->SetRadius(8.0f);



		pPlayer->AddComponent<AudioListener>();


		RegisterPlayer(pPlayer);

		pPlayer->GetComponent<PlayerScript>()->SetHUD(ob);
		pPlayer->GetComponent<PlayerScript>()->SetPlayerHUD(HUB);

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.4f, 0.4f, 0.4f, 0.5f));

		}

		Hunter* mHunter = new Hunter();
		AddGameObject(eLayerType::Monster, mHunter);
		mHunter->Initialize();
		mHunter->GetComponent<Transform>()->SetPositionXY(Vector2(-10.f, 0.f));
		mHunter->SetScene(this);
		PlusMonsterCnt();

		Hunter* mHunter02 = new Hunter();
		AddGameObject(eLayerType::Monster, mHunter02);
		mHunter02->Initialize();
		mHunter02->GetComponent<Transform>()->SetPositionXY(Vector2(-15.f, -20.f));

		mHunter02->SetScene(this);
		PlusMonsterCnt();

		Hunter* mHunter03 = new Hunter();
		AddGameObject(eLayerType::Monster, mHunter03);
		mHunter03->Initialize();
		mHunter03->GetComponent<Transform>()->SetPositionXY(Vector2(-17.f, -20.f));

		mHunter03->SetScene(this);
		PlusMonsterCnt();

		Hunter* mHunter04 = new Hunter();
		AddGameObject(eLayerType::Monster, mHunter04);
		mHunter04->Initialize();
		mHunter04->GetComponent<Transform>()->SetPositionXY(Vector2(-15.f, -25.f));

		mHunter04->SetScene(this);
		PlusMonsterCnt();

		
	

		m_Hunters.push_back(mHunter);
		m_Hunters.push_back(mHunter02);
		m_Hunters.push_back(mHunter03);
		m_Hunters.push_back(mHunter04);

		Camera* cameraComp = nullptr;
		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			//cameraComp->TurnLayerMask(eLayerType::UI, false);
			//cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			//cameraComp->TurnLayerMask(eLayerType::Ground, true);
			CameraScript* camerasr = camera->AddComponent<CameraScript>();
			camerasr->SetPlayer(pPlayer);
			camerasr->SetBackGround(Battle_BG01);
			//camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			
			camera->AddComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"BattleSound", L"..\\Resources\\Sound\\BattleSound.mp3"));

			m_SceneAS = camera->GetComponent<AudioSource>();

			SetCameraObj(camera);

			SetMainCamera(cameraComp);

			//scene 재입력 화면Shake
			pPlayer->SetCurScene(this);
		}
		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			cameraComp->TurnLayerMask(eLayerType::BackGround, FALSE);
			cameraComp->TurnLayerMask(eLayerType::Ground, FALSE);
			cameraComp->TurnLayerMask(eLayerType::LayeredObj, FALSE);
			cameraComp->TurnLayerMask(eLayerType::Player, FALSE);
			cameraComp->TurnLayerMask(eLayerType::Monster, FALSE);
			cameraComp->TurnLayerMask(eLayerType::PlayerAttack, false);


			//camera->AddComponent<CameraScript>();
		}

	}

	void BattleScene01::Update()
	{

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			SceneManager::LoadScene(L"BossScene");
		}


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

	void BattleScene01::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::LayeredObj, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Trigger, eLayerType::Player, true);
		renderer::mainCamera = GetMainCamera();

		std::wstring Pre_S = SceneManager::GetPreSceneName();

		SceneManager::SetCurScene(L"BattleScene");

		Scene::OnEnter();
		
		if (Pre_S == L"AbyssScene")
		{
			//mPlayer->GetComponent<Transform>()->SetPositionXY(Vector2(33.f, 3.f));
		}
		if (SceneManager::GetGrimmCoin())
		{
			SceneManager::DestoryObj(m_AbyssDoor);
			delete m_AbyssDoor;
		}
		
	}

	void BattleScene01::OnExit()
	{
		
		
		SceneManager::Destory();
		CollisionManager::Clear();

		Scene::OnExit();
		DestroyAll();
	
		
		SceneManager::SetPreScene(L"BattleScene");
	}

}