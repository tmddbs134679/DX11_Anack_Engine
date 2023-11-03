#pragma once
#include "AkMonsterState.h"


namespace Ak
{

	class DeadState :
		public MonsterState
	{

	public:

		DeadState();
		~DeadState();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;


	private:

		float	m_fTime;
		float   m_fRadianceTime;


		bool    m_bDestoryMonster;

		bool	m_bGrimmVoice;


		bool	m_bDestoryRadiance;

		bool    m_bRadianceDeadSound;

		float    m_fRadianceExit;



	};




}