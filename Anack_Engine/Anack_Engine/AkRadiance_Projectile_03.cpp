#include "AkRadiance_Projectile_03.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkSceneManager.h"
#include "AkTime.h"

namespace Ak
{
	Radiance_Projectile_03::Radiance_Projectile_03()
		: m_bAttack2(false)
		, m_bReplay(false)
		, m_bdis(false)
	{
		//¹Ù´Ú ÀÛÀº Ã¢

		MeshRenderer* mr_radiance_gd = AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Attack_03"));

		Collider2D* cd = AddComponent<Collider2D>();
	
		


		//GetComponent<Transform>()->SetScale(0.7f, 1.6f, 0.f);
		GetComponent<Transform>()->SetScale(0.f, 0.f, 0.f);




		m_particle = new GameObject();
		
		std::shared_ptr<Texture> Attack_particle
			= Resources::Load<Texture>(L"Attack_particle", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiacne_attack3_effect.png");

		std::shared_ptr<Texture> Attack_particle2
			= Resources::Load<Texture>(L"Attack_particle2", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiacne_attack3_effect_2.png");

		std::shared_ptr<Texture> Attack_particle3
			= Resources::Load<Texture>(L"Attack_particle3", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiacne_attack3_effect_3.png");



		MeshRenderer* mr = m_particle->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		mAnimator = m_particle->AddComponent<Animator>();
		mAnimator->Create(L"Attack_particle", Attack_particle, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f), 2);
		mAnimator->Create(L"Attack_particle2", Attack_particle2, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f), 1);
		mAnimator->Create(L"Attack_particle3", Attack_particle3, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f), 1);

		mAnimator->PlayAnimation(L"Attack_particle", true);
		m_particle->GetComponent<Transform>()->SetScale(Vector3(2.f, 3.f, 1.f));
		m_particle->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		SceneManager::AddGameObject(eLayerType::LayeredObj, m_particle);

	}

	Radiance_Projectile_03::~Radiance_Projectile_03()
	{

		mAnimator->PlayAnimation(L"Attack_particle3", false);
		//GameObject::~GameObject();
	}

	void Radiance_Projectile_03::Initialize()
	{

	}

	void Radiance_Projectile_03::Update()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();

		m_particle->GetComponent<Transform>()->SetPositionXY(Vector2(pos.x + 0.01f, pos.y - 0.4f));


		if (m_bAttack)
		{

			m_fTime += Time::DeltaTime();

			if (m_fTime >= 3.f)
			{
				GetComponent<Transform>()->SetScale(Vector3(0.7f, 1.6f, 0.f));
				mAnimator->PlayAnimation(L"Attack_particle2", false);
				m_bAttack = false;
				m_bAttack2 = true;
				GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.f));
			}

		
		}
	
		if (m_bAttack2)
		{
			m_fTime += Time::DeltaTime();

			if (m_fTime >= 8.f)
			{
				m_bdis = true;
				GetComponent<Transform>()->SetScale(Vector3(0.0f, 0.0f, 0.f));
				mAnimator->PlayAnimation(L"Attack_particle3", false);
				GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -10.f));
			}

			if (m_fTime >= 12.f)
			{
				
				mAnimator->PlayAnimation(L"Attack_particle", true);
				m_bReplay = true;
				m_fTime = 0.f;
				m_bAttack2 = false;
				GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -10.f));
			}
		}
		
	

		GameObject::Update();
	}

	void Radiance_Projectile_03::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Projectile_03::Render()
	{
		GameObject::Render();
	}

}