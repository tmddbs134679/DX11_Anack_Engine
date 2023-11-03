#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Trap :
		public GameObject
	{

	public:

		Trap();
		virtual ~Trap();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	};



}