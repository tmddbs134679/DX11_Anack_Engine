#include "AkMonsterState.h"
#include "AkMonster.h"
#include "AkAI.h"
#include <random>
#include "AkCameraScript.h"

namespace Ak
{
	MonsterState::MonsterState(eMonsterState _eState)
		: m_monsterState(_eState)
	{
	
	}
	MonsterState::~MonsterState()
	{

	}
	void MonsterState::update()
	{
		Monster* pMonster = GetAI()->GetOwner();

		if (pMonster->GetName() == L"Grimm")
		{
			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				GetAI()->ChangeState(eMonsterState::Death);
				pMonster->GetSceneCamera()->GetComponent<CameraScript>()->BossDeadCamera();
			}
		}

		if (pMonster->GetName() == L"Baldur")
		{
			if (pMonster->GetMonsterInfo().iHP_Count <= 0)
			{
				GetAI()->ChangeState(eMonsterState::Death);
			}
		}

	}


	Monster* MonsterState::GetMonster()
	{
		return m_pAI->GetOwner();
	
	}


	int MonsterState::RandomDir()
	{
		std::random_device  rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> distribution(-1, 1);
		int randomNumber = distribution(gen);

		return randomNumber;

	}

	int MonsterState::RandomPattern()
	{
		std::random_device  rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> distribution(1, 3);
		int randomNumber = distribution(gen);

		return randomNumber;
	}


	int MonsterState::RandomX(int _i)
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		// 0, 1, 2 중 하나를 랜덤으로 선택
		int randomNumber = 0;
		int selectedValue;

		if (_i == 1)
		{
			int randomNumber = std::rand() % 3;

			if (randomNumber == 0)
			{
				selectedValue = -8;
			}
			else if (randomNumber == 1)
			{
				selectedValue = 0;
			}
			else
			{
				selectedValue = 8;
			}
		}
		else if(_i == 2)
		{
			int randomNumber = std::rand() % 5;

			if (randomNumber == 0)
			{
				selectedValue = -9;
			}
			else if (randomNumber == 1)
			{
				selectedValue = 9;
			}
			else if (randomNumber == 2)
			{

				selectedValue = 0;

			}
			else if (randomNumber == 3)
			{
				selectedValue = -15;
			}
			else
			{
				selectedValue = 15;
			}
		}
		else
		{
			int randomNumber = std::rand() % 3;

			if (randomNumber == 0)
			{
				selectedValue = -8;
			}
			else if (randomNumber == 1)
			{
				selectedValue = 0;
			}
			else
			{
				selectedValue = 8;
			}

		}
		

			return selectedValue;
	}



	int MonsterState::RandomY()
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		
		int randomNumber = std::rand() % 3;

		int selectedValue;
		if (randomNumber == 0) {
			selectedValue = 6.8;
		}
		else if (randomNumber == 1) {
			selectedValue = 7.8;
		}
		else {
			selectedValue = 9.8;
		}

		return selectedValue;
	}

}