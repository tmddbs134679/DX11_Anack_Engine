#pragma once
#include "..\Engine_SOURCE\AkScene.h"

namespace Ak
{
	class RadianceScene :
		public Scene
	{
	public:
		RadianceScene();
		virtual ~RadianceScene();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	};



}