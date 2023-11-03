#pragma once
#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class AbyssScene :
		public Scene
	{
	public:
		AbyssScene();
		virtual ~AbyssScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};



}