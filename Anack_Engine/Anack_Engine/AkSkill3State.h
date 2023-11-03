#pragma once
#include "AkMonsterState.h"
#include <iostream>>
#include <random>
#include <cmath>

namespace Ak
{
	class Skill3State :
		public MonsterState
	{

	public:

		Skill3State();
		~Skill3State();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;

		float RandomFloat(float min, float max)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(min, max);
			return dis(gen);
		}

		Vector2 RandomDir()
		{
			float angle = RandomFloat(0, 2 * 3.14159); 
			return Vector2(std::cos(angle), std::sin(angle));
		}

	
		
	private:

		bool   m_bSkill[2];
		bool   m_bMakeOBJ[2];
		bool   m_bDis;
		bool   m_bChangeSkill;

		float m_fTime;
		int   m_iCNT;


		bool  m_bRadianceAttack;

		float m_fMoveTime;

		bool m_bPlayerOn;
		bool m_bRadianceSkill03;


	};

}
