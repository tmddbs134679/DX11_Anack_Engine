#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"
#include "AkAudioClip.h"


namespace Ak
{
	class Radiance_Projectile_04 :
		public GameObject
	{
	public:

		Radiance_Projectile_04();
		virtual ~Radiance_Projectile_04();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		std::vector<std::shared_ptr<AudioClip>> GetAC()
		{
			return m_AudioClips;
		}

		Collider2D* GetCD()
		{
			return mcd;
		}
		
	private:
		Animator* mAnimator;
		Collider2D* mcd;


		bool m_bCollider;

		std::vector<std::shared_ptr<AudioClip>> m_AudioClips;
		
		bool  m_bACPre;
		bool  m_bACBeam;


	};



}