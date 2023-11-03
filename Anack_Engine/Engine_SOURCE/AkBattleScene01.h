#pragma once

#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class BattleScene01 :
		public Scene
	{


	public:
		BattleScene01();
		virtual ~BattleScene01();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:

	};


}