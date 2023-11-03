#include "AkComputeShader.h"
#include "AkGraphicDevice_Dx11.h"

namespace Ak::graphics
{
	ComputeShader::ComputeShader(int x, int y ,int z)
		: Resource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = x;
		mThreadGroupCountY = y;
		mThreadGroupCountZ = z;
	}

	ComputeShader::ComputeShader()
		: Resource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = 32;
		mThreadGroupCountY = 32;
		mThreadGroupCountZ = 1;
	}

	ComputeShader::~ComputeShader()
	{
	}



	bool ComputeShader::Create(const std::wstring& _name, const std::string& _methodName)
	{
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += _name;

		ID3DBlob* errorBlob = nullptr;
		graphics::GetDevice()->CompileFromfile(fullPath, _methodName, "cs_5_0", mCSBlob.GetAddressOf());
		graphics::GetDevice()->CreateComputeShader(mCSBlob->GetBufferPointer()
			, mCSBlob->GetBufferSize(), mCS.GetAddressOf());
		return false;
	}

	void ComputeShader::OnExcute()
	{
		Binds();

		GetDevice()->BindComputeShader(mCS.Get());
		GetDevice()->Dispatch(mGroupX, mGroupY, mGroupZ);

		Clear();

	}


	void ComputeShader::Binds()
	{

	}

	void ComputeShader::Clear()
	{

	}


}