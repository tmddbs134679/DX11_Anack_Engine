#include "AkGround.h"
#include "AkGroundScript.h"


namespace Ak
{
	Ground::Ground()
	{
		AddComponent<Collider2D>();
		AddComponent<GroundScript>();
	}

	Ground::~Ground()
	{

	}

	void Ground::Initialize()
	{
		
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Ground::Render()
	{
		GameObject::Render();
	}
	
}

