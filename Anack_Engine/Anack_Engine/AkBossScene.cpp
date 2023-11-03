#include "AkBossScene.h"
#include "AkMeshRenderer.h"
#include "AkTransform.h"
#include "AkCamera.h"
#include "AkCameraScript.h"
#include "AkResources.h"
#include "../Anack_Engine/AkPlayerScript.h"
#include "AkRenderer.h"
#include "AkCollisionManager.h"
#include "AkGround.h"
#include "../Anack_Engine/AkBaldur.h"
#include "../Anack_Engine/AkHunter.h"
#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkBrumm.h"
#include "../Anack_Engine/AkGrimm.h"
#include "AkBossStartTigger.h"
#include "AkGrimm_Projectile_01.h"
#include "AkGrimm_Projectile_02.h"
#include "AkGrimm_Projectile_03.h"
#include "AkFlame.h"
#include "AkAudioClip.h"
#include "AkAudioListener.h"
#include "AkInput.h"
#include "AkSceneManager.h"
#include "../Anack_Engine/AkBossToStartTrigger.h"
#include "../Anack_Engine/AkSceneChangeScript.h"

namespace Ak
{
	BossScene::BossScene()
	{
		
	}

	BossScene::~BossScene()
	{

	}

	void BossScene::Initialize()
	{
		

#pragma region Map Setting

		GameObject* Boss_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG);
		Boss_BG->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg = Boss_BG->AddComponent<MeshRenderer>();
		mr_boss_bg->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg->SetMaterial(Resources::Find<Material>(L"Boss_BG"));
		Boss_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 1.f, 1.5f));
		Boss_BG->GetComponent<Transform>()->SetScale(Vector3(40.f, 20.f, 20.f));
		


		GameObject* Boss_BG01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG01);
		Boss_BG01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg01 = Boss_BG01->AddComponent<MeshRenderer>();
		mr_boss_bg01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg01->SetMaterial(Resources::Find<Material>(L"Grimm_BG_01"));
		Boss_BG01->GetComponent<Transform>()->SetPosition(Vector3(-39.8f, -2.f, 1.5f));
		Boss_BG01->GetComponent<Transform>()->SetScale(Vector3(40.f, 8.f, 20.f));

		GameObject* Boss_BG02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG02);
		Boss_BG02->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg02 = Boss_BG02->AddComponent<MeshRenderer>();
		mr_boss_bg02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg02->SetMaterial(Resources::Find<Material>(L"Boss_BG_02"));
		Boss_BG02->GetComponent<Transform>()->SetPosition(Vector3(0.f, -0.8f, 1.51f));
		Boss_BG02->GetComponent<Transform>()->SetScale(Vector3(33.f, 13.3f, 20.f));

		GameObject* Boss_curtain_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_curtain_01);
		Boss_curtain_01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_curtain_01 = Boss_curtain_01->AddComponent<MeshRenderer>();
		mr_boss_curtain_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_curtain_01->SetMaterial(Resources::Find<Material>(L"Boss_Curtain_01"));
		Boss_curtain_01->GetComponent<Transform>()->SetPosition(Vector3(-17.f, -1.f, 1.45f));
		Boss_curtain_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 6.f, 20.f));


		GameObject* Boss_rag_tent_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_rag_tent_01);
		Boss_rag_tent_01->SetName(L"Mune_BG");
		MeshRenderer* mr_rag_tent_01 = Boss_rag_tent_01->AddComponent<MeshRenderer>();
		mr_rag_tent_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_rag_tent_01->SetMaterial(Resources::Find<Material>(L"Boss_rag_tent"));
		Boss_rag_tent_01->GetComponent<Transform>()->SetPosition(Vector3(-30.f, -1.f, 0.44f));
		Boss_rag_tent_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 6.f, 20.f));

		GameObject* Boss_pillar_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_pillar_01);
		Boss_pillar_01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_pillar_01 = Boss_pillar_01->AddComponent<MeshRenderer>();
		mr_boss_pillar_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_pillar_01->SetMaterial(Resources::Find<Material>(L"Boss_Pillar"));
		Boss_pillar_01->GetComponent<Transform>()->SetPosition(Vector3(-35.f, -2.1f, 0.99f));
		Boss_pillar_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 9.f, 20.f));

		GameObject* Boss_Door_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_Door_01);
		Boss_Door_01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_door = Boss_Door_01->AddComponent<MeshRenderer>();
		mr_boss_door->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_door->SetMaterial(Resources::Find<Material>(L"Boss_Door"));
		Boss_Door_01->GetComponent<Transform>()->SetPosition(Vector3(-53.2f, -3.4f, 0.99f));
		Boss_Door_01->GetComponent<Transform>()->SetScale(Vector3(5.f, 4.f, 20.f));

		GameObject* Boss_rag_tent_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_rag_tent_02);
		Boss_rag_tent_01->SetName(L"Mune_BG");
		MeshRenderer* mr_rag_tent_02 = Boss_rag_tent_02->AddComponent<MeshRenderer>();
		mr_rag_tent_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_rag_tent_02->SetMaterial(Resources::Find<Material>(L"Boss_rag_tent"));
		Boss_rag_tent_02->GetComponent<Transform>()->SetPosition(Vector3(-45.f, -1.f, 0.44f));
		Boss_rag_tent_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 6.f, 20.f));



		Ground* Boss_In_Floor01 = new Ground();
		AddGameObject(eLayerType::Ground, Boss_In_Floor01);
		Boss_In_Floor01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_in_floor_01 = Boss_In_Floor01->AddComponent<MeshRenderer>();
		mr_boss_in_floor_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_in_floor_01->SetMaterial(Resources::Find<Material>(L"Grimm_In_Floor_01"));
		Boss_In_Floor01->GetComponent<Transform>()->SetPosition(Vector3(-40.f, -6.f, 1.499f));
		Boss_In_Floor01->GetComponent<Transform>()->SetScale(Vector3(43.f, 1.5f, 20.f));
	

		//øﬁ¬ 
		GameObject* Boss_In_Floor02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_In_Floor02);
		Boss_In_Floor02->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_in_floor_02 = Boss_In_Floor02->AddComponent<MeshRenderer>();
		mr_boss_in_floor_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_in_floor_02->SetMaterial(Resources::Find<Material>(L"Boss_Floor_02"));
		Boss_In_Floor02->GetComponent<Transform>()->SetPosition(Vector3(-40.f, -5.8f, 0.97f));
		Boss_In_Floor02->GetComponent<Transform>()->SetScale(Vector3(42.f, 1.5f, 20.f));

		GameObject* Boss_BG_Layered_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG_Layered_01);
		Boss_BG_Layered_01->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg_layered_01 = Boss_BG_Layered_01->AddComponent<MeshRenderer>();
		mr_boss_bg_layered_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg_layered_01->SetMaterial(Resources::Find<Material>(L"Grimm_BG_Layered_01"));
		Boss_BG_Layered_01->GetComponent<Transform>()->SetPosition(Vector3(-50.f, -5.5f, 0.496f));
		Boss_BG_Layered_01->GetComponent<Transform>()->SetScale(Vector3(3.f, 4.f, 20.f));

		GameObject* Boss_BG_Layered_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG_Layered_02);
		Boss_BG_Layered_02->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg_layered_02 = Boss_BG_Layered_02->AddComponent<MeshRenderer>();
		mr_boss_bg_layered_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg_layered_02->SetMaterial(Resources::Find<Material>(L"Grimm_BG_Layered_01"));
		Boss_BG_Layered_02->GetComponent<Transform>()->SetPosition(Vector3(-25.f, -5.5f, 0.496f));
		Boss_BG_Layered_02->GetComponent<Transform>()->SetScale(Vector3(3.f, 4.f, 20.f));

		GameObject* Boss_BG_Layered_03 = new GameObject();
		AddGameObject(eLayerType::BackGround, Boss_BG_Layered_03);
		Boss_BG_Layered_03->SetName(L"Mune_BG");
		MeshRenderer* mr_boss_bg_layered_03 = Boss_BG_Layered_03->AddComponent<MeshRenderer>();
		mr_boss_bg_layered_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_bg_layered_03->SetMaterial(Resources::Find<Material>(L"Grimm_BG_Layered_02"));
		Boss_BG_Layered_03->GetComponent<Transform>()->SetPosition(Vector3(-23.f, -4.7f, 1.496f));
		Boss_BG_Layered_03->GetComponent<Transform>()->SetScale(Vector3(6.f, 1.5f, 20.f));

		GameObject* Boss_round_BG = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_round_BG);
		MeshRenderer* mr_round_bg_01 = Boss_round_BG->AddComponent<MeshRenderer>();
		mr_round_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_round_bg_01->SetMaterial(Resources::Find<Material>(L"Grimm_round_BG"));
		Boss_round_BG->GetComponent<Transform>()->SetPosition(Vector3(-40.f, -1.f, 0.98f));
		Boss_round_BG->GetComponent<Transform>()->SetScale(Vector3(40.f, 9.f, 0.f));

		GameObject* Boss_round_BG_02 = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_round_BG_02);
		MeshRenderer* mr_round_bg_02 = Boss_round_BG_02->AddComponent<MeshRenderer>();
		mr_round_bg_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_round_bg_02->SetMaterial(Resources::Find<Material>(L"Grimm_round_BG_02"));
		Boss_round_BG_02->GetComponent<Transform>()->SetPosition(Vector3(-30.f, -6.3f, 0.88f));
		Boss_round_BG_02->GetComponent<Transform>()->SetScale(Vector3(15.f, 5.f, 0.f));

		GameObject* Boss_round_BG_03 = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_round_BG_03);
		MeshRenderer* mr_round_bg_03 = Boss_round_BG_03->AddComponent<MeshRenderer>();
		mr_round_bg_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_round_bg_03->SetMaterial(Resources::Find<Material>(L"Grimm_round_BG_02"));
		Boss_round_BG_03->GetComponent<Transform>()->SetPosition(Vector3(-45.f, -7.f, 0.88f));
		Boss_round_BG_03->GetComponent<Transform>()->SetScale(Vector3(15.f, 5.f, 0.f));


		GameObject* Black_BG01 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG01);
		MeshRenderer* mr_black_bg_01 = Black_BG01->AddComponent<MeshRenderer>();
		mr_black_bg_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_01->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG01->GetComponent<Transform>()->SetPosition(Vector3(0.f, -8.f, 0.9998f));
		Black_BG01->GetComponent<Transform>()->SetScale(Vector3(35.f, 5.f, 0.f));

		GameObject* Black_BG02 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG02);
		MeshRenderer* mr_black_bg_02 = Black_BG02->AddComponent<MeshRenderer>();
		mr_black_bg_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_02->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG02->GetComponent<Transform>()->SetPosition(Vector3(-40.f, 0.f, 1.9998f));
		Black_BG02->GetComponent<Transform>()->SetScale(Vector3(55.f, 40.f, 0.f));


		GameObject* Black_BG03 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG03);
		MeshRenderer* mr_black_bg_03 = Black_BG03->AddComponent<MeshRenderer>();
		mr_black_bg_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_03->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG03->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.9998f));
		Black_BG03->GetComponent<Transform>()->SetScale(Vector3(70.f, 40.f, 0.f));

		GameObject* Black_BG04 = new GameObject();
		AddGameObject(eLayerType::Ground, Black_BG04);
		MeshRenderer* mr_black_bg_04 = Black_BG04->AddComponent<MeshRenderer>();
		mr_black_bg_04->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_black_bg_04->SetMaterial(Resources::Find<Material>(L"BT_Black_BG"));
		Black_BG04->GetComponent<Transform>()->SetPosition(Vector3(-70.f, 0.f, 1.9998f));
		Black_BG04->GetComponent<Transform>()->SetScale(Vector3(30.f, 40.f, 0.f));


		//ø¿∏•¬ ∂•
		Ground* Boss_floor_01 = new Ground();
		AddGameObject(eLayerType::Ground, Boss_floor_01);
		MeshRenderer* mr_boss_floor_01 = Boss_floor_01->AddComponent<MeshRenderer>();
		mr_boss_floor_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_floor_01->SetMaterial(Resources::Find<Material>(L"Boss_Floor_01"));
		Boss_floor_01->GetComponent<Transform>()->SetPosition(Vector3(-1.f, -6.0f, 0.9997f));
		Boss_floor_01->GetComponent<Transform>()->SetScale(Vector3(35.f, 1.3f, 0.f));
		Boss_floor_01->AddComponent<Collider2D>();

		GameObject* Boss_floor_effect = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_floor_effect);
		MeshRenderer* mr_floor_effect = Boss_floor_effect->AddComponent<MeshRenderer>();
		mr_floor_effect->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_effect->SetMaterial(Resources::Find<Material>(L"Boss_floor_effect"));
		Boss_floor_effect->GetComponent<Transform>()->SetPosition(Vector3(5.f, -5.7f, 0.9997f));
		Boss_floor_effect->GetComponent<Transform>()->SetScale(Vector3(6.f, 1.f, 0.f));

		GameObject* Boss_floor_effect02 = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_floor_effect02);
		MeshRenderer* mr_floor_effect02 = Boss_floor_effect02->AddComponent<MeshRenderer>();
		mr_floor_effect02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_floor_effect02->SetMaterial(Resources::Find<Material>(L"Boss_floor_effect_02"));
		Boss_floor_effect02->GetComponent<Transform>()->SetPosition(Vector3(6.f, 4.5f, 0.9997f));
		Boss_floor_effect02->GetComponent<Transform>()->SetScale(Vector3(8.f, 28.f, 0.f));


		GameObject* Boss_Top_C = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_Top_C);
		MeshRenderer* mr_boss_top_c = Boss_Top_C->AddComponent<MeshRenderer>();
		mr_boss_top_c->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_top_c->SetMaterial(Resources::Find<Material>(L"Boss_Top_c_01"));
		Boss_Top_C->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.8f, 0.9997f));
		Boss_Top_C->GetComponent<Transform>()->SetScale(Vector3(33.f, 4.f, 0.f));


		GameObject* Boss_Top_L = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_Top_L);
		MeshRenderer* mr_boss_top_l = Boss_Top_L->AddComponent<MeshRenderer>();
		mr_boss_top_l->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_top_l->SetMaterial(Resources::Find<Material>(L"Boss_Top_l_01"));
		Boss_Top_L->GetComponent<Transform>()->SetPosition(Vector3(-14.f, 4.f, 0.9996f));
		Boss_Top_L->GetComponent<Transform>()->SetScale(Vector3(6.f, 7.f, 0.f));

		GameObject* Boss_Top_R = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_Top_R);
		MeshRenderer* mr_boss_top_r = Boss_Top_R->AddComponent<MeshRenderer>();
		mr_boss_top_r->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_top_r->SetMaterial(Resources::Find<Material>(L"Boss_Top_Right_01"));
		Boss_Top_R->GetComponent<Transform>()->SetPosition(Vector3(14.f, 4.f, 0.9996f));
		Boss_Top_R->GetComponent<Transform>()->SetScale(Vector3(6.f, 7.f, 0.f));


		GameObject* Boss_wall_r = new GameObject();
		AddGameObject(eLayerType::Ground, Boss_wall_r);
		MeshRenderer* mr_boss_wall_r = Boss_wall_r->AddComponent<MeshRenderer>();
		mr_boss_wall_r->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_boss_wall_r->SetMaterial(Resources::Find<Material>(L"Boss_wall_R_01"));
		Boss_wall_r->GetComponent<Transform>()->SetPosition(Vector3(17.3f, -2.4f, 0.9998f));
		Boss_wall_r->GetComponent<Transform>()->SetScale(Vector3(2.5f, 6.f, 0.f));


		GameObject* ten_chain_01 = new GameObject();
		AddGameObject(eLayerType::BackGround, ten_chain_01);
		ten_chain_01->SetName(L"Mune_BG");
		MeshRenderer* mr_tent_chain_01 = ten_chain_01->AddComponent<MeshRenderer>();
		mr_tent_chain_01->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_tent_chain_01->SetMaterial(Resources::Find<Material>(L"Tent_Chain_01"));
		ten_chain_01->GetComponent<Transform>()->SetPosition(Vector3(-10.7f, 4.2f, 0.44f));
		ten_chain_01->GetComponent<Transform>()->SetScale(Vector3(2.f, 5.f, 20.f));

		GameObject* ten_chain_02 = new GameObject();
		AddGameObject(eLayerType::BackGround, ten_chain_02);
		ten_chain_02->SetName(L"Mune_BG");
		MeshRenderer* mr_tent_chain_02 = ten_chain_02->AddComponent<MeshRenderer>();
		mr_tent_chain_02->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_tent_chain_02->SetMaterial(Resources::Find<Material>(L"Tent_Chain_01"));
		ten_chain_02->GetComponent<Transform>()->SetPosition(Vector3(12.4f, 4.2f, 2.f));
		ten_chain_02->GetComponent<Transform>()->SetScale(Vector3(2.4f, 5.5f, 20.f));

		GameObject* ten_chain_03 = new GameObject();
		AddGameObject(eLayerType::BackGround, ten_chain_03);
		ten_chain_03->SetName(L"Mune_BG");
		MeshRenderer* mr_tent_chain_03 = ten_chain_03->AddComponent<MeshRenderer>();
		mr_tent_chain_03->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_tent_chain_03->SetMaterial(Resources::Find<Material>(L"Tent_Chain_01"));
		ten_chain_03->GetComponent<Transform>()->SetPosition(Vector3(3.8f, 3.2f, 0.44f));
		ten_chain_03->GetComponent<Transform>()->SetScale(Vector3(1.3f, 2.8f, 20.f));


#pragma endregion


		BossToStartTrigger* BTS_Trigger = new BossToStartTrigger();
		BTS_Trigger->GetComponent<Transform>()->SetPosition(Vector3(-57.f, -4.f, 1.f));
		AddGameObject(eLayerType::Trigger, BTS_Trigger);


		Brumm* bBrumm = new Brumm();
		AddGameObject(eLayerType::LayeredObj, bBrumm);
		bBrumm->AddComponent<AudioSource>();
		bBrumm->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Accordion", L"..\\Resources\\Sound\\Accordion.mp3"));

		//bBrumm->GetComponent<AudioSource>()->GetClip()->SetSoundDistance(Vector2(1.f,5.f));
		bBrumm->GetComponent<AudioSource>()->Play();

		m_Brumm = bBrumm;

		Flame* fFlame = new Flame();
		AddGameObject(eLayerType::LayeredObj, fFlame);
		fFlame->GetComponent<Transform>()->SetPosition(Vector3(-10.6, 3.f, 0.45f));


		Flame* fFlame2 = new Flame();
		AddGameObject(eLayerType::LayeredObj, fFlame2);
		fFlame2->GetComponent<Transform>()->SetPosition(Vector3(12.4f, 3.f, 2.f));
	


		Flame* fFlame3 = new Flame();
		AddGameObject(eLayerType::LayeredObj, fFlame3);
		fFlame3->GetComponent<Transform>()->SetPosition(Vector3(3.8f, 2.5f, 0.44f));
		fFlame3->GetComponent<Transform>()->SetScale(Vector3(2.5f, 2.f, 0.f));


	/*	Hunter* mHunter = new Hunter();
		AddGameObject(eLayerType::Monster, mHunter);
		mHunter->GetComponent<Transform>()->SetPositionXY(Vector2(3.f, 0.f));
		mHunter->Initialize();
		mHunter->SetScene(this);*/



		BossStartTigger* BossTrigger = new BossStartTigger();
		AddGameObject(eLayerType::Trigger, BossTrigger);
		BossTrigger->GetComponent<Transform>()->SetPosition(Vector3(-3.f, -1.f, 1.f));
		BossTrigger->SetBrumm(bBrumm);
		


		Grimm* mGrimm = new Grimm();
		AddGameObject(eLayerType::Monster, mGrimm);
		mGrimm->GetComponent<Transform>()->SetPositionXY(Vector2(4.5f, -2.f));
		mGrimm->Initialize();
		mGrimm->SetScene(this);
		mGrimm->SetBossTrigger(BossTrigger);
		mGrimm->SetBossBG(Boss_BG02);
		mGrimm->SetLightObj(Boss_floor_effect02);
		mGrimm->SetLightObj(Boss_floor_effect);


		UI_HUD* HUB = new UI_HUD();
		HUB->Initialize();
		std::vector<Health*> ob = HUB->GetHUDObj();

		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);

		pPlayer->Initialize();
		pPlayer->GetComponent<PlayerScript>()->SetPlayer(pPlayer);
		pPlayer->GetComponent<Transform>()->SetPosition(-55.f, 10.f, 1.000f);

		//m_SceneAS = 
		//pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Accordion", L"..\\Resources\\Sound\\Accordion.mp3"));
		pPlayer->AddComponent<AudioListener>();
		pPlayer->SetCurScene(this);
		pPlayer->AddComponent<AudioSource>();

		RegisterPlayer(pPlayer);


		pPlayer->GetComponent<PlayerScript>()->SetHUD(ob);
		pPlayer->GetComponent<PlayerScript>()->SetPlayerHUD(HUB);


		GameObject* Scenelight = new GameObject();
		Scenelight->SetName(L"SceneLight");
		AddGameObject(eLayerType::Light, Scenelight);
		Light* ScenelightComp = Scenelight->AddComponent<Light>();
		ScenelightComp->SetType(eLightType::Directional);
		ScenelightComp->SetColor(Vector4(0.4f, 0.4f, 0.4f, 0.5f));
		//ScenelightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		SetSceneLightObj(Scenelight);



		GameObject* camera = new GameObject();
		camera->SetName(L"PlayerCamera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* cameraSr = camera->AddComponent<CameraScript>();
		cameraSr->SetPlayer(pPlayer);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
		SetMainCamera(cameraComp);

		//Camera AudioSourceø° SceneClip ¿˙¿Â.
		m_SceneAC = Resources::Load<AudioClip>(L"Grimm", L"..\\Resources\\Sound\\Grimm Troupe.mp3");
		camera->AddComponent<AudioSource>();
		camera->GetComponent<AudioSource>()->SetClip(m_SceneAC);

		SetCameraObj(camera);

		mGrimm->SetSceneCamera(camera);

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
			pCameraComp->TurnLayerMask(eLayerType::Monster, false);
			pCameraComp->TurnLayerMask(eLayerType::MonsterAttack, false);
			//pCamera->AddComponent<CameraScript>();
		}


		BTS_Trigger->GetComponent<SceneChangeScript>()->SetSceneLight(this);
	}

	void BossScene::Update()
	{
		if(Input::GetKeyDown(eKeyCode::A))
		{
			SceneManager::LoadScene(L"AbyssScene");
		}
		
		Scene::Update();
	}

	void BossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BossScene::Render()
	{
		Scene::Render();
	}

	void BossScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerAttack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trigger, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		renderer::mainCamera = GetMainCamera();

		SceneManager::SetCurScene(L"BossScene");

		Scene::OnEnter();

	
	}

	void BossScene::OnExit()
	{
		m_Brumm->GetComponent<AudioSource>()->Stop();

		SceneManager::Destory();
		CollisionManager::Clear();


		Scene::OnExit();
		DestroyAll();

		SceneManager::SetPreScene(L"BossScene");
	}
}