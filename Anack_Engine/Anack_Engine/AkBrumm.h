#pragma once
#include "AkGameObject.h"

namespace Ak 
{

	class Brumm :
		public GameObject
	{
	public:
		Brumm();
		virtual ~Brumm();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();



	};



}