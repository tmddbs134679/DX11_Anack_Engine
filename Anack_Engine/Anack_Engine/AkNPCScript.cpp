#include "AkNPCScript.h"
#include "AkAnimator.h"
#include "AkInput.h"
#include "AkSceneManager.h"
#include "AkFontWrapper.h"

namespace Ak
{
	NPCScript::NPCScript()
		: m_NPC(nullptr)
		, m_bUI(true)
		, m_UI_NPC(nullptr)
	{
	}

	NPCScript::~NPCScript()
	{
	}

	void NPCScript::Initialize()
	{
	}

	void NPCScript::Update()
	{
	}

	void NPCScript::LateUpdate()
	{
	}

	void NPCScript::Render()
	{

	}
	void NPCScript::OnCollisionEnter(Collider2D* _other)
	{
		Vector3 NpcPos =  m_NPC->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerPos = _other->GetPosition();

		int Dir = NpcPos.x - PlayerPos.x > 0 ? 1 : -1;

		if (Dir == 1)
		{
			m_NPC->GetComponent<Animator>()->PlayAnimation(L"Elderbug_idle_l", true);
		}

	}
	void NPCScript::OnCollision(Collider2D* _other)
	{
		Vector3 NpcPos = m_NPC->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerPos = _other->GetPosition();

		int Dir = NpcPos.x - PlayerPos.x > 0 ? 1 : -1;

		if (Dir == 1)
		{
			m_NPC->GetComponent<Animator>()->PlayAnimation(L"Elderbug_idle_l", true);
		}
		else
		{
			m_NPC->GetComponent<Animator>()->PlayAnimation(L"Elderbug_idle_r", true);
		}


		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (m_bUI)
			{
				UI_NPC* pUI_NPC = new UI_NPC();
				pUI_NPC->Initialize();
				m_bUI = false;
				m_UI_NPC = pUI_NPC;
				m_NPC->GetComponent<AudioSource>()->SetClip(m_NPC->GetAC()[0]);
				m_NPC->GetComponent<AudioSource>()->Play();

			}
			else
			{
				delete m_UI_NPC;
				m_bUI = true;
			}
			
		}
	}


	void NPCScript::OnCollisionExit(Collider2D* _other)
	{
		m_NPC->GetComponent<Animator>()->PlayAnimation(L"Elderbug_idle_r", true);
	}

}