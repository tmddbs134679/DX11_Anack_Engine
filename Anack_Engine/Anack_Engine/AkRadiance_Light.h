#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"
//#include "AkRadiance_Trigger.h"
namespace Ak
{
	class Radiance_Light :
		public GameObject
	{

	public:

		Radiance_Light();
		virtual ~Radiance_Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		std::shared_ptr<AudioClip> GetAC()
		{
			return m_ac;
		}
	
	private:

		Animator* mAnimator;

		

		bool m_bAudioOn;
		std::shared_ptr<AudioClip> m_ac;
	};



}