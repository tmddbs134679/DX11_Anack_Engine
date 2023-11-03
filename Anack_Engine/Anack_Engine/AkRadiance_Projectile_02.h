#pragma once
#include "AkGameObject.h"
#include "AkAudioClip.h"

namespace Ak
{
	class Radiance_Projectile_02 :
		public GameObject
	{
	public:

		Radiance_Projectile_02();
		virtual ~Radiance_Projectile_02();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


		std::shared_ptr<AudioClip> GetAc()
		{
			return m_ac;
		}

	private:

		
		std::shared_ptr<AudioClip> m_ac;
	};



}