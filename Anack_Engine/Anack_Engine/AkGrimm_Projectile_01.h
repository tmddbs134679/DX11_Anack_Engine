#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{
	class Grimm_Projectile_01 :
		public GameObject
	{
	public:

		Grimm_Projectile_01();
		virtual ~Grimm_Projectile_01();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:

		void ChoosesAnim(int _dir);
	public:
		int GetDir()
		{
			return m_iDir;
		}

	public:

		void SetDir(int _dir)
		{
			m_iDir = _dir;
		}


	private:
		Animator* mAnimator;
		int m_iDir;
		float fTime;
	};



}