#include "AkAI.h"



namespace Ak
{
	AI::AI()
		: m_pCurState(eMonsterState::Idle)
		, m_pOwner(nullptr)
	{

	}

	AI::~AI()
	{
		std::map<eMonsterState, MonsterState*>::iterator iter = m_mapState.begin();

		for (iter; iter != m_mapState.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}

	void AI::Update()
	{
		m_pActiveState->update();
	}

	void AI::Initialize()
	{
		m_pActiveState->Enter();

	}

	void AI::AddState(MonsterState* _pstate)
	{
		MonsterState* pState = GetState(_pstate->GetType());
		assert(!pState);

		m_mapState.insert(std::make_pair(_pstate->GetType(), _pstate));
		_pstate->m_pAI = this;

	}

	MonsterState* AI::FindState(eMonsterState _eState)
	{
		std::map<eMonsterState, MonsterState*>::iterator iter = m_mapState.find(_eState);

		if (iter != m_mapState.end())
			return iter->second;

		return nullptr;
	}

	void AI::SetCurState(eMonsterState _eState)
	{
		m_pActiveState = GetState(_eState);

		assert(m_pActiveState);
	}

	void AI::ChangeState(eMonsterState _eState)
	{
		MonsterState* pNextState = GetState(_eState);

		assert(pNextState != m_pActiveState); 
		
		m_pActiveState->Exit();
		m_pActiveState = pNextState;
		m_pActiveState->Enter();
	}

	MonsterState* AI::GetState(eMonsterState _eState)
	{
		std::map<eMonsterState, MonsterState*>::iterator iter = m_mapState.find(_eState);
		if (iter == m_mapState.end())
			return nullptr;

		return iter->second;
	}

}

