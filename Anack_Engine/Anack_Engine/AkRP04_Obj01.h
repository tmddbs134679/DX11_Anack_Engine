#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Projectile_04.h"

namespace Ak
{
	class RP04_Obj01 :
		public GameObject
	{
	public:
	
		RP04_Obj01();
		~RP04_Obj01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void AttackOn()
		{
			m_bAttack = true;
		}

		bool GetAttack()
		{
			return m_bAttack;
		}

	private:

		std::vector<Radiance_Projectile_04*> m_vRP;

		bool m_bAttack;

		 float fmove;

	};


}