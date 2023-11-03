#pragma once
#include "AkMonster.h"
#include "AkAnimator.h"
#include "AkRadiance_Particle.h"


namespace Ak
{
	class Radiance :
		public Monster
	{
	public:

		Radiance();
		virtual ~Radiance();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	
		AI* GetAI()
		{
			return pRadianceAI;
		}




	private:
		Animator* mAnimator;
		GameObject* m_Radiance_partcile;
		AI* pRadianceAI;


		bool m_bDisAnim;

	};



}