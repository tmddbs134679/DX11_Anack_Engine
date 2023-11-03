#pragma once

#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class MenuScene :
		public Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:

	};


}