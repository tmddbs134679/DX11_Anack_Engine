#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{
	class RG_Short :
		public GameObject
	{
	public:

		RG_Short();
		virtual ~RG_Short();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	private:
		Animator* mAnimator;



	};



}