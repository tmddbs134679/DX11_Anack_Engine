#include "AkRadianceBG.h"
#include "AkResources.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"


namespace Ak
{
	RadianceBG::RadianceBG()
	{

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteAnimationShader");

		std::shared_ptr<Texture> Radiance_BG
			= Resources::Load<Texture>(L"Radiance_BG_txt", L"..\\Resources\\Texture\\Dream\\Radiance_BG.png");

		GetComponent<Transform>()->SetScale(100.f, 150.f, 0.f);


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		

		mAnimator = AddComponent<Animator>();

		mAnimator->SetMulSize(10);

		mAnimator->Create(L"Radiance_BG", Radiance_BG, Vector2(0.0f, 0.0f), Vector2(1000.f, 1000.f), 1);

		mAnimator->PlayAnimation(L"Radiance_BG", false);


	}

	RadianceBG::~RadianceBG()
	{

	}

	void RadianceBG::Initialize()
	{

	}

	void RadianceBG::Update()
	{
		
		GameObject::Update();
	}

	void RadianceBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RadianceBG::Render()
	{
		GameObject::Render();
	}
}