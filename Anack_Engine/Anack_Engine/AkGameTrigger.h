#pragma once
#include "AkGameObject.h"
#include "AkAnimator.h"

namespace Ak
{

	class GameTrigger :
		public GameObject
	{
	public:
		GameTrigger();
		virtual ~GameTrigger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:

	



	private:
		
	};



}