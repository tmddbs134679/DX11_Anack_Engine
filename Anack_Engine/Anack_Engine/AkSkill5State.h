#pragma once
#include "AkMonsterState.h"


namespace Ak
{
	class Skill5State :
		public MonsterState
	{
	public:

		Skill5State();
		~Skill5State();

	public:

		virtual void update() override;
		virtual void Enter() override;
		virtual void Exit() override;




	private:

		bool m_bSkill[3];
	};



}