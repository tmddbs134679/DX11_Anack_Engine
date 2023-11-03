#pragma once
#include "AkMonsterState.h"
#include "AkGrimm_Projectile_03.h"

namespace Ak
{
	class Skill2State :
		public MonsterState
	{

	public:

		Skill2State();
		~Skill2State();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;


	private:

		bool m_bSkill2;
		bool m_bCreateSkillObj01;
		bool m_bCreateSkillObj02;
		bool m_bDestorySkillObj;

		bool m_bDissapear;
		bool m_bChangeSkill;

		bool m_bRadianceSkill2Start;

		float m_fMoveTime;


		bool m_bRadiance1;
		bool m_bRadiance2;
		bool m_bRadiance3;
		bool m_bRadiance4;


		std::vector<Grimm_Projectile_03*> m_vSkillObj;
	};


}