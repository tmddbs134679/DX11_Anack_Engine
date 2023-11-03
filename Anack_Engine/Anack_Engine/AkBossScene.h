#pragma once

#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class BossScene :
		public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};


}