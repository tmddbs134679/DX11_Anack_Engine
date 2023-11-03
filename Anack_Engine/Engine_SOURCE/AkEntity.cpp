#include "AkEntity.h"



namespace Ak
{
	Ak::Entity::Entity()
		: mName(L"")
		,mColliderID((UINT64)this)
	{
	}

	Ak::Entity::~Entity()
	{
	}

}