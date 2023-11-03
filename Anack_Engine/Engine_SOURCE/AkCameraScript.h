#pragma once
#include "AkScript.h"
#include "../Anack_Engine/AkPlayer.h"
#include "AkCamera.h"

namespace Ak
{
	class CameraScript :
		public Script
	{
	public:
		virtual void Update() override;



		void SetPlayer(Player* _obj)
		{
			m_pPlayer = _obj;
		}

		void PlayBattleAnim()
		{
			m_bBattleAnim = true;
		}

		void PlayShakeCamera()
		{
			m_bShakeCamera = true;
		}
		Player* GetPlayer()
		{
			return m_pPlayer;
		}

		void SetBackGround(GameObject* _obj)
		{
			m_BackGround = _obj;
		}

		void BossDeadCamera()
		{
			m_bBossDeadCamera = true;

		}

		void BossDeadOff()
		{
			m_bBossDeadCamera = false;
		}
	public:

	

	private:

		Player*		m_pPlayer;
		GameObject* m_BackGround;


		//float		m_fShakeDuration;
		//float		m_fShakeMagnitude;
		float		m_fShakeTime;

		bool		m_bShakeCamera = false;
		bool        m_bBossDeadCamera = false;


		float		m_fBattleAnimTime;

		bool		m_bBattleAnim = false;

	};


}