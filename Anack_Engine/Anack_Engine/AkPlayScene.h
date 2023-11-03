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

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

		bool m_bfull;
		float m_zPos;
		GameObject* m_camera;
		
	};

}
