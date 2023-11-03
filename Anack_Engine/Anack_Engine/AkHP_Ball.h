#pragma once
//#include "AkGameObject.h"
//#include "AkAnimator.h"

namespace Ak
{
	class HP_Ball :
		public GameObject
	{
	public:
		

		HP_Ball();
		virtual ~HP_Ball();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:

		void SetLifeCnt(int _i)
		{
			m_iLifeSoul = _i;
		}
		
		int GetLifeCnt()
		{
			return m_iLifeSoul;
		}

		void DisLifeSoul()
		{
			if (m_iLifeSoul >= 3)
			{
				m_iLifeSoul -= 3;
				m_bLifeIncre = true;
			}
			else
			{
				//m_iLifeSoul = 0;
				m_bLifeIncre = false;
			}
				
		}

		void IncreLifeSoul()
		{
			if (m_iLifeSoul >= 10)
				m_iLifeSoul = 10;
			else
			++m_iLifeSoul;
		}

		
		bool CheckBoolLife()
		{
			return m_bLifeIncre;
		}

	private:

		bool		 m_bUI;

		int			 m_iLifeSoul;
		Animator*    m_Animator;

		bool		 m_bLifeIncre;


	};



}