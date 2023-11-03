#include "AkGroundScript.h"
#include "AkGameObject.h"
#include "AkTransform.h"
#include "AkPlayer.h"
#include "AkPlayerScript.h"
#include "AkRigidBody.h"

namespace Ak
{

	GroundScript::GroundScript()
	{

	}

	GroundScript::~GroundScript()
	{

	}

	void GroundScript::Initialize()
	{

	}

	void GroundScript::Update()
	{

	}

	void GroundScript::LateUpdate()
	{

	}

	void GroundScript::Render()
	{

	}

	void GroundScript::OnCollisionEnter(Collider2D* other)
	{

		
	}

	void GroundScript::OnCollision(Collider2D* other)
	{

		GetOwner()->GroundSideOff();

		GameObject* pGameObj = other->GetOwner();

		if (pGameObj->GetLayerType() == eLayerType::Player || pGameObj->GetLayerType() == eLayerType::Monster)
		{


			Collider2D* pGroundCollider = GetOwner()->GetComponent<Collider2D>();
			Collider2D* pOtherCollider = pGameObj->GetComponent<Collider2D>();


			Vector3 vPos = pGroundCollider->GetPosition();
			Vector2 vSize = pGroundCollider->GetSize();
			Vector3 vScale = GetOwner()->GetComponent<Transform>()->GetScale();



			Vector3 vObjPos = pOtherCollider->GetPosition();
			Vector2 vObjSize = pOtherCollider->GetSize();
			Vector3 vObjScale = pGameObj->GetComponent<Transform>()->GetScale();

			float storeObjPosY = vObjPos.y;

			float fDiffy = (vPos.y - vObjPos.y);
			float value_y = fabs(fDiffy) - (vSize.y * vScale.y + vObjSize.y * vObjScale.y) / 2.f;

			if (vObjPos.y < vPos.y)
			{
				//위쪽
				vObjPos.y += value_y;
			}
			else
			{
				//아래쪽
				vObjPos.y -= value_y;
			}
		

			//수평
			float fHorizontalLen = abs(vObjPos.x - vPos.x);

			float fHorizontalThreshold = vObjScale.x / 2.f + vScale.x / 2.f;


			//x축에 충돌 시 y는 기본 y축으로 설정

			if (vObjPos.x - 0.1f >= vPos.x + vScale.x / 2)
			{
				
				vObjPos.x += 0.05f;
				vObjPos.y = storeObjPosY;
				GetOwner()->GroundSideOn();
			}
			
			

			if (vObjPos.x + 0.1f <= vPos.x - vScale.x / 2)
			{
				vObjPos.x -= 0.05;
				vObjPos.y = storeObjPosY;
				GetOwner()->GroundSideOn();
			}
	

			pGameObj->GetComponent<Transform>()->SetPosition(vObjPos);

		}
	}

	void GroundScript::OnCollisionExit(Collider2D* other)
	{
		int a = 0;
	}
}

