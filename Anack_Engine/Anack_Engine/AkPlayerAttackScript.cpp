#include "AkPlayerAttackScript.h"
#include "AkGameObject.h"
#include "AkRigidBody.h"
#include "AkSceneManager.h"

namespace Ak
{
	PlayerAttackScript::PlayerAttackScript()
	{

	}

	PlayerAttackScript::~PlayerAttackScript()
	{

	}

	void PlayerAttackScript::Initialize()
	{

	}

	void PlayerAttackScript::Update()
	{

	}

	void PlayerAttackScript::LateUpdate()
	{

	}

	void PlayerAttackScript::Render()
	{

	}

	void PlayerAttackScript::OnCollisionEnter(Collider2D* _other)
	{

		GameObject* OtherObj = _other->GetOwner();

		GameObject* gPlayer = m_pPlayerWeapon->GetPlayer();
		
		gPlayer->GetComponent<Transform>()->GetPosition();

		if (OtherObj->GetLayerType() == eLayerType::Monster)
		{
			m_HUD->GetHP_Ball()->IncreLifeSoul();
			SceneManager::SetBall(m_HUD->GetHP_Ball()->GetLifeCnt());

		}

	

	}

	void PlayerAttackScript::OnCollision(Collider2D* _other)
	{

	}

	void PlayerAttackScript::OnCollisionExit(Collider2D* _other)
	{
	/*	GameObject* gPlayer = m_pPlayerWeapon->GetPlayer();

		gPlayer->GetComponent<RigidBody>()->SetVelocity(Vector2::Zero);*/
	}
}