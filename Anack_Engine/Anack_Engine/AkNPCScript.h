#pragma once
#include "AkScript.h"
#include "AkElderbug.h"
#include "AkUI_NPC.h"


namespace Ak
{
	class NPCScript :
		public Script
	{
	public:
		NPCScript();
		~NPCScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other) override;
		virtual	void OnCollision(Collider2D* _other) override;
		virtual	void OnCollisionExit(Collider2D* _other) override;

	public:
		void SetNPC(Elderbug* _edb)
		{
			m_NPC = _edb;
		}


	private:
		Elderbug* m_NPC;
		bool	  m_bUI;

		UI_NPC*	  m_UI_NPC;


	};



}