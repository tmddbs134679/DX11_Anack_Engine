#include "AkHP_Ball.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkLight.h"
#include "AkRenderer.h"
#include "AkSceneManager.h"


namespace Ak
{
	HP_Ball::HP_Ball()
		: m_bUI(false)
		, m_iLifeSoul(0)
	{
		SetName(L"HP_Ball");

		std::shared_ptr<Texture> HP_Ball_00
			= Resources::Load<Texture>(L"HP_Ball_00_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_0.png");

		std::shared_ptr<Texture> HP_Ball_10
			= Resources::Load<Texture>(L"HP_Ball_10_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_10.png");

		std::shared_ptr<Texture> HP_Ball_20
			= Resources::Load<Texture>(L"HP_Ball_20_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_20.png");

		std::shared_ptr<Texture> HP_Ball_30
			= Resources::Load<Texture>(L"HP_Ball_30_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_30.png");

		std::shared_ptr<Texture> HP_Ball_40
			= Resources::Load<Texture>(L"HP_Ball_40_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_40.png");

		std::shared_ptr<Texture> HP_Ball_50
			= Resources::Load<Texture>(L"HP_Ball_50_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_50.png");

		std::shared_ptr<Texture> HP_Ball_60
			= Resources::Load<Texture>(L"HP_Ball_60_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_60.png");

		std::shared_ptr<Texture> HP_Ball_70
			= Resources::Load<Texture>(L"HP_Ball_70_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_70.png");

		std::shared_ptr<Texture> HP_Ball_80
			= Resources::Load<Texture>(L"HP_Ball_80_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_80.png");

		std::shared_ptr<Texture> HP_Ball_90
			= Resources::Load<Texture>(L"HP_Ball_90_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_90.png");

		std::shared_ptr<Texture> HP_Ball_100
			= Resources::Load<Texture>(L"HP_Ball_100_txt", L"..\\Resources\\Texture\\ball\\HP_Ball_100.png");



		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		GetComponent<Transform>()->SetPosition(Vector3(-5.832f, 2.81f, -2.99f));
		GetComponent<Transform>()->SetScale(Vector3(2.21f, 2.21f, 0.f));

		m_Animator = AddComponent<Animator>();


		m_Animator->Create(L"HP_Ball_00", HP_Ball_00, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_10", HP_Ball_10, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_20", HP_Ball_20, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_30", HP_Ball_30, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_40", HP_Ball_40, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_50", HP_Ball_50, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_60", HP_Ball_60, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_70", HP_Ball_70, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_80", HP_Ball_80, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_90", HP_Ball_90, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);
		m_Animator->Create(L"HP_Ball_100", HP_Ball_100, Vector2(0.0f, 0.0f), Vector2(147.f, 147.f), 1);

		m_Animator->PlayAnimation(L"HP_Ball_100", false);

		m_iLifeSoul = SceneManager::GetBall();
	}

	HP_Ball::~HP_Ball()
	{
		GameObject::~GameObject();
	}

	void HP_Ball::Initialize()
	{

	}

	void HP_Ball::Update()
	{

		switch (m_iLifeSoul)
		{
			case 0:
				m_Animator->PlayAnimation(L"HP_Ball_00", false);
				break;

			case 1:
				m_Animator->PlayAnimation(L"HP_Ball_10", false);
				break;

			case 2:
				m_Animator->PlayAnimation(L"HP_Ball_20", false);
				break;
			case 3:

				m_Animator->PlayAnimation(L"HP_Ball_30", false);
				break;
			case 4:

				m_Animator->PlayAnimation(L"HP_Ball_40", false);
				break;
			case 5:

				m_Animator->PlayAnimation(L"HP_Ball_50", false);
				break;

			case 6:
				m_Animator->PlayAnimation(L"HP_Ball_60", false);
				break;
				
			case 7:
				m_Animator->PlayAnimation(L"HP_Ball_70", false);
				break;

			case 8:
				m_Animator->PlayAnimation(L"HP_Ball_80", false);
				break;

			case 9:
				m_Animator->PlayAnimation(L"HP_Ball_90", false);
				break;

			case 10:
				m_Animator->PlayAnimation(L"HP_Ball_100", false);
				break;

			default:
			break;
		}


		GameObject::Update();
	}

	void HP_Ball::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void HP_Ball::Render()
	{
		

		renderer::AnimatorCB AnimatorCB;
		AnimatorCB.bUI = m_bUI;


		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&AnimatorCB);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

		GameObject::Render();

	}

}