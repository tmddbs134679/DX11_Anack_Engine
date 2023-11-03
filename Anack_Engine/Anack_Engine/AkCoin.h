#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Coin :
		public GameObject
	{
	public:

		Coin();
		virtual ~Coin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	};


}