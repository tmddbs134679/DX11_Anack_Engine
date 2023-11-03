#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"


namespace Ak
{
	class Radiance_Projectile_03 :
		public GameObject
	{

	public:

		Radiance_Projectile_03();
		virtual ~Radiance_Projectile_03();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:

		GameObject* GetParticle()
		{
			return m_particle;
		}

		void AttackOn()
		{
			m_bAttack = true;
		}

		void Replayoff()
		{
			m_bReplay = false;
		}

		bool Replay()
		{
			return m_bReplay;
		}

		bool Test()
		{
			return m_bAttack2;
		}

		bool Dis()
		{
			return m_bdis;
		}

		void DisOff()
		{
			m_bdis = false;
		}

	private:
		Animator*  mAnimator;

		GameObject* m_particle;

	


		float m_fTime;


		bool m_bAttack;
		bool m_bAttack2;


		bool m_bReplay;
		bool m_bdis;

	

	};



}