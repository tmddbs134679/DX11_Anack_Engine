#include "AkRadiance_Light.h"
#include "AkShader.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAudioClip.h"

namespace Ak
{
	Radiance_Light::Radiance_Light()
		: m_bAudioOn(true)
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"MonsterShader");

		std::shared_ptr<Texture> Radiance_Light_idle
			= Resources::Load<Texture>(L"Radiance_Light_idle_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_Light\\Radiance_Light_idle.png");

		std::shared_ptr<Texture> Radiance_Light
			= Resources::Load<Texture>(L"Radiance_Light_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_Light\\Radiance_Light.png");


		GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);
		GetComponent<Transform>()->SetPosition(Vector3(0.f, 5.f, 1.2f));
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterMaterial"));


		mAnimator = AddComponent<Animator>();

		mAnimator->SetMulSize(2);

		mAnimator->Create(L"Radiance_Light_idle", Radiance_Light_idle, Vector2(0.0f, 0.0f), Vector2(250.f, 200.f), 1);
		mAnimator->Create(L"Radiance_Light", Radiance_Light, Vector2(0.0f, 0.0f), Vector2(250.f, 200.f), 10);

		mAnimator->PlayAnimation(L"Radiance_Light_idle", false);

		m_ac = Resources::Load<AudioClip>(L"Radiance_in", L"..\\Resources\\Sound\\Radiance\\radiance_in_01.mp3");
		
	}

	Radiance_Light::~Radiance_Light()
	{

	}

	void Radiance_Light::Initialize()
	{

	}

	void Radiance_Light::Update()
	{

		if (m_bAudioOn)
		{
			if (mAnimator->GetPlayAnimationName() == L"Radiance_Light")
			{
				m_ac->Play();
				m_bAudioOn = false;
			}
		}
	

		GameObject::Update();
	}

	void Radiance_Light::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Light::Render()
	{
		GameObject::Render();
	}

}