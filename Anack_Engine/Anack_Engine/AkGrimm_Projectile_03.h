#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Grimm_Projectile_03 :
		public GameObject
	{
	public:

		Grimm_Projectile_03();
		virtual ~Grimm_Projectile_03();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	private:

		Collider2D* m_cd;
		Animator* mAnimator;


		float m_fMaxCdSize01Y;
		float m_fMaxCdSize02Y;

		bool m_bDestory;
		float fPreSizeY;
	};



}