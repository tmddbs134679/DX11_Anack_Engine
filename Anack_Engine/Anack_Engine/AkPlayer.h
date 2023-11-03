#pragma once
#include "../Engine_SOURCE/AkGameObject.h"
#include "../Engine_SOURCE/AkMeshRenderer.h"
#include "../Engine_SOURCE/AkAnimator.h"
#include "../Engine_SOURCE/AkLight.h"
#include "AkPlayerScript.h"
//#include "../Engine_SOURCE/AkCameraScript.h"
#include "../Engine_SOURCE/AkAudioSource.h"


namespace Ak
{
	class PlayerWeapon;
	class PlayerScript;

	class Player :
		public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	public:

		void bDamagePlayer()
		{
			m_bDamage = true;
		}

		void SetCurScene(Scene* _scene)
		{
			m_CurScene = _scene;
		}

		void SetBattleBox(GameObject* _obj)
		{
			m_BattleBoxObj = _obj;
		}

	/*	void SetSceneCameraObj(GameObject* _obj)
		{
			m_SceneCameraObj = _obj;
		}*/

	public:
		Scene* GetCurScene()
		{
			return m_CurScene;
		}

		GameObject* GetBattleBox()
		{
			return m_BattleBoxObj;
		}
	
		std::vector<std::shared_ptr<AudioClip>> GetPlayerClips()
		{
			return m_AudioClips;
		}

		void SetPlayerHud(UI_HUD* _hud)
		{
			m_Hud = _hud;
		}

		UI_HUD* GetHud()
		{
			return m_Hud;
		}

	private:
	
		static Transform* mTr;
		static MeshRenderer* mMr;
		static Collider2D* mCollider;
		static Animator* mAnimatior;
		static Light* mLight;
		static PlayerScript* mPlayerSr;
	
		
		PlayerWeapon* m_pPlayerWeapon;
		PlayerScript* m_pPlayerScript;


		bool c_bDamage;

		bool m_bDamage;
		renderer::PlayerCB PlayerCB;
		int m_iBlinkCNT;

		float m_fBlinkTime;


		AudioSource* m_AudioSource;

		Scene* m_CurScene;

		std::vector<std::shared_ptr<AudioClip>> m_AudioClips;


		GameObject* m_BattleBoxObj;
		UI_HUD* m_Hud;

		
		
		GameObject* m_PlayerShadow;

	};



}