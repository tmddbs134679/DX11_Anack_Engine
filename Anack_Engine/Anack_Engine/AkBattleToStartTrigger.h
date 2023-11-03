#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class BattleToStartTrigger :
		public GameObject
	{
	public:


		BattleToStartTrigger();
		virtual ~BattleToStartTrigger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};

}