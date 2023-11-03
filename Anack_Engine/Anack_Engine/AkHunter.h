#pragma once
#include "AkMonster.h"


namespace Ak
{
	class Hunter :
		public Monster
	{
	public:

		Hunter();
		virtual ~Hunter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:

		AI* pHunterAI;
	
	};



}