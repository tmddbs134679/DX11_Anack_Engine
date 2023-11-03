#include "AkBossTriggerScript.h"
#include "AkTime.h"
#include "AkSceneManager.h"

namespace Ak
{
	BossTriggerScript::BossTriggerScript()
		: m_bTriggerOn(false)
	{

	}

	BossTriggerScript::~BossTriggerScript()
	{
	
	}

	void BossTriggerScript::Initialize()
	{

	}

	void BossTriggerScript::Update()
	{
		
	}

	void BossTriggerScript::LateUpdate()
	{
	
	}

	void BossTriggerScript::Render()
	{

	}

	void BossTriggerScript::OnCollisionEnter(Collider2D* _other)
	{
		m_bTriggerOn = true;


		
	}

	void BossTriggerScript::OnCollision(Collider2D* _other)
	{


	}
	void BossTriggerScript::OnCollisionExit(Collider2D* _other)
	{

	}

}