#include "AkLight.h"
#include "AkRenderer.h"
#include "AkTransform.h"
#include "AkGameObject.h"
#include "../Anack_Engine/AkSceneChangeScript.h"

namespace Ak
{
	Light::Light()
		: Component(eComponentType::Light)
	{

	}

	Light::~Light()
	{
		
	}

	void Light::Initialize()
	{

	}

	void Light::Update()
	{

	}

	void Light::LateUpdate()
	{
		renderer::lights.push_back(this);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.f);
		mAttribute.direction = Vector4(tr->Forword().x, tr->Forword().y, tr->Forword().z, 1.f);
	}

	void Light::Render()
	{

	}

}
