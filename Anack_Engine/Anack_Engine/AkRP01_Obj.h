#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Proejctile_01.h"
#include "AkMonster.h"
#include "AkPlayer.h"


namespace Ak
{
	class RP01_Obj :
		public GameObject
	{

	public:
		enum RP03Pattern
		{
			pattern01 = 1,
			pattern02,
			pattern03,
			pattern04,
		};

		RP01_Obj();
		~RP01_Obj();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Vector2 RP01_CalculateDirection(float _angle);

		void Suffle();



		void SetOwner(Monster* _mon)
		{
			m_Owner = _mon;
		}

		void SetPlayer(Player* _player)
		{
			m_Player = _player;
		}

		bool GetPatternEnd()
		{
			return m_bParrernEnd;
		}

		void ChangePattern()
		{
			Suffle();
			AttackCNT = 0;
			m_bParrernEnd = false;
			m_fPatternEndTime = 0.f;
			
			if (ipattern == 4)
			{
				ipattern = 1;
			}
			
			m_EPattern = static_cast<RP03Pattern>(ipattern);

			ipattern++;
		}

		int GetPatternI()
		{
			return ipattern;
		}

		void PatternOff()
		{
			m_bParrernEnd = false;
		}

		int GetAttackCnt()
		{
			return AttackCNT;
		}

		void AttackOn()
		{
			m_bAttack = true;
		}

		bool GetAttack()
		{
			return m_bAttack;
		}

	private:
		std::vector<Radiance_Proejctile_01*> m_vRP;

		RP03Pattern m_EPattern;

		Monster* m_Owner;


		float m_fTime03;

		Player* m_Player;

		float radius;

		float angleStep;

		float angle;
		float radians;

		float x;
		float y;

		int AttackCNT;

		float m_fPattern01;
		float m_fPattern02;
		float m_fPattern03;

		float m_fPatternEndTime;

		bool m_bParrernEnd;

		int ipattern = 2;

		std::vector<int> m_vRandoms;
		

		bool m_bAttack;

 
	};


}