#pragma once

#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class PlayScene :
		public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:

		
	};

}
