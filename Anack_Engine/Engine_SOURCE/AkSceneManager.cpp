#include "AkSceneManager.h"


namespace Ak
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	bool SceneManager::sbooltest = false;
	bool SceneManager::sbGrimm = false;
	int  SceneManager::m_iBall = 10;
	int  SceneManager::m_iHealth = 4;
	bool SceneManager::sbDeadState = false;

	std::wstring SceneManager::PreSceneName = L" ";
	std::wstring SceneManager::CurSceneName = L" ";

	void SceneManager::Initialize()
	{

		//mActiveScene = new MenuScene();

		//Scene* StartScene01 = new StartGameScene();
		//Scene* BattleScene_01 = new BattleScene01();

		//mScenes.insert(std::make_pair(L"Menu", mActiveScene));
		//mScenes.insert(std::make_pair(L"StartGame", StartScene01));
		//mScenes.insert(std::make_pair(L"Battle_BG01", BattleScene_01));

		//mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));

		//mActiveScene->Initialize();

		
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();

	}

	void SceneManager::Destory()
	{
		mActiveScene->Destory();

	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring _name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(_name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return	iter->second;
	}
}