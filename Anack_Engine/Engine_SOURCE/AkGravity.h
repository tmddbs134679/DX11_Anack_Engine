#pragma once
#include "AkComponent.h"


namespace Ak
{
	class Gravity :
		public Component
	{

	public:
		Gravity();
		~Gravity();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	private:

		bool		m_bGround;


	};



}