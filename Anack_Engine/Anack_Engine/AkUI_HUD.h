#pragma once
//#include "AkGameObject.h"
//#include "AkHealth.h"
#include "AkHP_Ball.h"

namespace Ak
{
	class UI_HUD :
		public GameObject
	{
	public:
		UI_HUD();
		virtual ~UI_HUD();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	public:


		std::vector<Health*> GetHUDObj()
		{
			return m_objHUDCount;
		}

		GameObject* GetHudMain()
		{
			return m_HUD;
		}

		GameObject* GetHudCoin()
		{
			return m_HUD_Coin;
		}

		HP_Ball* GetHP_Ball()
		{
			return m_HPBall;
		}

		int GetHealthCNT()
		{
			return m_iHealthCNT;
		}

		void SetHealthCnt(int _i)
		{
			m_iHealthCNT = _i;
		}

	public:

		void DisHealthCNT()
		{
			--m_iHealthCNT;
		}

		void IncreHealthCNT()
		{
			++m_iHealthCNT;
		}

	private:

		GameObject* m_HUD;
		GameObject* m_HUD_Coin;
		std::vector<Health*> m_objHUDCount;

		HP_Ball*	m_HPBall;


		bool m_bUI = true;

		int m_iHealthCNT;

	};

}
