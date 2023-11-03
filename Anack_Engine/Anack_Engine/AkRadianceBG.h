#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{
	class RadianceBG :
		public GameObject
	{
	public:

		RadianceBG();
		virtual ~RadianceBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	private:
		Animator* mAnimator;

	};



}