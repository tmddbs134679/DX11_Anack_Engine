#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Projectile_04.h"
#include "AkMonster.h"

namespace Ak
{
	class RP04_Obj02 :
		public GameObject
	{
	public:

		RP04_Obj02();
		~RP04_Obj02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void SetOwner(Monster* _mon)
		{
			m_Owner = _mon;
		}



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

		Monster* m_Owner;

		bool m_bAttack;

		int m_iAttackCnt;

		bool	m_bACPre0;
		bool	m_bACBeam0;

		bool	m_bACPre1;
		bool	m_bACBeam1;
		bool    m_bSound;


		float fTime;

	};



}