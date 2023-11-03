#include "AkRG_Long.h"
#include "AkShader.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkGroundScript.h"

namespace Ak
{
	RG_Long::RG_Long()
	{
		
		AddComponent<Collider2D>()->SetSize(Vector2(0.8f, 0.5f));
		AddComponent<GroundScript>();

		

		MeshRenderer* mr_radiance_gd = AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"Radiance_Ground_L"));
		GetComponent<Transform>()->SetScale(Vector3(5.f, 2.f, 0.f));
		//SceneManager::AddGameObject(eLayerType::LayeredObj, m_Radiance_partcile);


	}

	RG_Long::~RG_Long()
	{

	}

	void RG_Long::Initialize()
	{

	}

	void RG_Long::Update()
	{
		GameObject::Update();
	}

	void RG_Long::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RG_Long::Render()
	{
		GameObject::Render();
	}
}
