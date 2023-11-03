#pragma once
#include "AkMonsterState.h"

namespace Ak
{
	class TraceState :
		public MonsterState
	{
	public:
		TraceState();
		~TraceState();

	public:
		virtual void update() override;

		virtual void Enter() override;
		virtual void Exit() override;


	private:

		float m_fTraceSound;

	};



}
