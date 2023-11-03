#pragma once
#include "AkScript.h"
#include "AkRadiance_Trigger.h"

namespace Ak
{
	class Radiance_Trigger_Script :
		public Script
	{
	public:

		Radiance_Trigger_Script();
		~Radiance_Trigger_Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other);
		virtual	void OnCollision(Collider2D* _other);
		virtual	void OnCollisionExit(Collider2D* _other);

		bool GetStart()
		{
			return m_bStart;
		}


		void OffStart()
		{
			m_bStart = false;
		}
	private:

		bool  m_bStart;

		Radiance_Trigger* m_Owner;


	};


}
