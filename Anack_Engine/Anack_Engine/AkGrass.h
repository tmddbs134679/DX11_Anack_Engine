#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Grass :
		public GameObject
	{

	public:

		Grass();
		virtual ~Grass();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:



	};



}