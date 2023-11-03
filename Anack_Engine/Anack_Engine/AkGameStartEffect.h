#pragma once
//#include "AkGameObject.h"


namespace Ak
{
	class GameStartEffect :
		public GameObject
	{
	public:

		GameStartEffect();
		virtual ~GameStartEffect();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:



	};


}
