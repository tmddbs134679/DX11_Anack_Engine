#include "AkFlame.h"
#include "AkResources.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"


namespace Ak
{
	Flame::Flame()
	{
		SetName(L"Flame");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> Flame01
			= Resources::Load<Texture>(L"Flame_txt", L"..\\Resources\\Texture\\BossScene\\grimm_flame.png");

		GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
	
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Flame01", Flame01, Vector2(0.0f, 0.0f), Vector2(82.f, 82.f), 9);


		mAnimator->PlayAnimation(L"Flame01", true);
	}

	Flame::~Flame()
	{

	}

	void Flame::Initialize()
	{

	}

	void Flame::Update()
	{
		GameObject::Update();
	}

	void Flame::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Flame::Render()
	{
		GameObject::Render();
	}

}