#pragma once
#include "Anack_Engine.h"
#include "AkGraphics.h"
#include "AkTexture.h"

namespace Ak::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd);
		//bool CreateTexture2D(const D3D11_TEXTURE2D_DESC* _desc, void* _data, ID3D11Texture2D** _ppTexture2D);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementLayout, UINT _NumElements, ID3DBlob* _bytecode, ID3D11InputLayout** _ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data);
		bool CompileFromfile(const std::wstring& _fileName, const std::string& _funName, const std::string& _version, ID3DBlob** _ppCode);
		bool CreateVertexShader(const void* _pShaderBycode, SIZE_T _BytecodeLength, ID3D11VertexShader** _ppVertexShader);
		bool CreateGeometryShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11GeometryShader** _ppGeometryShader);
		bool CreatePixelShader(const void* _pShaderBycode, SIZE_T _BytecodeLength, ID3D11PixelShader** _ppPixelShader);
		bool CreateComputeShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ComputeShader** _ppComputeShader);
		bool CreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState);
		bool CreateRasterizeState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc, ID3D11DepthStencilState** _ppDepthStencilState);
		bool CreateBlendState(const D3D11_BLEND_DESC* _pBlendStateDesc, ID3D11BlendState** _ppBlendState);
		bool CreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDSV);
		bool CreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView);
		bool CreateShaderResourceView(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc, ID3D11ShaderResourceView** _ppSRView);
		bool CreateUnorderedAccessView(ID3D11Resource* _pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* _pDesc, ID3D11UnorderedAccessView** _ppURV);

		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);


		void BindInputLayout(ID3D11InputLayout* _pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
		void BindVertexBuffer(UINT _StartSlot, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);
		void BindHullShader(ID3D11HullShader* _pHullShader);
		void BindDomainShader(ID3D11DomainShader* _pDomainShader);
		void BindGeometryShader(ID3D11GeometryShader* _pGeometryShader);

		void BindIndexBuffer(ID3D11Buffer* _buffer, DXGI_FORMAT _Format, UINT _Offset);
		void BindVertexShader(ID3D11VertexShader* _pVertexShader);
		void BindPixelShader(ID3D11PixelShader* _pPixelShader);

		void BindComputeShader(ID3D11ComputeShader* _pComputeShader);
		void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);

		void SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _size);
		void BindConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer);
		void BindsConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer);
		void BindBuffer(ID3D11Buffer* _buffer, void* _data, UINT _size);
		void BindShaderResource(eShaderStage _stage, UINT _startSlot, ID3D11ShaderResourceView** _ppSRV);
		void BindUnorderedAccess(UINT _slot, ID3D11UnorderedAccessView** _ppURV, const UINT* _pUAVInitialCounts);

		void BindSampler(eShaderStage _Stage, UINT _StartSlot, ID3D11SamplerState** _ppSamplers);
		void BindViewPort(D3D11_VIEWPORT* _ViewPort);
		void BindRasterizeState(ID3D11RasterizerState* _pRasterizerState);
		void BindDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState);
		void BindBlendState(ID3D11BlendState* _pBlendState);
		void CopyResource(ID3D11Resource* _pDstResource, ID3D11Resource* _pSrcResource);


		void KeyInput();
		
		void DrawIndexed(UINT _idxCount, UINT _StartIdxLoc, INT _BaseVertexIdxLoc);
		void DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation, INT _BaseVertexLocation, UINT _StartInstanceLocation);


		void ClearTarget();
		void UpdateViewPort();
		
		void Draw();
		void Present();


		ID3D11Device* GetID3D11Device() 
		{
			return mDevice.Get();
		}

		ID3D11DeviceContext* GetID3D11DeviceContext() 
		{ 
			return mContext.Get(); 
		}

	private:
		//// 실제 그래픽카드 하드웨어 객체
		//Microsoft::WRL::ComPtr<ID3D11Device> mDevice;


		////  dx11에서 직접적으로 디바이스객체 접근하지않고
		//// 이객체를 이용하여 명령을 내린다.
		//Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		//// 최종적으로 그려질 텍스처(도화지)
		//std::shared_ptr<Ak::graphics::Texture> mRenderTarget;

		//// 깊이버퍼
		//std::shared_ptr<Ak::graphics::Texture> mDepthStencil;

		//// 더블버퍼링 작업을 진행해주는 swapChain
		//Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		//D3D11_VIEWPORT mViewPort;


		//test
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;

	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}