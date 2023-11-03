#pragma once
#include "AkMonster.h"
#include "AkAnimator.h"

namespace Ak
{
	class Grimm :
		public Monster
	{
	public:

		Grimm();
		virtual ~Grimm();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void Render() override;


	private:
		Animator* mAnimator;

		Vector2 vPreCdSide;
	};



}