#include "AkParticleSystem.h"
#include "AkMesh.h"
#include "AkResources.h"
#include "AkTransform.h"
#include "AkGameObject.h"
#include "AkTime.h"
#include "AkConstantBuffer.h"
#include "AkRenderer.h"
#include "AkFontWrapper.h"
#include <random>

namespace Ak
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
		, m_iParticleCount(1000)
		, m_fParticleSpeed(0.f)
		, m_vParticleDirection(Vector4::Zero)
		, m_fParticleDestory(1.f)
		, m_fParticleRandom(0.f)
		, m_vOffSet(Vector3::Zero)
		, m_fEndSize(100.f)
		, m_fStartSize(100.f)
		, m_bRandomZ(false)
		, m_fRotationSpeed(0.f)
		, m_fStartRotation(0.f)
		, m_fScale(1.f)
		, m_fAngle1(0.f)
		, m_fAngle2(0.f)
		, m_bDirectionRandom(false)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{

			
			Vector4 pos = Vector4::Zero;
			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
			particles[i].time = 0.f;
			//particles[i].size = m_fScale;
		}


		mBuffer = new graphics::StructedBuffer();
		mBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particles);

		m_SharedBuffer = new graphics::StructedBuffer();
		m_SharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);


	}

	ParticleSystem::~ParticleSystem()
	{
		delete m_SharedBuffer;
		delete mBuffer;
	}

	void ParticleSystem::Initialize()
	{

	}

	void ParticleSystem::Update()
	{

	}

	void ParticleSystem::LateUpdate()
	{
		
		float AliveTime = 1.0f / 10.f;
		mTime += Time::DeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 1;
			m_SharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			m_SharedBuffer->SetData(&shareData, 1);
		}

		mCS->SetParticleBuffer(mBuffer);
		mCS->SetSharedBuffer(m_SharedBuffer);
		mCS->OnExcute();

	}

	void ParticleSystem::Render()
	{
		Vector3 pos = GetOwner()->mTransform->GetPosition();

		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		//GetOwner()->mTransform->BindConstantBuffer();
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

	

		static float elapsedTime = 0.0f;
		elapsedTime += Time::DeltaTime();

		renderer::ParticleCB data = {};
		//data.elementCount = mBuffer->GetStride();
		data.particleElementCount = m_iParticleCount;
		data.particleStartSpeed = m_fParticleSpeed;
		data.particleElpasedTime = Time::DeltaTime();
		data.particleDeltaTime = Time::DeltaTime();
		data.particleDirection = m_vParticleDirection;
		data.particleDestoryTime = m_fParticleDestory;
		data.particleOffset = m_vOffSet;
		data.particlePos = pos;
		data.particleRandom = m_fParticleRandom;
		//data.particleEndSize = m_fEndSize;
		//data.particleStartSize = m_fStartSize;
		data.bParticleTest = m_bRandomZ;
		data.particleStartRotation = XMConvertToRadians(m_fStartRotation);
		data.particleRotationSpeed = XMConvertToRadians(m_fRotationSpeed);
		data.particleScale = m_fScale;
		data.particleAngle1 = XMConvertToRadians(m_fAngle1);
		data.particleAngle2 = XMConvertToRadians(m_fAngle2);
		data.particleRandomDirection = m_bDirectionRandom;

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);


		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mBuffer->Clear();
	
	}

	
}
