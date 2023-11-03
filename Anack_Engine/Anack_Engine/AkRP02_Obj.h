#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Projectile_02.h"
#include "AkMonster.h"


namespace Ak
{
	class RP02_Obj :
		public GameObject
	{
	public:

		RP02_Obj();
		~RP02_Obj();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:

		void SetOwner(Monster* _mon)
		{
			m_Owner = _mon;
		}

		void SetPlayer(Player* _player)
		{
			m_Player = _player;
		}

		void AttackOn()
		{
			m_bAttack = true;
			m_bAttackSetting = true;
		}

		bool GetAttackOn()
		{
			return m_bAttack;
		}

		void AttackOff()
		{
			m_bAttack = false;
		}

	private:

		Monster* m_Owner;

		Player* m_Player;


		std::vector<Radiance_Projectile_02*> m_vRP;

		bool m_bAttack;

		float m_fTime;

		bool m_bAttackSetting;

		bool m_bAC;

	};



}