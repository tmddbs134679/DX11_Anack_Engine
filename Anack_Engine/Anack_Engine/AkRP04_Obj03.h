#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Projectile_04.h"
#include "AkMonster.h"


namespace Ak
{
	class RP04_Obj03 :
		public GameObject
	{

	public:

		RP04_Obj03();
		~RP04_Obj03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		float Random();

		void SetOwner(Monster* _mon)
		{
			m_Owner = _mon;
		}

		void SetPlayer(Player* _player)
		{
			m_Player = _player;
		}

		void AttackOff()
		{
			m_bAttack = false;
		}

	private:

		Radiance_Projectile_04* m_RP;

		Monster* m_Owner;

		Player* m_Player;


		bool m_bChRot;

		bool m_bAttack;

		

	};

}
