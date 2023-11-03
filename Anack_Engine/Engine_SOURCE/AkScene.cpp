#include "AkScene.h"
#include "AkRenderer.h"
#include "AkTime.h"
#include "AkLayer.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkSceneManager.h"

namespace Ak
{
	Scene::Scene()
		: mPlayer(nullptr)
		, m_iMonsterCount(0)
		, m_Door(nullptr)
		, m_iPreBallPercent(0)
		, m_iPreHPCnt(0)
		, m_bCoin(false)
	{

		mLayers.resize((int)Ak::enums::eLayerType::End);



	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{


	}

	void Scene::Update()
	{


		for (Layer& layer : mLayers)
		{
			layer.Update();
		}

	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}



	}

	void Scene::Destory()
	{

		for (Layer& layer : mLayers)
		{
			layer.Destory();
		}
		
	}

	void Scene::OnEnter()
	{
		m_Fade = new Fade();
		m_Fade->bInFadeIn();
		AddGameObject(eLayerType::UI, m_Fade);
		
		Initialize();

		if (SceneManager::GetCoin())
		{
			if(mPlayer != nullptr)
				mPlayer->CoinHave();
		}

		if (m_SceneAS != nullptr)
			m_SceneAS->Play();
	}

	void Scene::OnExit()
	{
		if (m_SceneAS != nullptr)
		m_SceneAS->Stop();

		if (m_SceneAC != nullptr)
			m_SceneAC->Stop();

		if (mPlayer != nullptr)
		{
			if (mPlayer->GetCoin())
			{
				m_bCoin = true;
			}
		}
		
	
	}

	void Scene::DestroyAll()
	{
		for (Layer& layer : mLayers)
		{
			layer.DestroyAll();
		}

	}

	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);

	}

}