#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Flame :
		public GameObject
	{


	public:

		Flame();
		virtual ~Flame();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};


}