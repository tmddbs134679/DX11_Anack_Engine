#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Light.h"
#include "AkRadiance.h"

namespace Ak
{
	class Radiance_Trigger :
		public GameObject
	{
	public:

		Radiance_Trigger();
		virtual ~Radiance_Trigger();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();



		void SetRadianceLight(Radiance_Light* _obj)
		{
			m_Radiance_Light = _obj;

		}

		void SetRadiance(Radiance* _obj)
		{
			m_Radiance = _obj;

		}

		void SetPlayer(Player* _player)
		{
			m_Player = _player;
		}

		Radiance_Light* GetRadianceLight()
		{
			return m_Radiance_Light;
		}

	private:

		Radiance_Light* m_Radiance_Light;

		Radiance* m_Radiance;


		bool m_bRadianceAttackStart;

		Player* m_Player;

		
		bool  m_bDestory;

		
	};



}