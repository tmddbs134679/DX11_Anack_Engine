#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{
	class EndingBG :
		public GameObject
	{
	public:

		EndingBG();
		virtual ~EndingBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;




	private:
		Animator* mAnimator;

	};

}

