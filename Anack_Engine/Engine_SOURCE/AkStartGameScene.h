#pragma once

#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class StartGameScene
		: public Scene
	{

	public:
		StartGameScene();
		virtual ~StartGameScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void HUDInitialize();

	

	private:
		

		bool mbSceneTrigger;
		
	


	};


}