#pragma once
#include "AkScript.h"
#include "AkMonster.h"
namespace Ak
{

	class BossTriggerScript :
		public Script
	{
	public:
		BossTriggerScript();
		~BossTriggerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other);
		virtual	void OnCollision(Collider2D* _other);
		virtual	void OnCollisionExit(Collider2D* _other);

	public:

		bool GetTriggerState()
		{
			return m_bTriggerOn;
		}



		
	private:
		
		bool	m_bTriggerOn;
		bool    m_bTriggerDestory;


	};



	
}