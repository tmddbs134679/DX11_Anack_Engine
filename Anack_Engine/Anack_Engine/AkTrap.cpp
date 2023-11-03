#include "AkTrap.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkAnimator.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"


namespace Ak
{
	Trap::Trap()
	{
		SetName(L"Trap");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		
		std::shared_ptr<Texture> Trap_01
			= Resources::Load<Texture>(L"Trap_01", L"..\\Resources\\Texture\\Abyss\\Trap\\Trap.png");


		GetComponent<Transform>()->SetScale(Vector3(30.f, 10.f, 0.f));


		Animator* aAnimator = AddComponent<Animator>();


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		AddComponent<Collider2D>();
		GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -5.f));


		aAnimator->Create(L"Trap_01", Trap_01, Vector2(0.0f, 0.0f), Vector2(115.f, 99.f), 3);

		aAnimator->PlayAnimation(L"Trap_01", true);

	}

	Trap::~Trap()
	{

	}

	void Trap::Initialize()
	{

	}

	void Trap::Update()
	{
		GameObject::Update();
	}

	void Trap::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Trap::Render()
	{
		GameObject::Render();
	}
}
