#include "AkEndingBG.h"
#include "AkResources.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"

namespace Ak
{
	EndingBG::EndingBG()
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteAnimationShader");

		std::shared_ptr<Texture> Ending_BG
			= Resources::Load<Texture>(L"Ending_BG_txt", L"..\\Resources\\Texture\\Ending.png");

		GetComponent<Transform>()->SetScale(100.f, 40.f, 0.f);


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));



		mAnimator = AddComponent<Animator>();

		mAnimator->SetMulSize(10);

		mAnimator->Create(L"Ending_BG", Ending_BG, Vector2(0.0f, 0.0f), Vector2(433.f, 630.f), 1);

		mAnimator->PlayAnimation(L"Ending_BG", false);

	}

	EndingBG::~EndingBG()
	{

	}

	void EndingBG::Initialize()
	{

	}

	void EndingBG::Update()
	{
		GameObject::Update();
	}

	void EndingBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EndingBG::Render()
	{
		GameObject::Render();
	}

}