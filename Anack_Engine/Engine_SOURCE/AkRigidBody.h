#pragma once
#include "AkComponent.h"

using namespace Ak::math;


namespace Ak
{
	class RigidBody :
		public Component
	{
	public:
		RigidBody();
		~RigidBody();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	public:
		void Move();


	public:

		void AddForce(Vector2 _vF)
		{
			m_vForce += _vF;
		}

		void SetMass(float _fMass)
		{
			m_fMass = _fMass;
		}

		void SetVelocity(Vector2 _v)
		{
			m_vVelocity = _v;
		}

		void SetMaxVelocity(Vector2 _v)
		{
			m_vMaxVelocity = _v;
		}

		void SetAccelAlpha(Vector2 _vAccel)
		{
			m_vAccelA = _vAccel;
		}

		void SetGround(bool _bool)
		{
			m_bGround = _bool;
		}


		void SetGravity(Vector2 _gravity)
		{
			m_Gravity = _gravity;
		}

		void SetAddPos(Vector2 _vec)
		{
			m_vAddPos = _vec;
		}
	public:

		void AddVelocity(Vector2 _v)
		{
			m_vVelocity += _v;
		}

		float GetMass()
		{
			return m_fMass;
		}

		Vector2 GetVelocity()
		{
			return m_vVelocity;
		}

		bool IsGround()
		{
			return m_bGround;
		}
	

	private:

		Vector2		m_vForce;		// 크기, 방향
		Vector2		m_vAccel;		// 가속도
		Vector2		m_vAccelA;		//추가 가속도 
		Vector2		m_vVelocity;	//속도(크기 : 속력, 방향)  
		Vector2		m_vMaxVelocity;	//최대 속력
		Vector2     m_vAddPos;

		//float		m_fSpeed		//속력(순수한 속도의 양)
		float		m_fMass;		// 질량
		float		m_fricCoeff;	//마찰 계수

		bool		m_bGround;
		Vector2		m_Gravity;

		

	};


}
