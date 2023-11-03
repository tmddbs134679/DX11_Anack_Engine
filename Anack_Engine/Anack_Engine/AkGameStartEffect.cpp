#include "AkGameStartEffect.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkAnimator.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"

namespace Ak
{
	GameStartEffect::GameStartEffect()
	{
		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Game_Start_Effect01"));

	}

	GameStartEffect::~GameStartEffect()
	{

	}

	void GameStartEffect::Initialize()
	{
	
	}

	void GameStartEffect::Update()
	{
		GameObject::Update();
	}

	void GameStartEffect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void GameStartEffect::Render()
	{
		GameObject::Render();
	}

}