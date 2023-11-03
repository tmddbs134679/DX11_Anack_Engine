#pragma once
#include "AkMonsterState.h"
#include "AkMonster.h"


class MonsterState;


namespace Ak
{
	class MonsterState;

	class AI
	{
		
	public:

		AI();
		~AI();

		friend class Monster;
	public:


		void Update();
		void Initialize();

		void AddState(MonsterState* _pstate);

		MonsterState* FindState(eMonsterState	_eState);
		void SetCurState(eMonsterState _eState);
		void ChangeState(eMonsterState _eState);
		
		MonsterState* GetState(eMonsterState _eState);

	public:

		void SetOwner(Monster* _Owner)
		{
			m_pOwner = _Owner;
		}

	
	public:

		Monster* GetOwner()
		{
			return m_pOwner;
		}

		MonsterState* GetActiveState()
		{
			return m_pActiveState;
		}

	
		
	private:

		Monster* m_pOwner;

		std::map<eMonsterState, MonsterState*>	m_mapState;

		eMonsterState m_pCurState;

		MonsterState* m_pActiveState;



	};




}