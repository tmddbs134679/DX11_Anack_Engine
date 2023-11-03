#pragma once
#include "AkScript.h"
#include "AkMonster.h"
#include "AkAI.h"
#include "Info.h"

namespace Ak
{
	class MonsterScript :
		public Script
	{

	public:
		MonsterScript();
		~MonsterScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other) override;
		virtual	void OnCollision(Collider2D* _other) override;
		virtual	void OnCollisionExit(Collider2D* _other) override;

	public:

		void SetAI(AI* _ai)
		{
			m_pAI = _ai;
		}

		void SetCollisionGround()
		{
			m_bCollisionGround = false;
		}

		bool bCollisionGround()
		{
			return m_bCollisionGround;
		}
	private:

		Monster* m_Monster;
		AI* m_pAI;


		AI* m_AIDestory;


		float	m_fKnockBackTime;

		int	Knock_Back_Dir_X;
		int	Knock_Back_Dir_Y;

		bool m_bKnockBackEnter;
		bool m_bDestoryMonster;

		float  m_fTimeDestory;
		
		bool m_bCollisionGround;


	};
}