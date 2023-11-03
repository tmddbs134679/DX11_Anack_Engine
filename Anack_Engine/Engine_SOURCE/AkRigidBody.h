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

		Vector2		m_vForce;		// ũ��, ����
		Vector2		m_vAccel;		// ���ӵ�
		Vector2		m_vAccelA;		//�߰� ���ӵ� 
		Vector2		m_vVelocity;	//�ӵ�(ũ�� : �ӷ�, ����)  
		Vector2		m_vMaxVelocity;	//�ִ� �ӷ�
		Vector2     m_vAddPos;

		//float		m_fSpeed		//�ӷ�(������ �ӵ��� ��)
		float		m_fMass;		// ����
		float		m_fricCoeff;	//���� ���

		bool		m_bGround;
		Vector2		m_Gravity;

		

	};


}
