#include "AkGrimm_Projectile_03.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkTexture.h"
#include "AkTime.h"
#include "AkSceneManager.h"

namespace Ak
{
	Grimm_Projectile_03::Grimm_Projectile_03()
		: m_fMaxCdSize01Y(0.7f)
		, m_fMaxCdSize02Y(1.3f)
		, m_bDestory(false)
	{

		SetName(L"GrimmAttack03");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> Attack_03
			= Resources::Load<Texture>(L"Attack_03_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack3_01_obj.png");


		std::shared_ptr<Texture> Attack_03_02
			= Resources::Load<Texture>(L"Attack_03_02_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack3_02_obj.png");

		std::shared_ptr<Texture> Attack_03_03
			= Resources::Load<Texture>(L"Attack_03_03_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack3_03_obj.png");

		GetComponent<Transform>()->SetScale(2.3f, 2.5f, 0.f);
		m_cd = AddComponent<Collider2D>();

		//
		m_cd->SetSize(Vector2(0.2f, 0.f));
		m_cd->SetCenter(Vector2(-0.2f, -0.5f));
		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Attack_03", Attack_03, Vector2(0.0f, 0.0f), Vector2(200.f, 233.f), 4);

		mAnimator->Create(L"Attack_03_02", Attack_03_02, Vector2(0.0f, 0.0f), Vector2(300.f, 285.f), 8);

		mAnimator->Create(L"Attack_03_03", Attack_03_03, Vector2(0.0f, 0.0f), Vector2(300.f, 285.f), 8);
		//GetComponent<Transform>()->SetScale(3.f, 15.f, 0.f);
		//GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -3.f));
		//mAnimator->PlayAnimation(L"Attack_03_02", false);
		mAnimator->PlayAnimation(L"Attack_03_03", false);

		fPreSizeY = 1.3f;
	}

	Grimm_Projectile_03::~Grimm_Projectile_03()
	{
		fPreSizeY = 1.3f;
 	}

	void Grimm_Projectile_03::Initialize()
	{

	}

	void Grimm_Projectile_03::Update()
	{
		GameObject::Update();

		if (mAnimator->GetPlayAnimationName() == L"Attack_03")
		{
	
			float fSizeY = m_cd->GetSize().y;
			if (m_fMaxCdSize01Y >= fSizeY)
			{
				fSizeY += 0.002f;
				m_cd->SetSize(Vector2(m_cd->GetSize().x, fSizeY));
			}
		}

		if (mAnimator->GetPlayAnimationName() == L"Attack_03_02")
		{
			GetComponent<Transform>()->SetScale(3.f, 15.f, 0.f);
			GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -3.f));

			float fSizeY = m_cd->GetSize().y;
			if (m_fMaxCdSize02Y >= fSizeY)
			{
				fSizeY += 0.001f;
				m_cd->SetSize(Vector2(m_cd->GetSize().x, fSizeY));
			}

		}

		if (mAnimator->GetPlayAnimationName() == L"Attack_03_03")
		{
			GetComponent<Transform>()->SetScale(3.f, 15.f, 0.f);
			GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -3.f));

			float fSizeY = m_cd->GetSize().y;

			 
			if (fPreSizeY >= 0.f)
			{
				fPreSizeY -= 0.002f;
				m_cd->SetSize(Vector2(m_cd->GetSize().x, fPreSizeY));
				m_bDestory = true;
			}
		}

		if (m_bDestory)
		{
			static float DsTime = 0.f;
			DsTime += Time::DeltaTime();

			if (DsTime >= 1.5f)
			{
				SceneManager::DestoryObj(this);
				delete this;
				DsTime = 0.f;
			}
			
		}
	}

	void Grimm_Projectile_03::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Grimm_Projectile_03::Render()
	{
		GameObject::Render();
	}

}