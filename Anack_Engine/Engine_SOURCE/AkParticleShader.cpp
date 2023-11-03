#include "AkParticleShader.h"
#include "AkRenderer.h"
#include "AkConstantBuffer.h"
#include "AkTime.h"



namespace Ak::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, m_ParticleBuffer(nullptr)
		, m_SharedBuffer(nullptr)
	{

	}

	ParticleShader::~ParticleShader()
	{

	}

	void ParticleShader::Binds()
	{
		m_ParticleBuffer->BindUAV(0);
		m_SharedBuffer->BindUAV(1);


		mGroupX = m_ParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;

	}

	void ParticleShader::Clear()
	{
		m_ParticleBuffer->Clear();
		m_SharedBuffer->Clear();
	}

	void ParticleShader::SetParticleBuffer(StructedBuffer* _particleBuffer)
	{
		m_ParticleBuffer = _particleBuffer;

	

	}

}