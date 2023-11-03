#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class Radiance_Particle :
		public GameObject
	{

	public:
		Radiance_Particle();
		virtual ~Radiance_Particle();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	};



}