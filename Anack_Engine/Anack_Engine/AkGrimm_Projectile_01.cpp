#include "AkGrimm_Projectile_01.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkTexture.h"
#include "AkTime.h"
#include "AkSceneManager.h"

namespace Ak
{
	Grimm_Projectile_01::Grimm_Projectile_01()
		: m_iDir(0)
	{
		SetName(L"GrimmAttack01");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> Attack_01
			= Resources::Load<Texture>(L"Attack_01_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack01_obj.png");

		std::shared_ptr<Texture> Attack_01_r
			= Resources::Load<Texture>(L"Attack_01_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack01_obj_r.png");

		GetComponent<Transform>()->SetScale(3.f, 2.f, 0.f);
		AddComponent<Collider2D>();

		GetComponent<Collider2D>()->SetSize(Vector2(0.7f, 0.3f));


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Attack_01", Attack_01, Vector2(0.0f, 0.0f), Vector2(300.f, 186.f), 3);
		mAnimator->Create(L"Attack_01_r", Attack_01_r, Vector2(0.0f, 0.0f), Vector2(300.f, 186.f), 3);
		//mAnimator->PlayAnimation(L"Attack_01", true);

	}

	Grimm_Projectile_01::~Grimm_Projectile_01()
	{
		fTime = 0.f;
	}

	void Grimm_Projectile_01::Initialize()
	{

	}

	void Grimm_Projectile_01::Update()
	{
		
		fTime += Time::DeltaTime();

		GameObject::Update();

		Vector3 vPos = GetComponent<Transform>()->GetPosition();

		
		if (m_iDir == -1)
		{
			GetComponent<Transform>()->SetPosition(vPos.x - 0.01f, vPos.y + 0.001f, vPos.z);
		}
		else if(m_iDir == 1)
		{
			GetComponent<Transform>()->SetPosition(vPos.x + 0.01f, vPos.y + 0.001f, vPos.z);
		}

		if (fTime >= 3.f)
		{
 			SceneManager::DestoryObj(this);
			delete this;
			
		}
	}

	void Grimm_Projectile_01::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Grimm_Projectile_01::Render()
	{
		GameObject::Render();
	}


	void Grimm_Projectile_01::ChoosesAnim(int _dir)
	{
		m_iDir = _dir;

		if (m_iDir == -1)
			mAnimator->PlayAnimation(L"Attack_01", true);
		else
			mAnimator->PlayAnimation(L"Attack_01_r", true);
	}
}