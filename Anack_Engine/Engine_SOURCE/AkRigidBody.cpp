#include "AkRigidBody.h"
#include "AkTime.h"
#include "AkGameObject.h"
#include "AkComponent.h"
#include "AkTransform.h"

namespace Ak
{

	RigidBody::RigidBody()
		: Component(eComponentType::RigidBody)
		, m_vForce(Vector2::Zero)
		, m_vAccel(Vector2::Zero)
		, m_vAccelA(Vector2::Zero)
		, m_vVelocity(Vector2::Zero)
		, m_vMaxVelocity(Vector2(10.f,18.f))
		, m_fMass(1.f)
		, m_fricCoeff(50.f)
		, m_bGround(false)
		, m_Gravity(Vector2(0.f,-70.f))
		, m_vAddPos(Vector2::Zero)
	{


	}

	RigidBody::~RigidBody()
	{

	}

	void RigidBody::Initialize()
	{

	}

	void RigidBody::Update()
	{
		
	}

	void RigidBody::LateUpdate()
	{
		float fForce = m_vForce.Length();

		if (fForce != 0.f)
		{
			m_vAccel = m_vForce / m_fMass;
		}

		m_vAccel += m_vAccelA;

		m_vVelocity += m_vAccel * Time::DeltaTime();



		//마찰력
		if (!(m_vVelocity.x == 0 && m_vVelocity.y == 0))
		{
			Vector2 vFricDir = -m_vVelocity;
			vFricDir.Normalize();

			Vector2 vFriction = vFricDir * m_fricCoeff * Time::DeltaTime();

			if (vFriction.Length() >= m_vVelocity.Length())
			{
				m_vVelocity = Vector2(0.f, 0.f);
			}
			else
			{
				m_vVelocity += vFriction;

			}
		}

		//중력
		if (m_bGround)
		{
			// 땅위에 있을때
			Vector2 gravity = m_Gravity;
			gravity.Normalize();

			float dot = m_vVelocity.Dot(gravity);
			m_vVelocity -= gravity * dot;
		}
		else
		{
			m_vVelocity += m_Gravity * Time::DeltaTime();
		}


		// 중력가속도 최대 속도 제한
		Vector2 gravity = m_Gravity;
		gravity.Normalize();
		float dot = m_vVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = m_vVelocity - gravity;
		if (m_vMaxVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= m_vMaxVelocity.y;
		}

		if (m_vMaxVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= m_vMaxVelocity.x;
		}


		//속도 제한 검사
		if (abs(m_vMaxVelocity.x < m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
		}

		if (abs(m_vMaxVelocity.y < m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
		}
	
		//속도에 따른 이동
		Move();

		//힘 초기화
		m_vForce = Vector2(0.f, 0.f);

		m_vAccel = Vector2(0.f, 0.f);
		m_vAccelA = Vector2(0.f, 0.f);
		
	}

	void RigidBody::Render()
	{

	}

	void RigidBody::Move()
	{

		float fSpeed = m_vVelocity.Length();
		
		if (fSpeed != 0.f)
		{

			 Transform * tr = GetOwner()->GetComponent<Transform>();
			 Vector2 vPos = tr->GetPostionXY();

			 vPos = vPos + m_vAddPos + m_vVelocity * Time::DeltaTime();
			 tr->SetPositionXY(vPos);

		}

	}

}
