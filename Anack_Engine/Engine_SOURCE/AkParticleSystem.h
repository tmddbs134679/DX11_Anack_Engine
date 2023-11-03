#pragma once
#include "AkMeshRenderer.h"
#include "AkStructedBuffer.h"
#include "AkParticleShader.h"
namespace Ak
{
	class ParticleSystem :
		public MeshRenderer
	{
		

	public:
	

		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	

	public:

		void SetParticleCount(int _int)
		{
			m_iParticleCount = _int;
		}


		void SetParticleSpeed(float _f)
		{
			m_fParticleSpeed = _f;
		}

		void SetParticleDirection(Vector4 _vec)
		{
			m_vParticleDirection = _vec;
		}

		void SetParticleDestory(float _f)
		{
			m_fParticleDestory = _f;
		}

		void SetParticleOffset(Vector3 _v)
		{
			m_vOffSet = _v;
		}

		void SetParticleRandom(float _f)
		{
			m_fParticleRandom = _f;
		}

		void SetSize(float _f)
		{
			m_fScale = _f;
		}

		void SetRandomZ(bool _b)
		{
			m_bRandomZ = _b;
		}

		void SetRotation(float _rotation, float _speed)
		{
			//시작 회전각도
			m_fStartRotation = _rotation;
			//회전 속도
			m_fRotationSpeed = _speed;
		}

		void SetAngle(float _f1, float _f2)
		{
			m_fAngle1 = _f1;
			m_fAngle2 = _f2;
		}
		
		void SetRandomDirection(bool _b)
		{
			m_bDirectionRandom = _b;
		}

	private:
		graphics::StructedBuffer* mBuffer;
		graphics::StructedBuffer* m_SharedBuffer;

		std::shared_ptr<ParticleShader> mCS;
		

		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
		float	mFrequency;

		float mTime;


		int	m_iParticleCount;
		float m_fParticleSpeed;
		Vector4 m_vParticleDirection;
		float m_fParticleDestory;

		Vector3 m_vOffSet;
		float m_fParticleRandom;
		float m_fStartSize;
		float m_fEndSize;
	
		bool m_bRandomZ;
		
		float m_fStartRotation;
		float m_fRotationSpeed;

		float m_fScale;

		float m_fAngle1;
		float m_fAngle2;

		bool m_bDirectionRandom;

	private:


		std::shared_ptr<ParticleShader> mParticleShader;


	};
}