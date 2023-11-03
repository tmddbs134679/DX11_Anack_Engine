#pragma once
#include "AkEntity.h"
#include "AkGameObject.h"
#include "AkLayer.h"
//#include "../Anack_Engine/AkUI_HUD.h"
#include "../Anack_Engine/AkFade.h"
#include "AkAudioSource.h"
#include "../Anack_Engine/AkBrumm.h"


namespace Ak
{
	

	class Scene :
		public Entity
	{
	public:

		

		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(eLayerType type, GameObject* gameObj);


		void DestroyAll();

	public:

		void SetSceneLightObj(GameObject* _obj)
		{
			mSceneLightObj = _obj;
		}

		void SetMainCamera(Camera* _camera)
		{
			mMainCamera = _camera;
		}

		void RegisterPlayer(GameObject* _player)
		{
			mPlayer = _player;
		}

		void SetSceneAudio(AudioSource* _as)
		{
			m_SceneAS = _as;
		}

		void SetCameraObj(GameObject* _obj)
		{
			m_cameraObj = _obj;
		}
		
	public:
		AudioSource* GetSceneAs()
		{
			return m_SceneAS;
		}

		Camera* GetMainCamera()
		{
			return mMainCamera;
		}

		GameObject* GetCameraObj()
		{
			return m_cameraObj;
		}

		GameObject* GetSceneLightObj()
		{
			return mSceneLightObj;
		}

		GameObject* GetPlayer()
		{
			return mPlayer;
		}


		Layer& GetLayer(eLayerType _type)
		{
			return mLayers[(UINT)_type];

		}
	
		std::shared_ptr<AudioClip> GetCurSceneAC()
		{
			return m_SceneAC;
		}
	public:


		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (Layer* layer : mLayers)
			{
				auto gameObjs = layer->GetGameObjects();

				for (GameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						findObjs.push_back(buff);
				}
			}
			return findObjs;
		}

		void DestorySceneGameObejct(eLayerType _eType, GameObject* _pGameObj) 
		{ 
			mLayers[(UINT)_eType].DestoryGameObject(_pGameObj);
		}
		
	public:

		int GetMonsterCnt()
		{
			return m_iMonsterCount;
		}

		void PlusMonsterCnt()
		{
			m_iMonsterCount++;
		}

		void MinusMonsterCnt()
		{
			m_iMonsterCount--;

			if (m_iMonsterCount <= 0)
				m_iMonsterCount = 0;
		}
		
		Fade* GetFade()
		{
			return m_Fade;
		}

		void SetDoor(GameObject* _obj)
		{
			m_Door = _obj;
		}
	
	protected:

		//GameObject* m_FadeObj;

		Fade* m_Fade;
		AudioSource* m_SceneAS;
		GameObject* mPlayer;

		GameObject* m_Testp;
		
		std::shared_ptr<AudioClip> m_SceneAC;

		//StartScene door Check
		GameObject* m_Door;


		//Player Á¤º¸
		int m_iPreHPCnt;
		int m_iPreBallPercent;
		bool m_bCoin;

		GameObject* m_GrimmDoor;

		GameObject* m_AbyssDoor;
		Brumm* m_Brumm;

		std::vector<GameObject*> m_Hunters;

		bool m_BEndingStart;
		float m_fEndingTime;

	private:
	
		std::vector<Layer> mLayers;
		Camera* mMainCamera;
		GameObject* mSceneLightObj;

		GameObject* m_cameraObj;

		

		int	m_iMonsterCount;

	
		
		

		



	};

}
