#pragma once
#include "AkGraphics.h"
#include "AkEntity.h"

namespace Ak::graphics
{

	class StructedBuffer :
		public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();


		bool Create(UINT _size, UINT _stride, eViewType _type, void* _data, bool cpuAccess = false);
		bool CreateRWBuffer();
		void SetData(void* _data, UINT _stride);
		void GetData(void* _data, UINT _size);
		void BindSRV(eShaderStage _stage, UINT _slot);
		void BindUAV(UINT _slot);

		void Clear();


	public:

		UINT GetSize()
		{
			return mSize;
		}

		UINT GetStride()
		{
			return mStride;
		}

	private:

		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_ReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_WriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eViewType	mType;

		UINT		mSize;
		UINT		mStride;

		UINT		mSRVSlot;
		UINT		mUAVSlot;


	};



}