#include "AkBox.h"
#include "AkResources.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"
#include "AkCoin.h"
#include "AkCameraScript.h"


namespace Ak
{
	Box::Box()
		: m_iOpenCnt(0)
		, m_bBoxOpen(false)
		, m_bCreateCoin(false)
		, m_AC(nullptr)
	{
		SetName(L"Box");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> box_close
			= Resources::Load<Texture>(L"box_close_txt", L"..\\Resources\\Texture\\BattleScene\\Box\\Box.png");

		std::shared_ptr<Texture> box_open
			= Resources::Load<Texture>(L"box_open_txt", L"..\\Resources\\Texture\\BattleScene\\Box\\Box_Open.png");

		std::shared_ptr<Texture> box_empty
			= Resources::Load<Texture>(L"box_empty_txt", L"..\\Resources\\Texture\\BattleScene\\Box\\box_empty.png");


		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		 mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"box_close", box_close, Vector2(0.0f, 0.0f), Vector2(230.f, 200.f), 1);
		mAnimator->Create(L"box_open", box_open, Vector2(0.0f, 0.0f), Vector2(230.f, 230.f), 3);
		mAnimator->Create(L"box_empty", box_empty, Vector2(0.0f, 0.0f), Vector2(230.f, 200.f), 1);

		mAnimator->PlayAnimation(L"box_close", false);

		std::shared_ptr<AudioClip> ac = Resources::Load<AudioClip>(L"Chest_Open", L"..\\Resources\\Sound\\chest_open.mp3");

		m_AC = ac;
	}

	Box::~Box()
	{

	}

	void Box::Initialize()
	{

	}

	void Box::Update()
	{
		GameObject::Update();

		if (m_pCurScene != nullptr)
		{
			if (m_pCurScene->GetMonsterCnt() == 0)
			{
				if (!m_bBoxOpen)
				{
					mAnimator->PlayAnimation(L"box_empty", false);
					m_pCurScene->GetCameraObj()->GetComponent<CameraScript>()->PlayBattleAnim();
					m_AC->Play();
					m_bBoxOpen = true;
				}
			}
		}

		if (mAnimator->GetPlayAnimationName() == L"box_empty")
		{
			if (!m_bCreateCoin)
			{

				Coin* mCoin = new Coin();
				mCoin->SetName(L"BoxCoin");
				m_pCurScene->AddGameObject(eLayerType::LayeredObj, mCoin);
				mCoin->GetComponent<Transform>()->SetPosition(Vector3(-16.4f, -4.f, 0.99f));

				m_bCreateCoin = true;
			}
		}
	
	}

	void Box::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Box::Render()
	{
		GameObject::Render();
	}

}