#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class BossToStartTrigger :
		public GameObject
	{

	public:


		BossToStartTrigger();
		virtual ~BossToStartTrigger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};



}