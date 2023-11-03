#pragma once
#include "AkResource.h"
#include "AkGraphics.h"

namespace Ak::graphics
{

	class ComputeShader :
		public Resource
	{
	public:
		ComputeShader(int x, int y, int z);
		ComputeShader();
		virtual ~ComputeShader();

	public:

		virtual void Binds();
		virtual void Clear();

		bool Create(const std::wstring& _name, const std::string& _methodName);

		void OnExcute();

	

	public:

		virtual HRESULT Load(const std::wstring& path)
		{
			return S_FALSE;
		}


	protected:


		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader>	mCS;

		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;
	};


}
