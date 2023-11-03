#pragma once
//#include "AkScript.h"
//#include <AkScript.h>
#include "../Engine_SOURCE/AkScript.h"

namespace  Ak
{

	class GridScript :
		public Script
	{
	public:

		GridScript();
		virtual ~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:

		void SetCamera(Camera* camera)
		{
			mCamera = camera;
		}

	private:
		Camera* mCamera;
	};



}