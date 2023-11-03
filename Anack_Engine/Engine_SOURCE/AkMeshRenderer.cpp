#include "AkMeshRenderer.h"
#include "AkGameObject.h"
#include "AkTransform.h"
#include "AkRenderer.h"
#include "AkResource.h"
#include "AkMesh.h"
#include "AkMaterial.h"
#include "AkResources.h"
#include "AkAnimator.h"


namespace Ak
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{

	}

	MeshRenderer::~MeshRenderer()
	{

	}
	void MeshRenderer::Initialize()
	{
	
	}

	void MeshRenderer::Update()
	{

	}

	void MeshRenderer::LateUpdate()
	{

	}

	void MeshRenderer::SetMeshRenderer(const std::wstring _meshKey, const std::wstring _materialKey)
	{
		mMesh = Ak::Resources::Find<Mesh>(_meshKey);
		assert(mMesh != nullptr);

		mMaterial = Ak::Resources::Find<Material>(_materialKey);
		assert(mMaterial != nullptr);
	}

	void MeshRenderer::Render()
	{
		Transform* Tr = GetOwner()->GetComponent<Transform>();
		Tr->BindConstantBuffer();
		
		mMesh->BindBuffer();
		mMaterial->Binds();

		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (animator)
		{

			animator->Binds();

		}

		mMesh->Render();
		mMaterial->Clear();

	}
}