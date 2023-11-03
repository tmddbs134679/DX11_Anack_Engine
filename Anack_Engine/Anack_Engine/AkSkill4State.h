#pragma once
#include "AkMonsterState.h"

namespace Ak
{
	class Skill4State :
		public MonsterState
	{


	public:

		Skill4State();
		~Skill4State();

	public:

		virtual void update() override;
		virtual void Enter() override;
		virtual void Exit() override;



	private:
		bool m_bSkill04_01;

		bool  m_bSkill04_02;
		bool  m_bSkill04_03;
		bool  m_bSkill04Ch;
		bool  m_bSkillDis;
		bool m_bReskill04_02;

	

		Vector2 m_vTest;

	};



}