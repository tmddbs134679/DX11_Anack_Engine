#include "AkBrumm.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"

namespace Ak
{
	Brumm::Brumm()
	{
		SetName(L"Brumm");

		std::shared_ptr<Texture> Brumm
			= Resources::Load<Texture>(L"Brumm_txt", L"..\\Resources\\Texture\\NPC\\Grimm_in\\Brumm.png");


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(-40.f, -3.9f, 1.01f));
		tr->SetScale(3.f, 3.f, 0.f);



		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Brumm_Ani", Brumm, Vector2(0.0f, 0.0f), Vector2(200.f, 330.f), 9, Vector2::Zero, 0.12f);
	
		mAnimator->PlayAnimation(L"Brumm_Ani", true);


	}

	Brumm::~Brumm()
	{
	
	}

	void Brumm::Initialize()
	{

	}

	void Brumm::Update()
	{
		GameObject::Update();
	}

	void Brumm::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Brumm::Render()
	{
		GameObject::Render();
	}
}

