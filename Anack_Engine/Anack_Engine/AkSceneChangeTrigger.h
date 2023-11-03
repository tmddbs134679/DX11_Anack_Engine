#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class SceneChangeTrigger :
		public GameObject
	{
	public:


		SceneChangeTrigger();
		virtual ~SceneChangeTrigger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;





	};


}