
#include "AkPlayScene.h"
#include "AkTransform.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkMesh.h"
#include "AkCameraScript.h"
#include "AkCamera.h"
#include "AkInput.h"
#include "AkSceneManager.h"
#include "AkGridScript.h"
#include "AkBaldur.h"
#include "AkParticleSystem.h"
#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkBrumm.h"
#include "AkFlame.h"
#include "AkBox.h"
#include "AkCoin.h"
#include "AkPlayerWeapon.h"
#include "AkGrimm_Projectile_02.h"
#include "AkEndingBG.h"
#include "AkAudioListener.h"
#include "AkTime.h"


namespace Ak
{
	PlayScene::PlayScene()
		: m_bfull(true)
		, m_zPos(0.f)
	{
		

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		
		
		EndingBG* End_BG = new EndingBG();
		AddGameObject(eLayerType::BackGround, End_BG);

		GameObject* Menu_BG = new GameObject();
		AddGameObject(eLayerType::BackGround, Menu_BG);
		Menu_BG->SetName(L"Mune_BG");
		MeshRenderer* mrbackGround = Menu_BG->AddComponent<MeshRenderer>();
		mrbackGround->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrbackGround->SetMaterial(Resources::Find<Material>(L"Menutexture"));
		Menu_BG->GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 1.5002f));
		Menu_BG->GetComponent<Transform>()->SetScale(Vector3(200.f, 200.f, 20.f));
		
		GameObject* light = new GameObject();
		light->SetName(L"Smile");
		AddGameObject(eLayerType::Light, light);
		Light* lightComp = light->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

		


		m_SceneAC = Resources::Load<AudioClip>(L"ending", L"..\\Resources\\Sound\\Enter_Hallownest.mp3");
		m_SceneAC->Play();

		m_camera = new GameObject();
		AddGameObject(eLayerType::Player, m_camera);
		m_camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		Camera* cameraComp = m_camera->AddComponent<Camera>();
		m_camera->AddComponent<CameraScript>();
		m_camera->AddComponent<AudioListener>();
		
		SetCameraObj(m_camera);

	}

	void PlayScene::Update()
	{
		m_fEndingTime += Time::DeltaTime();

		if (m_bfull)
		{
			if (m_fEndingTime >= 6.f)
			{
				m_zPos -= 0.0005f;
				m_camera->GetComponent<Transform>()->SetPosition(0.f, 0.f, m_zPos);

				if (m_zPos <= -10.f)
				{
					m_bfull = false;
				}
			}
		}
		

		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		
		Scene::OnEnter();
	}

	void PlayScene::OnExit()
	{
	}


}


