#pragma once
//#include "AkGameObject.h"


namespace Ak
{
	class Health :
		public GameObject
	{
	public:

		Health();
		virtual ~Health();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	private:

		bool m_bUI;
		Animator* mAnimator;
	};



}