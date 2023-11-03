#include "AkRadiance_Projectile_02.h"
#include "AkMeshRenderer.h"
#include"AkResources.h"
#include "AkTime.h"
#include "AkRigidBody.h"

namespace Ak
{
	Radiance_Projectile_02::Radiance_Projectile_02()
	{
		MeshRenderer* mr_radiance_gd = AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Attack_02"));

		Collider2D* cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(0.5f, 0.5f));
		AddComponent<RigidBody>();
		GetComponent<RigidBody>()->SetGravity(Vector2(0.f, 0.5f));


		GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);


		m_ac = Resources::Load<AudioClip>(L"Radiance_Attack02", L"..\\Resources\\Sound\\Radiance\\radiance_sword_create_circular.mp3");
	}

	Radiance_Projectile_02::~Radiance_Projectile_02()
	{

	}
	void Radiance_Projectile_02::Initialize()
	{

	}

	void Radiance_Projectile_02::Update()
	{
		static float fTime = 0.f;
		fTime += Time::DeltaTime();

		GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, fTime * 4));
		GameObject::Update();
	}

	void Radiance_Projectile_02::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Projectile_02::Render()
	{
		GameObject::Render();
	}

}