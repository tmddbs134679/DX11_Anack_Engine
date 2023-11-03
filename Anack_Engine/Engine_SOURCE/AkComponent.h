#pragma once
#include "AkEntity.h"


namespace Ak
{
	using namespace Ak::enums;
	using namespace Ak::math;

	class GameObject;

	class Component :
		public Entity
	{
	public:

		Component(eComponentType _type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner()
		{
			return mOwner;

		}

		void SetOwner(GameObject* _Owner)
		{
			mOwner = _Owner;
		}

	private:

		const eComponentType mType;
		GameObject* mOwner;
	};


}