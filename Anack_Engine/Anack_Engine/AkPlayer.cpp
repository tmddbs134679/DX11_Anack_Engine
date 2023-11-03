#include "AkPlayer.h"
#include "AkResources.h"
#include "AkRigidBody.h"
#include "AkPlayerWeapon.h"
#include "AkSceneManager.h"
#include "AkTime.h"
#include "AkParticleSystem.h"

namespace Ak
{
	Transform* Player::mTr = nullptr;
	MeshRenderer* Player::mMr = nullptr;
	Collider2D* Player::mCollider = nullptr;
	Animator* Player::mAnimatior = nullptr;
	Light* Player::mLight = nullptr;
	PlayerScript* Player::mPlayerSr = nullptr;

	Player::Player()
		: m_pPlayerWeapon(nullptr)
		, m_pPlayerScript(nullptr)
		, c_bDamage(false)
		, m_bDamage(false)
		, m_iBlinkCNT(0)
		, m_fBlinkTime(0.f)
		
	{
		SetName(L"Player");
		
	}

	Player::~Player()
	{
		if (m_pPlayerWeapon)
		{
			delete m_pPlayerWeapon;
			m_pPlayerWeapon = nullptr;
		}
	}
	
	void Player::Initialize()
	{
		mTr = GetComponent<Transform>();
		mMr = AddComponent<MeshRenderer>();
		mCollider = AddComponent<Collider2D>();
		mAnimatior = AddComponent<Animator>();
		mPlayerSr = AddComponent<PlayerScript>();
		mPlayerSr->Initialize();
		
		m_AudioSource = AddComponent<AudioSource>();


		mAnimatior->Initialize();


		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"PlayerMaterial"));
		mMr->Initialize();



		mTr->SetScale(Vector3(2.8f, 2.5f, 0.f));
		mTr->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));

		mCollider->SetSize(Vector2(0.25f, 0.6f));
		mCollider->SetCenter(Vector2(0.f, 0.0f));
		AddComponent<RigidBody>();

		mLight = AddComponent<Light>();
		mLight->SetName(L"PlayerLight");

		mLight->SetType(eLightType::Point);
		mLight->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.6f));
		mLight->SetRadius(8.0f);

		

		std::shared_ptr<AudioClip> ac1 = Resources::Load<AudioClip>(L"Knight_footstep", L"..\\Resources\\Sound\\Knight_walk_footsteps.mp3");
		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Knight_dash", L"..\\Resources\\Sound\\Knight_dash.mp3");

		m_AudioClips.push_back(ac1);
		m_AudioClips.push_back(ac2);

		GameObject* Shadow = new GameObject();
		SceneManager::AddGameObject(eLayerType::Player, Shadow);
		MeshRenderer* mr = Shadow->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Shadow_Ring"));
		Shadow->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.5f));
		Shadow->GetComponent<Transform>()->SetScale(Vector3(30.f, 20.5f, 10.f));
		m_PlayerShadow =Shadow;
		

		mPlayerSr->SetPlayer(this);
	
	}

	void Player::Update()
	{

		Vector3 pos = GetComponent<Transform>()->GetPosition();

		if (m_bPlayerShadow)
		{
			m_PlayerShadow->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y + 3.f, 0.7f));
		}
		else
		{
			m_PlayerShadow->GetComponent<Transform>()->SetPosition(Vector3(pos.x - 50, pos.y - 50, -10.f));
		}

		GameObject::Update();

	}

	void Player::LateUpdate()
	{
	
		GameObject::LateUpdate();
	}

	void Player::Render()
	{
		if (m_bDamage)
		{
			m_fBlinkTime += Time::DeltaTime();

			int Cnt = 5;
			float BlinkDuration = 0.1f;

			if (m_iBlinkCNT < Cnt)
			{
				if (m_fBlinkTime <= BlinkDuration)
				{
					// ±ôºýÀÓ È¿°ú Àû¿ë
					if (m_fBlinkTime < BlinkDuration / 2.0f)
					{
						// È¦¼ö ¹øÂ° ±ôºýÀÓÀº ¼û±è
						c_bDamage = false;
					}
					else
					{
						// Â¦¼ö ¹øÂ° ±ôºýÀÓÀº Ç¥½Ã
						c_bDamage = true;
					}

					PlayerCB.bTest2 = c_bDamage;
					ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
					pConstantBuffer->SetData(&PlayerCB);
					pConstantBuffer->Bind(eShaderStage::PS);
				}
				else
				{
					// ±ôºýÀÓÀÌ ³¡³­ ÈÄ »óÅÂ ÃÊ±âÈ­
					c_bDamage = false;

					PlayerCB.bTest2 = c_bDamage;
					ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
					pConstantBuffer->SetData(&PlayerCB);
					pConstantBuffer->Bind(eShaderStage::PS);
					m_fBlinkTime = 0.f;
					m_iBlinkCNT++;
				}
			}
			else
			{
				// µ¥¹ÌÁö È¿°ú ¿ÏÀüÈ÷ Á¾·á
				m_bDamage = false;
				m_fBlinkTime = 0.f;
				m_iBlinkCNT = 0;
			}
		}
		
		GameObject::Render();
	}

}

