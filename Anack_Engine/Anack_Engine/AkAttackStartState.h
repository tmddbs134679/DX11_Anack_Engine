#pragma once
#include "AkMonsterState.h"


namespace Ak
{

	class AttackStartState :
		public MonsterState
	{
	public:

		AttackStartState();
		~AttackStartState();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:

		float mTime;
		bool  bEnter;

		float m_grimmTime;
		bool  m_bGrimmEnter;
		bool  m_bGrimmSecEnter;
		float m_grimmsecTime;


		bool m_bGrimmThiEnter;
		bool m_bGrimmForEnter;
		bool m_bAttackChange;

		bool m_bRadianceCh;

	};



}