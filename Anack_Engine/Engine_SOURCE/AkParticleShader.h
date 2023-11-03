#pragma once
#include "AkComputeShader.h"
#include "AkStructedBuffer.h"

namespace Ak::graphics
{

	class ParticleShader :
		public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds();
		virtual void Clear();

		void SetParticleBuffer(StructedBuffer* _particleBuffer);


	public:

		void SetSharedBuffer(StructedBuffer* _sharedBuffer)
		{
			m_SharedBuffer = _sharedBuffer;
		}


	private:
		StructedBuffer* m_ParticleBuffer;
		StructedBuffer* m_SharedBuffer;
	};



}