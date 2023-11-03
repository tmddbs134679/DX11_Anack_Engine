#include "AkGraphicDevice_Dx11.h"
#include "AkApplication.h"
#include "AkRenderer.h"
#include "AkInput.h"
#include "AkTime.h"


extern Ak::Application application;


namespace Ak::graphics
{

	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf());

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)mRenderTarget.GetAddressOf())))
			return;

		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get()
			, nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{

	}

	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = _hwnd;
		//Windowed 창모드여부
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = _desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = _desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = _desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;

	}

	//test
	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}

	//bool GraphicDevice_Dx11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* _desc, void* _data, ID3D11Texture2D** _ppTexture2D)
	//{
	//	if (FAILED(mDevice->CreateTexture2D(_desc, nullptr, _ppTexture2D)))
	//		return false;

	//	return true;
	//}

	bool GraphicDevice_Dx11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementLayout, UINT _NumElements, ID3DBlob* _bytecode, ID3D11InputLayout** _ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(
			_pInputElementLayout,
			_NumElements,
			_bytecode->GetBufferPointer(),
			_bytecode->GetBufferSize(),
			_ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data)
	{
		
		if (FAILED(mDevice->CreateBuffer(_desc, _data, _buffer)))
			return false;

		return true;
	}


	bool GraphicDevice_Dx11::CompileFromfile(const std::wstring& _fileName, const std::string& _funName, const std::string& _version, ID3DBlob** _ppCode)
	{
		ID3DBlob* errorBlob = nullptr;

		D3DCompileFromFile(
			_fileName.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_funName.c_str(),
			_version.c_str(),
			0,
			0,
			_ppCode,
			&errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}

	bool GraphicDevice_Dx11::CreateVertexShader(const void* _pShaderBycode, SIZE_T _BytecodeLength, ID3D11VertexShader** _ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(_pShaderBycode, _BytecodeLength, nullptr, _ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateGeometryShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11GeometryShader** _ppGeometryShader)
	{
		if (FAILED(mDevice->CreateGeometryShader(_pShaderBytecode, _BytecodeLength, nullptr, _ppGeometryShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreatePixelShader(const void* _pShaderBycode, SIZE_T _BytecodeLength, ID3D11PixelShader** _ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(_pShaderBycode, _BytecodeLength, nullptr, _ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateComputeShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11ComputeShader** _ppComputeShader)
	{
		if (FAILED(mDevice->CreateComputeShader(_pShaderBytecode, _BytecodeLength, nullptr, _ppComputeShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState)
	{
		if(FAILED(mDevice->CreateSamplerState(_pSamplerDesc, _ppSamplerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateRasterizeState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(_pRasterizerDesc, _ppRasterizerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc, ID3D11DepthStencilState** _ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(_pDepthStencilDesc, _ppDepthStencilState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBlendState(const D3D11_BLEND_DESC* _pBlendStateDesc, ID3D11BlendState** _ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(_pBlendStateDesc, _ppBlendState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDSV)
	{
		if (FAILED(mDevice->CreateDepthStencilView(_pResource, _pDesc, _ppDSV)))
			return false;

		return true;
	}


	bool GraphicDevice_Dx11::CreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(_pResource, _pDesc, _ppRTView)))
			return false;

		return true;
	}



	bool GraphicDevice_Dx11::CreateShaderResourceView(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc 
													  ,ID3D11ShaderResourceView** _ppSRView)
	{
		if (FAILED(mDevice->CreateShaderResourceView(_pResource, _pDesc, _ppSRView)))
			return false;

		return true;
	}


	bool GraphicDevice_Dx11::CreateUnorderedAccessView(ID3D11Resource* _pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* _pDesc, ID3D11UnorderedAccessView** _ppURV)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(_pResource, _pDesc, _ppURV)))
			return false;

		return true;
	}


	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* _ViewPort)
	{
		mContext->RSSetViewports(1, _ViewPort);

	}

	void GraphicDevice_Dx11::BindRasterizeState(ID3D11RasterizerState* _pRasterizerState)
	{
		mContext->RSSetState(_pRasterizerState);
	}

	void GraphicDevice_Dx11::BindDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
	{
		mContext->OMSetDepthStencilState(_pDepthStencilState, 0);
	}

	void GraphicDevice_Dx11::BindBlendState(ID3D11BlendState* _pBlendState)
	{
		mContext->OMSetBlendState(_pBlendState, nullptr, 0xffffffff);
	}

	void GraphicDevice_Dx11::CopyResource(ID3D11Resource* _pDstResource, ID3D11Resource* _pSrcResource)
	{
		mContext->CopyResource(_pDstResource, _pSrcResource);
	}

	void GraphicDevice_Dx11::BindInputLayout(ID3D11InputLayout* _pInputLayout)
	{
		mContext->IASetInputLayout(_pInputLayout);
	}

	void GraphicDevice_Dx11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
	{
		//mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mContext->IASetPrimitiveTopology(_Topology);
	}

	void GraphicDevice_Dx11::BindVertexBuffer(UINT _StartSlot, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets)
	{
		mContext->IASetVertexBuffers(_StartSlot, 1, _ppVertexBuffers, _pStrides, _pOffsets);
	}

	void GraphicDevice_Dx11::BindHullShader(ID3D11HullShader* _pHullShader)
	{
		mContext->HSSetShader(_pHullShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindDomainShader(ID3D11DomainShader* _pDomainShader)
	{
		mContext->DSSetShader(_pDomainShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindGeometryShader(ID3D11GeometryShader* _pGeometryShader)
	{
		mContext->GSSetShader(_pGeometryShader, 0, 0);
	}


	void GraphicDevice_Dx11::BindIndexBuffer(ID3D11Buffer* _buffer, DXGI_FORMAT _Format, UINT _Offset)
	{
		mContext->IASetIndexBuffer(_buffer, _Format, _Offset);
	}

	void GraphicDevice_Dx11::BindVertexShader(ID3D11VertexShader* _pVertexShader)
	{
		mContext->VSSetShader(_pVertexShader, 0, 0);
		
	}

	void GraphicDevice_Dx11::BindPixelShader(ID3D11PixelShader* _pPixelShader)
	{
		mContext->PSSetShader(_pPixelShader, 0, 0);
	}


	void GraphicDevice_Dx11::BindComputeShader(ID3D11ComputeShader* _pComputeShader)
	{
		mContext->CSSetShader(_pComputeShader, 0, 0);
	}

	void GraphicDevice_Dx11::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		mContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}

	void GraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _size)
	{
		//상수버퍼랑 subRes 매핑
		D3D11_MAPPED_SUBRESOURCE SubRes = {};

		//메모리복사
		mContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubRes);
		memcpy(SubRes.pData, _data, _size);
		//할당 해제
		mContext->Unmap(_buffer, 0);

	}

	void GraphicDevice_Dx11::BindConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer)
	{
		switch (_stage)
		{
		case eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::END:

			break;
		}
	}

	void GraphicDevice_Dx11::BindsConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer)
	{
			
		mContext->VSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->HSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->DSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->GSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->PSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->CSSetConstantBuffers((UINT)_type, 1, &_buffer);
				
	}

	void GraphicDevice_Dx11::BindBuffer(ID3D11Buffer* _buffer, void* _data, UINT _size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, _data, _size);
		mContext->Unmap(_buffer, 0);
	}


	void GraphicDevice_Dx11::BindShaderResource(eShaderStage _stage, UINT _startSlot, ID3D11ShaderResourceView** _ppSRV)
	{
		switch (_stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(_startSlot, 1, _ppSRV);
			break;
		case eShaderStage::END:
			break;
	
		}
	}


	void GraphicDevice_Dx11::BindUnorderedAccess(UINT _slot, ID3D11UnorderedAccessView** _ppURV, const UINT* _pUAVInitialCounts)
	{
		mContext->CSSetUnorderedAccessViews(_slot, 1, _ppURV, _pUAVInitialCounts);
	}


	void GraphicDevice_Dx11::BindSampler(eShaderStage _Stage, UINT _StartSlot, ID3D11SamplerState** _ppSamplers)
	{

		switch (_Stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(_StartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::END:
			break;
		}
	}

	void GraphicDevice_Dx11::KeyInput()
	{
	/*	
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			renderer::Pos.x -= 0.6f * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			renderer::Pos.x += 0.6f * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
		{
			renderer::Pos.y += 0.6f * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN))
		{
			renderer::Pos.y -= 0.6f * Time::DeltaTime();
		}*/
	}

	void GraphicDevice_Dx11::DrawIndexed(UINT _idxCount, UINT _StartIdxLoc, INT _BaseVertexIdxLoc)
	{
		mContext->DrawIndexed(_idxCount, _StartIdxLoc, _BaseVertexIdxLoc);
	}

	void GraphicDevice_Dx11::DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation,
		INT _BaseVertexLocation, UINT _StartInstanceLocation)
	{
		mContext->DrawIndexedInstanced(_IndexCountPerInstance, _InstanceCount, _StartIndexLocation, _BaseVertexLocation, _StartInstanceLocation);
	}
	


	void GraphicDevice_Dx11::ClearTarget()
	{
		// render target clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

	}

	void GraphicDevice_Dx11::UpdateViewPort()
	{
		//키입력 이동
		KeyInput();

		//viewport update
		HWND Hwnd = application.GetHwnd();
		RECT WindRect = {};
		GetClientRect(Hwnd, &WindRect);

		mViewPort =
		{
			0.f,
			0.f,
			(float)(WindRect.right - WindRect.left),
			(float)(WindRect.bottom - WindRect.top),
			0.f,
			1.f
		};

		BindViewPort(&mViewPort);

	}

	void GraphicDevice_Dx11::Draw()
	{
		
	
		
	}

	void GraphicDevice_Dx11::Present()
	{
		mSwapChain->Present(0, 0);
	}
}

