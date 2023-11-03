#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();


		void DestroyAll();

		void AddGameObject(GameObject* gameObj);
		
		void DestoryGameObject(GameObject* gameObj);


		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}


	private:
		std::vector<GameObject*> mGameObjects;
	};
	
}
