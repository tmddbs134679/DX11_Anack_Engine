#pragma once
#include "AkMonsterState.h"
#include "AkGrimm_Projectile_01.h"

namespace Ak
{

	class AttackState :
		public MonsterState
	{

	public:

		AttackState();
		~AttackState();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:


		Vector2 m_PreColliderSize;

		
	};
}