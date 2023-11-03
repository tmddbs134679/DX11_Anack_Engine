#include "AkCoin.h"
#include "AkResources.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkCoinScript.h"
#include "AkSceneManager.h"


namespace Ak
{
	Coin::Coin()
	{
		SetName(L"Coin");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> Coin_ani
			= Resources::Load<Texture>(L"Coin_ani_txt", L"..\\Resources\\Texture\\BattleScene\\Coin\\Coin.png");



		GetComponent<Transform>()->SetScale(3.f, 3.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));


		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Coin_ani", Coin_ani, Vector2(0.0f, 0.0f), Vector2(58.f, 70.f), 7);


		mAnimator->PlayAnimation(L"Coin_ani", true);

		Collider2D* cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(0.3f, 0.3f));
		
	/*	CoinScript* cs = AddComponent<CoinScript>();
		cs->SetCoin(this);*/
	}

	Coin::~Coin()
	{
		SceneManager::DestoryObj(this);
	}

	void Coin::Initialize()
	{

	}

	void Coin::Update()
	{
		GameObject::Update();
	}

	void Coin::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Coin::Render()
	{
		GameObject::Render();
	}

}