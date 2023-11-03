#pragma once
#include "AkGameObject.h"
#include "AkAudioClip.h"


namespace Ak
{
	class Radiance_Proejctile_01 :
		public GameObject
	{
	public:

		Radiance_Proejctile_01();
		virtual ~Radiance_Proejctile_01();

		std::shared_ptr<AudioClip> GetAc()
		{
			return m_ac;
		}

	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();



		std::shared_ptr<AudioClip> m_ac;


	};



}