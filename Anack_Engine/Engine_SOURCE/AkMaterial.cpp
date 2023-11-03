#include "AkMaterial.h"

namespace Ak::graphics
{
	Material::Material()
		: Resource(Ak::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
	{

	}

	Material::~Material()
	{

	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{	
		//test
		if(mTexture)
			mTexture->BindShader(eShaderStage::PS, 0);
			//mTexture->BindShaderResource(eShaderStage::PS, 0);

		if(mShader)
			mShader->Binds();
	}

	void Material::Clear()
	{
		mTexture->Clear();
	}
 
}

