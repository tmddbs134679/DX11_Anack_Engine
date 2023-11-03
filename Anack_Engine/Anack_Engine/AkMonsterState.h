#pragma once

namespace Ak
{
	class AI;
	class Monster;


	enum class eMonsterState
	{
		Idle,
		Trace,
		Attack,
		AttackStart,
		Skill1,
		Skill2,
		Skill3,
		Skill4,
		Skill5,
		Death,

	};

	
	class MonsterState
	{

		friend class AI;

	public:
		MonsterState(eMonsterState _eState);
		~MonsterState();

	public:
		virtual void update();

		virtual void Enter() = 0;
		virtual void Exit() = 0;


		Monster* GetMonster();


		int RandomDir();

		int RandomPattern();

		int RandomX(int _i);

	
		int RandomY();

	public:

		void SetAI(AI* _AI)
		{
			m_pAI = _AI;
		}

		void SetType(eMonsterState _estate)
		{
			m_monsterState = _estate;
		}
		



	public:

		AI* GetAI()
		{
			return m_pAI;
		}

		eMonsterState GetType()
		{
			return m_monsterState;
		}






	public:



	private:
		AI*				m_pAI;
		
		eMonsterState m_monsterState;

		std::wstring m_wStateName;


	};


}
