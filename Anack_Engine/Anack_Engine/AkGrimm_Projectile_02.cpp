#include "AkGrimm_Projectile_02.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkTexture.h"
#include "AkTime.h"
#include "AkSceneManager.h"

namespace Ak
{

	Grimm_Projectile_02::Grimm_Projectile_02()
		: m_vMonPos(Vector2::Zero)
		, m_iCreatePJ(0)
	{
		SetName(L"GrimmAttack02");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> Attack_02
			= Resources::Load<Texture>(L"Attack_02_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack02_obj.png");


		GetComponent<Transform>()->SetScale(3.f, 2.f, 0.f);
		AddComponent<Collider2D>();

		GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.3f));
		GetComponent<Collider2D>()->SetCenter(Vector2(-0.1f, 0.f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Attack_02", Attack_02, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f), 7);

		mAnimator->PlayAnimation(L"Attack_02", true);
	}

	Grimm_Projectile_02::~Grimm_Projectile_02()
	{
		fTime = 0.f;
	}

	void Grimm_Projectile_02::Initialize()
	{

	}

	void Grimm_Projectile_02::Update()
	{
		GameObject::Update();
	}

	void Grimm_Projectile_02::LateUpdate()
	{
		GameObject::LateUpdate();

		////dir(-1,0)
		//if (iObj == 0)
		//{
		//	
		//	float UpdateX = m_vMonPos.x -= 0.005f;
		//	GetComponent<Transform>()->SetPosition(Vector3(UpdateX, m_vMonPos.y, 0.999f));
		//}
		////dir(1,0)
		//else if (iObj == 1)
		//{

		//	float UpdateX = m_vMonPos.x += 0.005f;
		//	GetComponent<Transform>()->SetPosition(Vector3(UpdateX, m_vMonPos.y, 0.9998f));
		//}
		////dir(0,-1)
		//else if (iObj == 2 || iObj == 3)
		//{

		//	float UpdateY = m_vMonPos.y -= 0.005f;
		//	GetComponent<Transform>()->SetPosition(Vector3(m_vMonPos.x, UpdateY, 0.9998f));
		//}
		////dir(-1,-1)
		//else if (iObj == 4)
		//{
		//	float UpdateX = m_vMonPos.x -= 0.005f;
		//	float UpdateY = m_vMonPos.y -= 0.005f;
		//	GetComponent<Transform>()->SetPosition(Vector3(UpdateX, UpdateY, 0.9998f));
		//}
		////dir(1,-1)
		//else if (iObj == 5)
		//{
		//	float UpdateX = m_vMonPos.x += 0.005f;
		//	float UpdateY = m_vMonPos.y -= 0.005f;
		//	GetComponent<Transform>()->SetPosition(Vector3(UpdateX, UpdateY, 0.9998f));
		//}
		

		Vector2 vc = CalculateDirection(m_fAngle);

		float UpdateX = m_vMonPos.x += (0.005f * vc.x);

		float UpdateY = m_vMonPos.y += (0.005f * vc.y);

		GetComponent<Transform>()->SetPosition(Vector3(UpdateX, UpdateY, 0.9998f));
		
		fTime += Time::DeltaTime();


		if (fTime >= 6.f)
		{
			SceneManager::DestoryObj(this);
			delete this;
			
			
		}
	}

	void Grimm_Projectile_02::Render()
	{
		GameObject::Render();
	}

	Vector2 Grimm_Projectile_02::CalculateDirection(float angle)
	{
		// 각도를 라디안으로 변환 (라디안 = 각도 * (π / 180))
		float radians = angle * (3.14159265359f / 180.0f);

		// 방향 벡터 계산 (사인과 코사인을 사용)
		float x = std::cos(radians); // x 방향
		float y = std::sin(radians); // y 방향

		return math::Vector2(x, y); // 방향 벡터 반환
	}

}