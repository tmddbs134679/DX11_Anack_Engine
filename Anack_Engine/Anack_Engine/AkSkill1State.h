#pragma once
#include "AkMonsterState.h"


namespace Ak
{
	class Skill1State :
		public MonsterState
	{

	public:

		Skill1State();
		~Skill1State();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;

	


	private:

		bool  m_bChangeSkill;
		bool  m_bEndSkill;

		int Attack01Cnt;

		bool m_bRadiacneAttack;


		bool m_bAttack03Change;

		bool m_RP3InIt;


		float m_fMoveTime;
	};



}