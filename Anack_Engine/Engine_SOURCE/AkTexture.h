#pragma once
#include "AkResource.h"
#include"AkGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif


namespace Ak::graphics
{
	class Texture :
		public Resource
	{
	public:
		Texture();
		~Texture();


	public:
		//bool Create(UINT _width, UINT _height, DXGI_FORMAT _format, UINT _bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShaderResource(eShaderStage _stage, UINT _startSlot);
		void BindUnorderedAccessViews(UINT _slot);
		void ClearUnorderedAccessViews(UINT _slot);

		//test
		void BindShader(eShaderStage stage, UINT startSlot);

		void Clear();


	public:
		//void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _rtv)
		//{
		//	mRenderTargetView = _rtv;
		//}

		//void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _dsv)
		//{
		//	mDepthStencilView = _dsv;
		//}

		//void SetUAV(Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> _uav)
		//{
		//	mUnorderedAccessView = _uav;
		//}

		//void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture)
		//{
		//	mTexture = _texture;
		//}

	public:
		size_t GetWidth() { return mImage.GetMetadata().width; }
		size_t GetHeight() { return mImage.GetMetadata().height; }

		//size_t GetWidth()
		//{
		//	return mWidth;
		//}

		//size_t GetHeight()
		//{
		//	return mWidth;
		//}

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV()
		{
			return mShaderResourceView;
		}

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV()
		{
			return mRenderTargetView;
		}

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV()
		{
			return mDepthStencilView;
		}

		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV()
		{
			return mUnorderedAccessView;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture()
		{
			return mTexture;
		}

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  mDepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>  mUnorderedAccessView;

		D3D11_TEXTURE2D_DESC mDesc;


		UINT mWidth;
		UINT mHeight;

	};

}
