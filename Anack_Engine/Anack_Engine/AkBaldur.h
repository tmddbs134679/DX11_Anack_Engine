#pragma once
#include "AkMonster.h"


namespace Ak
{
	class Baldur :
		public Monster
	{
	public:

		Baldur();
		virtual ~Baldur();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:



	private:

		
	};

}