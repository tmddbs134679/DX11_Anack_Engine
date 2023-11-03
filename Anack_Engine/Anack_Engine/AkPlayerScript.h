#pragma once
#include "../Anack_Engine/AkPlayerScript.h"
#include "../Engine_SOURCE/AkAnimator.h"
#include "AkPlayerWeapon.h"
#include "AkGameStartEffect.h"
#include "AkHealth.h"
#include "../Engine_SOURCE/AkAudioSource.h"
#include "AkUI_HUD.h"

namespace Ak
{
	class Player;

	class PlayerScript : public Script
	{
	public:

		enum class EPlayerState
		{
			Idle,
			Move,
			Jump,
			DoubleJump,
			Crouch,
			CrouchMove,
			Dash,
			Attack,
			Damage,
			Dead,


		};

		PlayerScript();
		virtual ~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		

		void Complete();



		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollision(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:

		void SetState(EPlayerState _state)
		{
			mState = _state;
			UpdateAnimation();
		}


		void SetPlayer(Player* _player)
		{
			m_pPlayer = _player;
		}

		void SetHUD(std::vector<Health*> _obj)
		{
			m_HUDObj = _obj;
		}
		
		void SetPlayerHUD(UI_HUD* _hud)
		{
			m_PlayerHUD = _hud;
		}

	public:
		

		UI_HUD* GetPlayerHUD()
		{
			return m_PlayerHUD;
		}


		EPlayerState GetCurState()
		{
			return mState;
		}

		bool GetBoolAttack()
		{
			return m_bAttack;
		}

		Transform* GetTransform()
		{
			return mtr;
		}

		void RestToggleOn()
		{
			
			m_bRest = true;
		}

	private:

		void update_move();

		void update_state();



		void UpdateAnimation();

		void Idle();
		void Move();
		void Jump();
		void Crouch();
		void CrouchMove();
		void Dash();
		void Attack();
		void Damage();
		void DoubleJump();
		void Dead();

		
	private:

		Animator*	 mAnimator;

		Transform*	 mtr;
		int			 mduration;
		int			 mdir;
		int			 mPreDir;

		bool		 m_bAttack;


		EPlayerState mState;
		


		bool		mbFinished;
		bool		bIsJumping;
		bool		bIsGround;
		bool		m_bGameTrigger;
		bool		m_bAttackCoolDown;

		Player*		m_pPlayer;

		PlayerWeapon* m_pPlayerWeapon;
		
		float		  m_fAttackTime;
		float		  m_fGameTriggerTime;

		bool b_FirEffect;
		bool b_SecEffect;
		bool b_Terffect;
		bool b_SceneChange;

		std::vector<GameStartEffect*> m_CreateEffects;

		std::vector<Health*>	m_HUDObj;
		UI_HUD* m_PlayerHUD;

		int HUDCount = 4;

		float m_fInvTime;
		bool  m_bInv;

		bool  m_bIsDashing;
		float m_fDashDuration;
		float m_fDashTimer;

		float m_fDashY;
		float m_fJumpTime;

		bool m_bTest;
		Vector2 m_vPreColliderSize;

		bool m_bHoldcd;
		
	

		int m_iAttackSoundCnt;

		bool m_bSlowTime;
		float m_fSlowTime;

	
		bool m_bDoubleJump;

		bool m_bRadianceIn;

		float m_fFadeInTime;
		bool m_bFadeOut;

		bool m_bRest;
		bool m_bRestToggled;

		bool m_bPlayerDead;
		float m_bDeadTime;

		bool m_bDeadScene;
		float m_fDeadSceneTime;

	};
}

