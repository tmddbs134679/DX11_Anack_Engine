#include "AkRadiance_Projectile_04.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkSceneManager.h"

namespace Ak
{
	Radiance_Projectile_04::Radiance_Projectile_04()
		: m_bCollider(true)

	{

		std::shared_ptr<Texture> attack04_001
			= Resources::Load<Texture>(L"attack04_001_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_001.png");

		std::shared_ptr<Texture> attack04_ready
			= Resources::Load<Texture>(L"attack04_ready_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_00.png");

		std::shared_ptr<Texture> attack04_set
			= Resources::Load<Texture>(L"attack04_set_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_01.png");


		std::shared_ptr<Texture> attack04_beam
			= Resources::Load<Texture>(L"attack04_beam_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_02.png");


		std::shared_ptr<Texture> attack04_dis
			= Resources::Load<Texture>(L"attack04_dis_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_03.png");


		std::shared_ptr<Texture> attack04_emp
			= Resources::Load<Texture>(L"attack04_emp_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack04_empty.png");


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"attack04_001", attack04_001, Vector2(0.0f, 0.0f), Vector2(30.f, 180.f), 2);
		mAnimator->Create(L"attack04_ready", attack04_ready, Vector2(0.0f, 0.0f), Vector2(30.f, 180.f), 1);
		mAnimator->Create(L"attack04_set", attack04_set, Vector2(0.0f, 0.0f), Vector2(50.f, 180.f), 2);
		mAnimator->Create(L"attack04_beam", attack04_beam, Vector2(0.0f, 0.0f), Vector2(60.f, 180.f), 2);
		mAnimator->Create(L"attack04_dis", attack04_dis, Vector2(0.0f, 0.0f), Vector2(60.f, 180.f), 5);
		mAnimator->Create(L"attack04_emp", attack04_emp, Vector2(0.0f, 0.0f), Vector2(30.f, 180.f), 1);


		mAnimator->PlayAnimation(L"attack04_beam", true);

		GetComponent<Transform>()->SetScale(Vector3(4.f, 50.f, 1.f));

		std::shared_ptr<AudioClip> ac1 = Resources::Load<AudioClip>(L"Radiance_Attack04_pre", L"..\\Resources\\Sound\\Radiance\\radiance_laser_prepare.mp3");
		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Radiance_Attack04_lazer", L"..\\Resources\\Sound\\Radiance\\radiance_laser_burst.mp3");

		m_AudioClips.push_back(ac1);
		m_AudioClips.push_back(ac2);

		mcd = AddComponent<Collider2D>();
		mcd->SetSize(Vector2(0.f, 0.f));

	}

	Radiance_Projectile_04::~Radiance_Projectile_04()
	{
		
	}

	void Radiance_Projectile_04::Initialize()
	{

	}
	void Radiance_Projectile_04::Update()
	{

		

		if (m_bCollider)
		{
			if (mAnimator->GetPlayAnimationName() == L"attack04_beam")
			{
			
				mcd->SetSize(Vector2(0.3f, 1.f));
				m_bCollider = false;
				

			}
		}



		if (!(mAnimator->GetPlayAnimationName() == L"attack04_beam"))
		{
			if (mcd != nullptr)
			{
			
				mcd->SetSize(Vector2(0.f, 0.f));
				m_bCollider = true;
			}

		}

	

		GameObject::Update();
	}

	void Radiance_Projectile_04::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Projectile_04::Render()
	{
		GameObject::Render();
	}
}