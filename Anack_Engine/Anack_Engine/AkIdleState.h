#pragma once
#include "AkMonsterState.h"

namespace Ak
{
	class IdleState :
		public MonsterState
	{
	public:

		IdleState();
		~IdleState();

	public:
		virtual void update();
		virtual void Enter();
		virtual void Exit();


	public:

		void SetTime(float _time)
		{
			m_fTime = _time;
		}

	

	private:

	

	private:


		float m_fTime;
		float m_fCurTime;
		bool  m_bhit;

	/*	int	  m_iMonsterDirX;
		int   m_iMonsterDirY;*/

		float m_fHunterTime;
		bool  m_bHunterRand;


	};


}