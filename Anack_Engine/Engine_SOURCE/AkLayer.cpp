#include "AkLayer.h"
#include "Akstruct.h"
namespace Ak
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{

	}

	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState()
				!= eState::Active)
				continue;


	 		gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState()
				!= eState::Active)
				continue;

			gameObj->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			//gameObj->LateUpdate();
			gameObj->Render();
		}
	}

	void Layer::Destory()
	{
		// dead ������Ʈ ��Ƶα�
		std::set<GameObject*> deleteGameObj = {};
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState()
				== eState::Dead)
				deleteGameObj.insert(gameObj);
		}

		// daed ������Ʈ ���ܽ�Ű�� layer����
		typedef std::vector<GameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end(); )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteGameObj.find(*(iter));

			if (deleteIter != deleteGameObj.end())
			{
				iter = mGameObjects.erase(iter);
				continue;
			}

			iter++;
		}

		//�޸� ����
		for (GameObject* gameObj : deleteGameObj)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}


	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}

	void Layer::DestoryGameObject(GameObject* gameObj)
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();
		for (iter; iter != mGameObjects.end(); ++iter)
		{
			if (*iter == gameObj)
			{
				mGameObjects.erase(iter);
				return;
			}
		}
	}

	void Layer::DestroyAll() 
	{
		for (GameObject* gameObj : mGameObjects) 
		{
			gameObj->SetState(eState::Dead);
		}
	}


}