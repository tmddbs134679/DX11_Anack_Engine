#include "AkRadiance_Trigger_Script.h"
#include "AkGameObject.h"
#include "AkTime.h"


namespace Ak
{
	Radiance_Trigger_Script::Radiance_Trigger_Script()
		: m_bStart(false)
	{

	}

	Radiance_Trigger_Script::~Radiance_Trigger_Script()
	{

	}

	void Radiance_Trigger_Script::Initialize()
	{
	
	}

	void Radiance_Trigger_Script::Update()
	{
	
	}

	void Radiance_Trigger_Script::LateUpdate()
	{

	}

	void Radiance_Trigger_Script::Render()
	{

	}

	void Radiance_Trigger_Script::OnCollisionEnter(Collider2D* _other)
	{
		GameObject* pGameObj = _other->GetOwner();

		if (pGameObj->GetLayerType() == eLayerType::Player)
		{
			m_bStart = true;

		}
	}

	void Radiance_Trigger_Script::OnCollision(Collider2D* _other)
	{

	}

	void Radiance_Trigger_Script::OnCollisionExit(Collider2D* _other)
	{

	}

}