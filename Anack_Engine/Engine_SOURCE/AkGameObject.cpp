#include "AkGameObject.h"
#include "AkRenderer.h"
#include "AkGraphicDevice_Dx11.h"


namespace Ak
{

	GameObject::GameObject()
		: mState(eState::Active)
		, m_bGroundSide(false)
		, m_bhaveCoin(false)
		, m_bGroundTrap(false)
		, m_bPlayerShadow(false)
	{
		mTransform = AddComponent<Transform>();

	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
		
	}

	void GameObject::Initialize()
	{

	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}

	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		
		for (Script* script : mScripts)
		{
			script->Render();

		}
	}

}