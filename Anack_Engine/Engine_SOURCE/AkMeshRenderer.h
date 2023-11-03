#pragma once
#include "AkComponent.h"
#include "AkMesh.h"
#include "AkMaterial.h"


namespace Ak
{
	class MeshRenderer :
		public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		
	public:

		void SetMeshRenderer(const std::wstring _meshKey, const std::wstring _materialKey);

	public:

		void SetMesh(std::shared_ptr<Mesh> _mesh)
		{
			mMesh = _mesh;
		}

		void SetMaterial(std::shared_ptr<Material> _material)
		{
			mMaterial = _material;
		}

	public:

		std::shared_ptr<Material> GetMaterial()
		{
			return mMaterial;
		}

		std::shared_ptr<Mesh> GetMesh()
		{
			return mMesh;
		}

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
		
	};


}