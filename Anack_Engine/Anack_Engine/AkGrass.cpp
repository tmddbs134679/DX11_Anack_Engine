#include "AkGrass.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkAnimator.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"

namespace Ak
{
	Grass::Grass()
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");


		std::shared_ptr<Texture> Grass_01
			= Resources::Load<Texture>(L"Grass_01", L"..\\Resources\\Texture\\Grass\\grass_01.png");

		std::shared_ptr<Texture> Grass_02
			= Resources::Load<Texture>(L"Grass_02", L"..\\Resources\\Texture\\Grass\\grass_02.png");

		std::shared_ptr<Texture> Grass_03
			= Resources::Load<Texture>(L"Grass_03", L"..\\Resources\\Texture\\Grass\\grass_03.png");

		Animator* aAnimator = AddComponent<Animator>();
		

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		aAnimator->Create(L"Grass_01", Grass_01, Vector2(0.0f, 0.0f), Vector2(88.0f, 100.f), 8);
		aAnimator->Create(L"Grass_02", Grass_02, Vector2(0.0f, 0.0f), Vector2(107.0f, 118.f), 9);
		aAnimator->Create(L"Grass_03", Grass_03, Vector2(0.0f, 0.0f), Vector2(130.0f, 246.f), 7);


		aAnimator->PlayAnimation(L"Grass_01", true);
	}

	Grass::~Grass()
	{

	}

	void Grass::Initialize()
	{

	}

	void Grass::Update()
	{
		GameObject::Update();
	}

	void Grass::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Grass::Render()
	{
		GameObject::Render();
	}

}
