#include "AkRG_Short.h"
#include "AkShader.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkGroundScript.h"

namespace Ak
{
	RG_Short::RG_Short()
	{
		
		
		AddComponent<Collider2D>()->SetSize(Vector2(0.8f, 0.3f));
		AddComponent<GroundScript>();



		MeshRenderer* mr_radiance_gd = AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Ground_S"));
		GetComponent<Transform>()->SetScale(2.f, 1.5f, 0.f);

	}

	RG_Short::~RG_Short()
	{

	}

	void RG_Short::Initialize()
	{

	}

	void RG_Short::Update()
	{
		GameObject::Update();
	}

	void RG_Short::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RG_Short::Render()
	{
		GameObject::Render();
	}
}
