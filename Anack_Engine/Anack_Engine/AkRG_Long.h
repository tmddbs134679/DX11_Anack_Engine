#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{
	class RG_Long :
		public GameObject
	{

	public:

		RG_Long();
		virtual ~RG_Long();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	private:
		Animator* mAnimator;


	};



}