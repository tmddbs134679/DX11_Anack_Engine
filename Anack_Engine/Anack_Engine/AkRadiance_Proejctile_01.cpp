#include "AkRadiance_Proejctile_01.h"
#include "AkMeshRenderer.h"
#include"AkResources.h"
#include "AkParticleSystem.h"


namespace Ak
{
	Radiance_Proejctile_01::Radiance_Proejctile_01()
	{
		//Ã¢ °ø°Ý
		
		MeshRenderer* mr_radiance_gd = AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Attack_01"));

		Collider2D* cd =AddComponent<Collider2D>();
		cd->SetSize(Vector2(0.3f, 1.f));

		GetComponent<Transform>()->SetScale(1.f, 4.3f, 0.f);
		//GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 1.55f));

		m_ac = Resources::Load<AudioClip>(L"Radiance_Attack01", L"..\\Resources\\Sound\\Radiance\\radiance_sword_shoot.mp3");

		
		//ParticleSystem* pss = AddComponent<ParticleSystem>();
		//pss->GetMaterial()->SetTexture(Resources::Find<Texture>(L"Radiance_particle"));
		//pss->SetParticleCount(20);
		//pss->SetParticleSpeed(5.f);
		//pss->SetParticleDestory(30.f);
		////pss->SetParticleRandom(1.f);
		//pss->SetSize(5.f);
		////pss->SetRandomDirection(true);
		//pss->SetRotation(0.f, 30.f);

	}

	Radiance_Proejctile_01::~Radiance_Proejctile_01()
	{

	}

	void Radiance_Proejctile_01::Initialize()
	{

	}

	void Radiance_Proejctile_01::Update()
	{
		GameObject::Update();
	}

	void Radiance_Proejctile_01::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Proejctile_01::Render()
	{
		GameObject::Render();
	}

}