#pragma once
#include "AkScene.h"

namespace Ak
{
	//extern bool m_bCoin;

	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destory();
		static void Release();

		

	public:
		template <typename T>
		static bool CreateScene(std::wstring _name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(_name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(_name, scene));
			mActiveScene = scene;
			//scene->Initialize();
			return true;
		}

		static Scene* LoadScene(std::wstring _name);

	public:
		static Scene* GetActiveScene()
			{
				return mActiveScene;
			}

		static void AddGameObject(eLayerType _eType, GameObject* _pGameObj)
		{
			mActiveScene->AddGameObject(_eType, _pGameObj);
		}
	
		static void DestoryObj(GameObject* _pGameObject)
		{
			mActiveScene->DestorySceneGameObejct(_pGameObject->GetLayerType(), _pGameObject);
		}

		static void TestCoin()
		{
			sbooltest = true;
		}

		static void HaveGrimmCoin()
		{
			sbGrimm = true;
		}

		static bool GetGrimmCoin()
		{
			return sbGrimm;
		}

		static bool GetCoin()
		{
			return sbooltest;
		}

		static void SetCurScene(std::wstring _str)
		{
			CurSceneName = _str;
		}

		static void SetPreScene(std::wstring _str)
		{
			PreSceneName = _str;
		}

		static std::wstring GetPreSceneName()
		{
			return PreSceneName;
		}

		static std::wstring GetCurSceneName()
		{
			return CurSceneName;
		}

		static void SetBall(int _i)
		{
			m_iBall = _i;
		}

		static int GetBall()
		{
			return m_iBall;
		}

		static void SetHealth(int _i)
		{
			m_iHealth = _i;
		}

		static int GetHealth()
		{
			return m_iHealth;
		}

		static void DeadState(bool _b)
		{
			sbDeadState = _b;
		}

		static bool GetDeadState()
		{
			return sbDeadState;
		}


	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
		static bool sbooltest;
		static bool sbGrimm;
		static int   m_iBall;
		static int   m_iHealth;

		static std::wstring PreSceneName;
		static std::wstring CurSceneName;

		static bool sbDeadState;


		//static int m_iPreHPCnt;
		//static int m_iPreBallPercent;
		

	};


}