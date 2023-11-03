#pragma once
#include "AkScript.h"
#include "AkUI_NPC.h"

namespace Ak
{

	class SceneChangeScript :
		public Script
	{


	public:
		SceneChangeScript();
		virtual ~SceneChangeScript();



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollision(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

		void SetSceneLight(Scene* _obj)
		{
			mScene = _obj;
		}

		Scene* GetSceneLight()
		{
			return mScene;
		}


		void SetTriggerName(std::wstring _str)
		{
			m_strTriggerName = _str;
		}


	private:

		std::wstring m_strTriggerName;
	private:

		float mTime;
		bool  bEnter;
		Scene* mScene;
	
		bool m_bInBattleScene;
		bool m_bInAbyssScene;
		bool m_bBossToStartScene;
		bool m_bAbyssToRadiance;
		
		
		bool m_bUI;

		UI_NPC* m_ui;

	};



}