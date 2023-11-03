#pragma once
#include "AkGameObject.h"
#include "AkRenderer.h"

namespace Ak
{
	class Fade :
		public GameObject
	{
	public:

		Fade();
		virtual ~Fade();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void bInFadeOut()
		{
			m_bFadeOut = true;
		}

	

		void bInFadeIn()
		{
			m_bFadein = true;
		}
		

		bool GetFadeOut()
		{
			return m_bFadeOut;
		}

		void bFadeTest()
		{
			m_test = true;
		}
	private:

		renderer::FadeCB FadeCB;

		float c_fcolorz;
		bool  c_bFadein;


		bool  m_bFadeOut;
		bool  m_bFadein;

		float m_fFadeOutTime;


		float m_fFadeTime;
		float m_fWaitTime;


		bool  m_test;
	};



}