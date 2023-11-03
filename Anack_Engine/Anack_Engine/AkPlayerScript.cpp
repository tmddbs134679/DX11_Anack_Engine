#include "AkPlayerScript.h"
#include "AkTransform.h"
#include "AkTime.h"
#include "AkCameraScript.h"
#include "AkInput.h"
#include "AkGameObject.h"
#include "AkAnimator.h"
#include "AkResources.h"
#include "AkRigidBody.h"
#include "AkSceneManager.h"
#include "AkGameTrigger.h"
#include "AkPlayerAttackScript.h"
#include "AkFade.h"




namespace Ak
{
	PlayerScript::PlayerScript()
		: mAnimator(nullptr)
		, mtr(nullptr)
		, mduration(1)
		, mdir(1)
		, mState(EPlayerState::Idle)
		, mPreDir(1)
		, mbFinished(false)
		, bIsJumping(false)
		, bIsGround(false)
		, m_bGameTrigger(false)
		, m_bAttack(false)
		, m_pPlayerWeapon(nullptr)
		, m_fAttackTime(0.f)
		, m_fGameTriggerTime(0.f)
		, b_FirEffect(false)
		, b_SecEffect(false)
		, b_Terffect(false)
		, b_SceneChange(false)
		, m_bAttackCoolDown(true)
		, m_fInvTime(0.f)
		, m_bInv(false)
		, m_bIsDashing(false)
		, m_fDashDuration(0.3f)
		, m_fDashTimer(0.f)
		, m_fJumpTime(0.f)
		, m_bTest(false)
		, m_bHoldcd(false)
		, m_iAttackSoundCnt(0)
		, m_bSlowTime(true)
		, m_fSlowTime(0.f)
		, m_bDoubleJump(true)
		, m_bRadianceIn(true)
		, m_fFadeInTime(0.f)
		, m_bRest(false)
		, m_bPlayerDead(false)
		, m_bDeadTime(0.f)
		, m_bDeadScene(false)
		, m_fDeadSceneTime(0.f)
	{

		
	}


	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
		
#pragma region Knight_animation
		
		
		std::shared_ptr<Texture> Knight_idle_f
			= Resources::Load<Texture>(L"Knight_idle_f", L"..\\Resources\\Texture\\Knight\\Knight_idle_f.png");

		std::shared_ptr<Texture> Knight_idle_l
			= Resources::Load<Texture>(L"Knight_idle_l", L"..\\Resources\\Texture\\Knight\\Knight_idle_l.png");

		std::shared_ptr<Texture> Knight_idle_r
			= Resources::Load<Texture>(L"Knight_idle_r", L"..\\Resources\\Texture\\Knight\\Knight_idle_r.png");


		std::shared_ptr<Texture> Knight_walk_r
			= Resources::Load<Texture>(L"Knight_walk_r", L"..\\Resources\\Texture\\Knight\\Knight_Walk_r.png");


		std::shared_ptr<Texture> Knight_walk_l
			= Resources::Load<Texture>(L"Knight_walk_l", L"..\\Resources\\Texture\\Knight\\Knight_Walk_l.png");


		std::shared_ptr<Texture> Knight_cr_ready_r
			= Resources::Load<Texture>(L"Knight_cr_ready_r", L"..\\Resources\\Texture\\Knight\\Knight_Cr_Ready_r.png");
		

		std::shared_ptr<Texture> Knight_cr_ready_l
			= Resources::Load<Texture>(L"Knight_cr_ready_l", L"..\\Resources\\Texture\\Knight\\Knight_Cr_Ready_l.png");


		std::shared_ptr<Texture> Knight_cr_start_r
			= Resources::Load<Texture>(L"Knight_cr_start_r", L"..\\Resources\\Texture\\Knight\\Knight_Cr_Start_r.png");

		std::shared_ptr<Texture> Knight_cr_start_l
			= Resources::Load<Texture>(L"Knight_cr_start_l", L"..\\Resources\\Texture\\Knight\\Knight_Cr_Start_l.png");

		std::shared_ptr<Texture> Knight_jump_r
			= Resources::Load<Texture>(L"Knight_jump_r", L"..\\Resources\\Texture\\Knight\\Knight_jump_r.png");

		std::shared_ptr<Texture> Knight_jump_l
			= Resources::Load<Texture>(L"Knight_jump_l", L"..\\Resources\\Texture\\Knight\\Knight_jump_l.png");

		std::shared_ptr<Texture> Knight_double_jump_r
			= Resources::Load<Texture>(L"Knight_double_jump_r", L"..\\Resources\\Texture\\Knight\\Knight_Double_jump_r.png");

		std::shared_ptr<Texture> Knight_double_jump_l
			= Resources::Load<Texture>(L"Knight_double_jump_l", L"..\\Resources\\Texture\\Knight\\Knight_Double_jump_l.png");

		std::shared_ptr<Texture> Knight_attack_r
			= Resources::Load<Texture>(L"Knight_attack_r", L"..\\Resources\\Texture\\Knight\\Knight_attak_r.png");

		std::shared_ptr<Texture> Knight_attack_l
			= Resources::Load<Texture>(L"Knight_attack_l", L"..\\Resources\\Texture\\Knight\\Knight_attak_l.png");

		std::shared_ptr<Texture> Knight_attack_down
			= Resources::Load<Texture>(L"Knight_attack_down", L"..\\Resources\\Texture\\Knight\\Knight_attack_down.png");

		std::shared_ptr<Texture> Knight_dash_l
			= Resources::Load<Texture>(L"Knight_dash_l", L"..\\Resources\\Texture\\Knight\\Knight_dash_l.png");

		std::shared_ptr<Texture> Knight_dash_r
			= Resources::Load<Texture>(L"Knight_dash_r", L"..\\Resources\\Texture\\Knight\\Knight_dash_r.png");

		std::shared_ptr<Texture> Knight_damage_l
			= Resources::Load<Texture>(L"Knight_damage_l", L"..\\Resources\\Texture\\Knight\\Knight_damage_l.png");

		std::shared_ptr<Texture> Knight_damage_r
			= Resources::Load<Texture>(L"Knight_damage_r", L"..\\Resources\\Texture\\Knight\\Knight_damage_r.png");


		std::shared_ptr<Texture> Knight_dead
			= Resources::Load<Texture>(L"Knight_dead", L"..\\Resources\\Texture\\Knight\\Knight_Dead.png");

 
#pragma endregion

		mAnimator = GetOwner()->GetComponent<Animator>();
		

		mtr = GetOwner()->GetComponent<Transform>();

		m_vPreColliderSize = Vector2(0.25f, 0.6f);


		mAnimator->Create(L"Knight_idle_f", Knight_idle_f, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 6);
		mAnimator->Create(L"Knight_idle_l", Knight_idle_l, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 6);
		mAnimator->Create(L"Knight_idle_r", Knight_idle_r, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 6);

		mAnimator->Create(L"Knight_walk_r", Knight_walk_r, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 9);
		mAnimator->Create(L"Knight_walk_l", Knight_walk_l, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 9);

		mAnimator->Create(L"Knight_cr_ready_r", Knight_cr_ready_r, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 3);
		mAnimator->Create(L"Knight_cr_ready_l", Knight_cr_ready_l, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 3);

		mAnimator->Create(L"Knight_cr_start_r", Knight_cr_start_r, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 7);
		mAnimator->Create(L"Knight_cr_start_l", Knight_cr_start_l, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 7);

		mAnimator->Create(L"Knight_jump_r", Knight_jump_r, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 12);
		mAnimator->Create(L"Knight_jump_l", Knight_jump_l, Vector2(0.0f, 0.0f), Vector2(128.0f, 130.f), 12);

		mAnimator->Create(L"Knight_double_jump_r", Knight_double_jump_r, Vector2(0.0f, 0.0f), Vector2(130.0f, 130.f), 7);
		mAnimator->Create(L"Knight_double_jump_l", Knight_double_jump_l, Vector2(0.0f, 0.0f), Vector2(130.0f, 130.f), 7);

		mAnimator->Create(L"Knight_attack_r", Knight_attack_r, Vector2(0.0f, 0.0f), Vector2(128.5f, 130.f), 8, Vector2::Zero, 0.05f);
		mAnimator->Create(L"Knight_attack_l", Knight_attack_l, Vector2(0.0f, 0.0f), Vector2(125.0f, 130.f), 9, Vector2::Zero, 0.05f);
		mAnimator->Create(L"Knight_attack_down", Knight_attack_down, Vector2(0.0f, 0.0f), Vector2(130.0f, 130.f), 5);

		mAnimator->Create(L"Knight_dash_l", Knight_dash_l, Vector2(0.0f, 0.0f), Vector2(180.f, 130.f), 6, Vector2::Zero, 0.05f);
		mAnimator->Create(L"Knight_dash_r", Knight_dash_r, Vector2(0.0f, 0.0f), Vector2(180.f, 130.f), 6, Vector2::Zero, 0.05f);
		
		mAnimator->Create(L"Knight_damage_l", Knight_damage_l, Vector2(0.0f, 0.0f), Vector2(128.f, 130.f), 4, Vector2::Zero, 0.05f);
		mAnimator->Create(L"Knight_damage_r", Knight_damage_r, Vector2(0.0f, 0.0f), Vector2(128.f, 130.f), 4, Vector2::Zero, 0.05f);

		mAnimator->Create(L"Knight_dead", Knight_dead, Vector2(0.0f, 0.0f), Vector2(100.f, 100.f), 1);



		mAnimator->PlayAnimation(L"Knight_jump_r", true);

	}

	void PlayerScript::Update()
	{
	

		if (m_bInv)
		{
			m_fInvTime += Time::DeltaTime();

			if (m_fInvTime >= 2.f)
			{
				m_bInv = false;
				m_fInvTime = 0.f;
			}
		}

		if (m_bSlowTime)
		{
			m_fSlowTime += Time::DeltaTime();

			Time::SetSlowTime(0.2);

			if (m_fSlowTime >= 0.2)
			{
				Time::SetSlowTime(1);
				m_fSlowTime = 0.f;
				m_bSlowTime = false;
				SetState(EPlayerState::Jump);
			}
		}

		if (m_bRest)
		{
			m_pPlayer->GetComponent<Transform>()->SetPositionXY(Vector2(5.f, -2.7f));
			mAnimator->PlayAnimation(L"Knight_idle_f", false);
		}

		update_move();


		//PlayerWeapon 위치 조절
		if (m_bAttack)
		{
			if (!bIsGround && Input::GetKey(eKeyCode::DOWN))
			{
				Vector3 vpos = m_pPlayer->GetComponent<Transform>()->GetPosition();
				m_pPlayerWeapon->GetComponent<Transform>()->SetPosition(Vector3(vpos.x, vpos.y - 1.f, vpos.z));
				m_bHoldcd = true;
			}
			else if (mdir == 1 && !m_bHoldcd)
			{
				Vector3 vpos = m_pPlayer->GetComponent<Transform>()->GetPosition();
				m_pPlayerWeapon->GetComponent<Transform>()->SetPosition(Vector3(vpos.x + 1.f, vpos.y, vpos.z));

			}
			else if(mdir == -1 && !m_bHoldcd)
			{
				Vector3 vpos = m_pPlayer->GetComponent<Transform>()->GetPosition();
				m_pPlayerWeapon->GetComponent<Transform>()->SetPosition(Vector3(vpos.x - 1.f, vpos.y, vpos.z));
			}


			m_fAttackTime += Time::DeltaTime();

			if (m_fAttackTime >= 0.2f)
			{
				SceneManager::DestoryObj(m_pPlayerWeapon);

				delete m_pPlayerWeapon;
				m_pPlayerWeapon = nullptr;

				m_bAttack = false;
				m_fAttackTime = 0.f;
				m_bAttackCoolDown = true;
				m_bHoldcd = false;
			}

		}


		update_state();

		if (m_bFadeOut)
		{

			m_fFadeInTime += Time::DeltaTime();

			if (m_fFadeInTime >= 1.f)
			{
				m_pPlayer->GetCurScene()->GetFade()->bInFadeIn();
				m_pPlayer->GetComponent<Transform>()->SetPositionXY(Vector2(-20.0f, 10.f));
				m_fFadeInTime = 0.f;
				m_bFadeOut = false;
				

			}
		}


		//Player Dead상태이면 fadeout
		if (m_bPlayerDead)
		{
			m_bDeadTime += Time::DeltaTime();

			if (m_bDeadTime >= 1.f)
			{
				m_pPlayer->GetCurScene()->GetFade()->bInFadeOut();
				m_bDeadTime = 0.f;
				m_bDeadScene = true;
				m_bPlayerDead = false;
			}
		}

		//Dead상태 -> 2초후 Scene 전환
		if (m_bDeadScene)
		{
			m_fDeadSceneTime += Time::DeltaTime();
			if (m_fDeadSceneTime >= 2.f)
			{
				SetState(EPlayerState::Idle);

				m_bDeadScene = false;
				m_fDeadSceneTime = 0.f;

				SceneManager::DeadState(true);
				SceneManager::LoadScene(L"StartGame");

			}

		}


		if (SceneManager::GetHealth() == 0)
		{
			m_pPlayer->SetPlayerShadow(true);
		}
		else
		{
			m_pPlayer->SetPlayerShadow(false);
		}

	}

	void PlayerScript::LateUpdate()
	{
	
	}

	void PlayerScript::Complete()
	{
		
	}

	void PlayerScript::update_move()
	{


		
		mtr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = mtr->GetPosition();

		
		if (!m_bSlowTime)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				if (!m_bIsDashing)
				{
					pos.x -= 5.0f * Time::DeltaTime();
					mtr->SetPosition(pos);
					mdir = -1;
				}

			}
			else if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				mdir = -1;
			}
			else if (Input::GetKey(eKeyCode::RIGHT))
			{
				if (!m_bIsDashing)
				{
					pos.x += 5.0f * Time::DeltaTime();
					mtr->SetPosition(pos);
					mdir = 1;
				}

			}
			else if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				mdir = 1;
			}
			else if (Input::GetKey(eKeyCode::DOWN))
			{
				Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
				cd->SetSize(Vector2(0.5f, 0.4f));
			}
			else if (Input::GetKey(eKeyCode::UP))
			{
				pos.y += 5.0f * Time::DeltaTime();
				mtr->SetPosition(pos);
			}


			if (Input::GetKeyUp(eKeyCode::DOWN))
			{
				Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
				cd->SetSize(m_vPreColliderSize);
			}

#pragma region Dash Func

			if (Input::GetKeyDown(eKeyCode::X))
			{
			
				if (!m_bIsDashing)
				{
					m_bIsDashing = true;
					m_fDashTimer = m_fDashDuration;
					m_fDashY = pos.y;
				}
			}

			if (m_bIsDashing)
			{

				if (m_fDashTimer > 0.f)
				{
					float DashSpeed = 20.f;
					static float HoldY = mtr->GetPosition().y;

					if (mdir == 1)
					{
						pos.x += DashSpeed * Time::DeltaTime();
						pos.y = m_fDashY;
					}
					else
					{
						pos.x -= DashSpeed * Time::DeltaTime();
						pos.y = m_fDashY;
					}
					mtr->SetPosition(pos);
					m_fDashTimer -= Time::DeltaTime();

				}
				else
				{

					m_bIsDashing = false;

					//Dash 종료할 때 상태입력이 있는 경우
					if (!bIsGround)
					{
						SetState(EPlayerState::Jump);
					}
					else if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
					{
						SetState(EPlayerState::Move);
					}
					else
					{
						SetState(EPlayerState::Idle);
					}
				}
			}


#pragma endregion


			if (Input::GetKey(eKeyCode::SPACE))
			{
				m_bTest = true;
				bIsGround = false;

				Vector2 curPosition = GetOwner()->GetComponent<Transform>()->GetPostionXY();

				if (m_fJumpTime <= 0.2f)
				{

					mState = EPlayerState::Jump;
					GetOwner()->GetComponent<RigidBody>()->AddVelocity(Vector2(GetOwner()->GetComponent<RigidBody>()->GetVelocity().x, 30.f));
					

				}
				else
				{
					m_bTest = false;
				}
			}

			if (m_bTest)
			{
				m_fJumpTime += Time::DeltaTime();

			}
		}


		//더블점프
		if (!bIsGround)
		{
			if (Input::GetKey(eKeyCode::UP))
			{
				if (Input::GetKeyDown(eKeyCode::SPACE))
				{
					if (m_bDoubleJump)
					{
						GetOwner()->GetComponent<RigidBody>()->AddVelocity(Vector2(GetOwner()->GetComponent<RigidBody>()->GetVelocity().x, 30.f));
						

					}
				}
			}
		}
		
		if (Input::GetKeyDown(eKeyCode::D))
		{
			m_PlayerHUD->GetHP_Ball()->DisLifeSoul();
			SceneManager::SetBall(m_PlayerHUD->GetHP_Ball()->GetLifeCnt());

			//영혼 퍼센트가 30이상인지 확인
			if (m_PlayerHUD->GetHP_Ball()->CheckBoolLife())
			{
				int HPCNT = m_PlayerHUD->GetHealthCNT();
				
				if (HPCNT < 4)
				{
					m_PlayerHUD->IncreHealthCNT();
					int HPCNT = m_PlayerHUD->GetHealthCNT();
					SceneManager::SetHealth(HPCNT);
					//HP증가
					Vector3 HudPos = m_HUDObj[HPCNT]->GetComponent<Transform>()->GetPosition();
					m_HUDObj[HPCNT]->GetComponent<Transform>()->SetPosition(Vector3(HudPos.x, 3.2f, HudPos.z));
					m_HUDObj[HPCNT]->GetComponent<Animator>()->PlayAnimation(L"Health_Add", false);
				}
				else
				{
					return;
				}
	

			}
			
		}
	}

	void PlayerScript::update_state()
	{

	


		if (!m_bSlowTime)
		{
			//좌
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				if (!bIsGround)
				{
					SetState(EPlayerState::Jump);
					//return;
				}
				else
				{
					SetState(EPlayerState::Move);

					std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
					for (const auto& clip : playercp)
					{
						if (clip->GetKey() == L"Knight_footstep")
						{
							m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
							m_pPlayer->GetComponent<AudioSource>()->Play();
						}
					}
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{

				if (!bIsGround)
				{
					std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
					for (const auto& clip : playercp)
					{
						if (clip->GetKey() == L"Knight_footstep")
						{
							m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
							m_pPlayer->GetComponent<AudioSource>()->Stop();
						}
					}
				}
			}

		
			//우
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				if (!bIsGround)
				{
					SetState(EPlayerState::Jump);
					return;
				}
				else
				{
					SetState(EPlayerState::Move);


					std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
					for (const auto& clip : playercp)
					{
						if (clip->GetKey() == L"Knight_footstep")
						{
							m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
							m_pPlayer->GetComponent<AudioSource>()->Play();
						}
					}

				}
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{

				if (!bIsGround)
				{
					std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
					for (const auto& clip : playercp)
					{
						if (clip->GetKey() == L"Knight_footstep")
						{
							m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
							m_pPlayer->GetComponent<AudioSource>()->Stop();
						}
					}
				}
			}

			//움크리기
			if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::DOWN)
				|| Input::GetKeyDown(eKeyCode::RIGHT) && Input::GetKey(eKeyCode::DOWN))
			{
				Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
				cd->SetSize(Vector2(0.5f, 0.4f));

				if (bIsGround)
				{
					SetState(EPlayerState::CrouchMove);
				}
			}
			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				Collider2D* cd = GetOwner()->GetComponent<Collider2D>();
				cd->SetSize(Vector2(0.5f, 0.4f));
				if (bIsGround)
				{
					SetState(EPlayerState::Crouch);
				}
			}

			//키입력 움크리기
			if (Input::GetKey(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::DOWN)
				|| Input::GetKeyDown(eKeyCode::LEFT) && Input::GetKey(eKeyCode::DOWN))
			{
				if (bIsGround)
				{
					SetState(EPlayerState::CrouchMove);
				}
			}

			//점프
			if (mState == EPlayerState::Jump)
			{
				if (bIsGround)
				{
					if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
					{
						SetState(EPlayerState::Move);


					}
					else
					{
						SetState(EPlayerState::Idle);
						
					}
				}
		
			}

			//점프
			if (Input::GetKeyDown(eKeyCode::SPACE) && mState != EPlayerState::Jump)
			{
				SetState(EPlayerState::Jump);
				m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Knight_Jump", L"..\\Resources\\Sound\\Knight_jump.mp3"));
				m_pPlayer->GetComponent<AudioSource>()->Play();

			}

			//더블점프
			if (!bIsGround)
			{
				if (Input::GetKey(eKeyCode::UP))
				{
					if (Input::GetKeyDown(eKeyCode::SPACE))
					{
						if (m_bDoubleJump)
						{
							SetState(EPlayerState::DoubleJump);
							m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Knight_double_jump", L"..\\Resources\\Sound\\Knight_double_jump.mp3"));
							m_pPlayer->GetComponent<AudioSource>()->Play();
							m_bDoubleJump = false;
						}
					}
				}
			}

			if (mAnimator->GetPlayAnimationName() == L"Knight_double_jump_r" ||
				mAnimator->GetPlayAnimationName() == L"Knight_double_jump_l")
			{
				if (mAnimator->GetAnimation()->isComplete())
				{
					SetState(EPlayerState::Jump);
				}

			}

			//공격
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (m_bAttackCoolDown)
				{
					SetState(EPlayerState::Attack);

					Vector3 vpos = m_pPlayer->GetComponent<Transform>()->GetPosition();

					m_pPlayerWeapon = new PlayerWeapon();
					m_pPlayerWeapon->Initialize();
					m_pPlayerWeapon->SetPlayer(GetOwner());
					m_pPlayerWeapon->GetComponent<PlayerAttackScript>()->SetHUD(m_PlayerHUD);

					SceneManager::AddGameObject(eLayerType::PlayerAttack, m_pPlayerWeapon);

					if (!bIsGround && Input::GetKey(eKeyCode::DOWN))
					{
						m_pPlayerWeapon->GetComponent<Animator>()->PlayAnimation(L"Knight_Attack_effect_d", false);
					}
					else if (mdir == 1)
					{
						m_pPlayerWeapon->GetComponent<Animator>()->PlayAnimation(L"Knight_Attack_effect_r", false);
					}
					else if (mdir == -1)
					{
						m_pPlayerWeapon->GetComponent<Animator>()->PlayAnimation(L"Knight_Attack_effect_l", false);
					}

					//FootStep 정지
					std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
					for (const auto& clip : playercp)
					{
						if (clip->GetKey() == L"Knight_footstep")
						{
							m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
							m_pPlayer->GetComponent<AudioSource>()->Stop();
						}
					}


					m_bAttack = true;
					m_bAttackCoolDown = false;
				}

				//AttackSound
				switch (m_iAttackSoundCnt)
				{
				case 0:
					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword1", L"..\\Resources\\Sound\\sword1.mp3"));
					break;
				case 1:
					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword2", L"..\\Resources\\Sound\\sword2.mp3"));
					break;
				case 2:
					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword3", L"..\\Resources\\Sound\\sword3.mp3"));
					break;
				case 3:
					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword4", L"..\\Resources\\Sound\\sword4.mp3"));
					break;
				case 4:
					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword5", L"..\\Resources\\Sound\\sword5.mp3"));
					break;
				default:
					break;
				}
				//m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"sword1", L"..\\Resources\\Sound\\sword1.mp3"));
				m_pPlayer->GetComponent<AudioSource>()->Play();
				m_iAttackSoundCnt++;

				if (m_iAttackSoundCnt == 5)
					m_iAttackSoundCnt = 0;
			}


			//Attack Anim 종료 후 anim설정
			//finish
			if (mAnimator->GetPlayAnimationName() == L"Knight_attack_r" ||
				mAnimator->GetPlayAnimationName() == L"Knight_attack_l")
			{
				if (mAnimator->GetAnimation()->isComplete())
				{

					if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
					{
						if (!bIsGround)
						{
							SetState(EPlayerState::Jump);
						}
						else
						{
							SetState(EPlayerState::Move);

							std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
							for (const auto& clip : playercp)
							{
								if (clip->GetKey() == L"Knight_footstep")
								{
									m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
									m_pPlayer->GetComponent<AudioSource>()->Play();
								}
							}
						}

					}
				}
			}

			if (mAnimator->GetPlayAnimationName() == L"Knight_attack_down")
			{
				if (mAnimator->GetAnimation()->isComplete())
				{
					SetState(EPlayerState::Jump);
				}
			}

			//대쉬
			if (Input::GetKeyDown(eKeyCode::X))
			{
				SetState(EPlayerState::Dash);

				std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
				for (const auto& clip : playercp)
				{
					if (clip->GetKey() == L"Knight_dash")
					{
						m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
						m_pPlayer->GetComponent<AudioSource>()->Play();
					}
				}

			}

			//키 Up
			if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				if (Input::GetKey(eKeyCode::RIGHT) && bIsGround == true)
				{
					SetState(EPlayerState::Move);
				}
				else
				{
					if (bIsGround)
					{
						SetState(EPlayerState::Idle);
					}
					else
					{
						SetState(EPlayerState::Jump);
					}
				}


				//FootStep 정지
				std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
				for (const auto& clip : playercp)
				{
					if (clip->GetKey() == L"Knight_footstep")
					{
						m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
						m_pPlayer->GetComponent<AudioSource>()->Stop();
					}
				}


			}

			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				if (Input::GetKey(eKeyCode::LEFT) && bIsGround == true)
				{
					SetState(EPlayerState::Move);
				}
				else
				{
					if (!bIsGround)
					{
						SetState(EPlayerState::Jump);
					}
					else
					{
						SetState(EPlayerState::Idle);
					}
				}

				//FootStep 정지
				std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
				for (const auto& clip : playercp)
				{
					if (clip->GetKey() == L"Knight_footstep")
					{
						m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
						m_pPlayer->GetComponent<AudioSource>()->Stop();
					}
				}

			}

			if (Input::GetKeyUp(eKeyCode::DOWN))
			{

				if (bIsGround)
				{
					SetState(EPlayerState::Idle);

					if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
					{
						SetState(EPlayerState::Move);
					}
				}
			}

			if (SceneManager::GetHealth() == -1)
			{
				SetState(EPlayerState::Dead);
			}
		}
		
	}

	void PlayerScript::UpdateAnimation()
	{
		switch (mState)
		{
		case PlayerScript::EPlayerState::Idle:
			Idle();
			break;

		case PlayerScript::EPlayerState::Move:
			Move();
			break;

		case PlayerScript::EPlayerState::Jump:
			Jump();
			break;

		case PlayerScript::EPlayerState::DoubleJump:
			DoubleJump();
			break;

		case PlayerScript::EPlayerState::Crouch:
			Crouch();
			break;

		case PlayerScript::EPlayerState::CrouchMove:
			CrouchMove();
			break;

		case PlayerScript::EPlayerState::Dash:
			Dash();
			break;
		case PlayerScript::EPlayerState::Attack:
			Attack();
			break;
		case PlayerScript::EPlayerState::Damage:
			Damage();
			break;
		case PlayerScript::EPlayerState::Dead:
			Dead();
			break;

		}
	}

	void PlayerScript::Idle()
 	{
		if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_idle_r",true);
		else if(mdir == -1)
			mAnimator->PlayAnimation(L"Knight_idle_l", true);
		else
		{
			mAnimator->PlayAnimation(L"Knight_idle_f", true);
			m_pPlayer->GetComponent<Collider2D>()->SetSize(Vector2(0.25f, 0.6f));
		}
			
	}

	void PlayerScript::Move()
	{
		if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_walk_r", true);
		else if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_walk_l", true);

	}

	void PlayerScript::Jump()
	{
		mduration = false;

		if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_jump_r", mduration);
		else if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_jump_l", mduration);
		
	}

	void PlayerScript::Crouch()
	{

		if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_cr_ready_l", false);
		else if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_cr_ready_r", false);
	
	}

	void PlayerScript::CrouchMove()
	{
			 if (mdir == -1)
				mAnimator->PlayAnimation(L"Knight_cr_start_l", true);
			else if (mdir == 1)
				mAnimator->PlayAnimation(L"Knight_cr_start_r", true);
	}

	void PlayerScript::Dash()
	{
		if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_dash_l", true);
		else if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_dash_r", true);

	
	}


	void PlayerScript::Attack()
	{
		mduration = false;
		if (!bIsGround && Input::GetKey(eKeyCode::DOWN))
		{
			mAnimator->PlayAnimation(L"Knight_attack_down", mduration);
		}
		else if (mdir == 1)
		{

			mAnimator->PlayAnimation(L"Knight_attack_r", mduration);
			
		}
		else if (mdir == -1)
		{
			mAnimator->PlayAnimation(L"Knight_attack_l", mduration);
			
		}
			
		mbFinished = true;
	}

	void PlayerScript::Damage()
	{
		if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_damage_l", false);
		else if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_damage_r", false);
	}

	void PlayerScript::DoubleJump()
	{
		if (mdir == 1)
			mAnimator->PlayAnimation(L"Knight_double_jump_r", false);
		else if (mdir == -1)
			mAnimator->PlayAnimation(L"Knight_double_jump_l", false);
	}

	void PlayerScript::Dead()
	{
		mAnimator->PlayAnimation(L"Knight_dead", false);
		m_pPlayer->GetComponent<Collider2D>()->SetSize(Vector2(0.25f, 0.4f));
		m_bPlayerDead = true;
	}


	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		m_fInvTime += Time::DeltaTime();

		if (other->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			bIsGround = true;
			m_bDoubleJump = true;

			if (!other->GetOwner()->GetGroundSide())
			{
				m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Knight_land", L"..\\Resources\\Sound\\Knight_land_soft.mp3"));
				m_pPlayer->GetComponent<AudioSource>()->Play();

			}

			if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
			{
				std::vector<std::shared_ptr<AudioClip>> playercp = m_pPlayer->GetPlayerClips();
				for (const auto& clip : playercp)
				{
					if (clip->GetKey() == L"Knight_footstep")
					{
						m_pPlayer->GetComponent<AudioSource>()->SetClip(clip);
						m_pPlayer->GetComponent<AudioSource>()->Play();
					}
				}
			}

		}

		m_fJumpTime = 0.f;

		b_FirEffect = true;
		b_SecEffect = true;
		b_Terffect = true;

		GameObject* pGameObj = other->GetOwner();

		if (pGameObj->GetName() == L"Game_Start")
		{
			m_bGameTrigger = true;
		}


		//몬스터 충돌 및 MonsterAttack 충돌 시 , Trap인 경우 
		if (pGameObj->GetLayerType() == eLayerType::Monster || pGameObj->GetLayerType() == eLayerType::MonsterAttack)
		{

			//충돌할때 대쉬중이면 대쉬 정지
			m_bIsDashing = false;

			if (!m_bInv)
			{
				//남은 HP
				int HPCNT = m_PlayerHUD->GetHealthCNT();

				if (HPCNT < 0)
				{
					return;
				}

				//Player hp감소 시 깜박임
				m_pPlayer->bDamagePlayer();

				//HP감소
				Vector3 HudPos = m_HUDObj[HPCNT]->GetComponent<Transform>()->GetPosition();
				m_HUDObj[HPCNT]->GetComponent<Transform>()->SetPosition(Vector3(HudPos.x, HudPos.y - 0.2f, HudPos.z));
				m_HUDObj[HPCNT]->GetComponent<Animator>()->PlayAnimation(L"Health_broken", false);

				m_PlayerHUD->DisHealthCNT();
				SceneManager::SetHealth(m_PlayerHUD->GetHealthCNT());

				Collider2D* pPlayerCollider = GetOwner()->GetComponent<Collider2D>();
				Collider2D* pMonsterCollider = pGameObj->GetComponent<Collider2D>();


				Vector3 vPos = pPlayerCollider->GetPosition();
				Vector2 vSize = pPlayerCollider->GetSize();
				Vector3 vScale = GetOwner()->GetComponent<Transform>()->GetScale();


				Vector3 vMonPos = pMonsterCollider->GetPosition();
				Vector2 vMonSize = pMonsterCollider->GetSize();
				Vector3 vMonScale = pGameObj->GetComponent<Transform>()->GetScale();


				//넉백
				float DiffDirX = vPos.x - vMonPos.x;

				float Knock_Back_X = 0.f;
				float Knock_Back_Y = 1.f;

				if (DiffDirX <= 0)
				{
					Knock_Back_X = -1.f;
					SetState(EPlayerState::Damage);
				}
					
				else
				{
					Knock_Back_X = 1.f;
					SetState(EPlayerState::Damage);
				}
					
				//기존 Player Position
				float prePlayerPosX = GetOwner()->GetComponent<Transform>()->GetPosition().x;
				float prePlayerPosY = GetOwner()->GetComponent<Transform>()->GetPosition().y;

				
				GetOwner()->GetComponent<Transform>()->SetPositionXY(Vector2(prePlayerPosX + (1.f * Knock_Back_X), prePlayerPosY + (1.5f * Knock_Back_Y)));

				//Damage Slow Time 
				//DamageSound 소리 추가


				m_pPlayer->GetCurScene()->GetCameraObj()->GetComponent<CameraScript>()->PlayShakeCamera();

				m_bSlowTime = true;
				m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Damage_AC", L"..\\Resources\\Sound\\Knight_damage.mp3"));
				m_pPlayer->GetComponent<AudioSource>()->Play();
			
				m_bInv = true;
			}
		}

		if (pGameObj->GetLayerType() ==eLayerType::LayeredObj)
		{
			//Coin 획득 시 
			if (pGameObj->GetName() == L"GrimmCoin")
			{
				SceneManager::HaveGrimmCoin();
				delete pGameObj;
			}

			if (pGameObj->GetName() == L"BoxCoin")
			{
				m_pPlayer->CoinHave();
				SceneManager::TestCoin();
				delete pGameObj;
			}
		}

	
		if (pGameObj->GetLayerType() == eLayerType::Ground && pGameObj->GetGroundTrap())
		{
			m_pPlayer->GetCurScene()->GetFade()->bInFadeOut();
			
			m_bFadeOut = true;
		}

		

	}

	void PlayerScript::OnCollision(Collider2D* other)
	{
		

		m_fJumpTime = 0.f;

  		GameObject* pGameObj = other->GetOwner();


		if (pGameObj->GetLayerType() == eLayerType::Ground)
		{
			bIsGround = true;
		}



		m_fGameTriggerTime += Time::DeltaTime();

		//Game_Start Collider -> NextScene 구현
		if (pGameObj->GetName() == L"Game_Start")
		{
			if (m_bGameTrigger)
			{

				if (m_fGameTriggerTime >= 1.5f)
				{

					if (b_FirEffect)
					{
						GameStartEffect* Game_Start_Effect = new GameStartEffect();
						Game_Start_Effect->SetName(L"Game_Start_Effect");
						SceneManager::AddGameObject(eLayerType::UI, Game_Start_Effect);
						Game_Start_Effect->GetComponent<Transform>()->SetPosition(Vector3(-5.f, 0.f, 0.5f));
						Game_Start_Effect->GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 0.f));
						m_CreateEffects.push_back(Game_Start_Effect);
						b_FirEffect = false;
					}
				}

				if (m_fGameTriggerTime >= 3.f)
				{

					if (b_SecEffect)
					{
						GameStartEffect* Game_Start_Effect = new GameStartEffect();
						Game_Start_Effect->SetName(L"Game_Start_Effect");
						SceneManager::AddGameObject(eLayerType::UI, Game_Start_Effect);
						Game_Start_Effect->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.5f));
						Game_Start_Effect->GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 0.f));
						m_CreateEffects.push_back(Game_Start_Effect);
						b_SecEffect = false;
					}
				}


				if (m_fGameTriggerTime >= 4.5f)
				{

					if (b_Terffect)
					{
						GameStartEffect* Game_Start_Effect = new GameStartEffect();
						Game_Start_Effect->SetName(L"Game_Start_Effect");
						SceneManager::AddGameObject(eLayerType::UI, Game_Start_Effect);
						Game_Start_Effect->GetComponent<Transform>()->SetPosition(Vector3(5.f, 0.f, 0.5f));
						Game_Start_Effect->GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 0.f));
						m_CreateEffects.push_back(Game_Start_Effect);
						b_Terffect = false;
						
						const float reduction = 0.5f;

						Vector4 color = GetOwner()->GetComponent<Light>()->GetColor();

						color.x -= reduction;
						color.y -= reduction;
						color.z -= reduction;

						GetOwner()->GetComponent<Light>()->SetColor(Vector4(color.x, color.y, color.z, 0.6f));
					

						m_pPlayer->GetCurScene()->GetFade()->bInFadeOut();
					}

					b_SceneChange = true;

					
						if (m_fGameTriggerTime >= 5.f && b_SceneChange == true)
						{
							
							SceneManager::LoadScene(L"StartGame");
						}
				}
			}
		}


		//Bench 회복-> Toggle 방식으로 구현
		if ((pGameObj->GetLayerType() == eLayerType::Trigger && pGameObj->GetComponent<Collider2D>()->GetName() == L"Bench_Trigger") || SceneManager::GetDeadState())
		{
			if (Input::GetKeyDown(eKeyCode::T) || SceneManager::GetDeadState())
			{
				m_bRestToggled = !m_bRestToggled;

				if (m_bRestToggled)
				{
					SceneManager::DeadState(false);
					m_pPlayer->GetComponent<Animator>()->PlayAnimation(L"Knight_idle_f", true);

					m_pPlayer->GetComponent<AudioSource>()->SetClip(Resources::Load<AudioClip>(L"Knight_Rest", L"..\\Resources\\Sound\\bench_rest.mp3"));
					m_pPlayer->GetComponent<AudioSource>()->Play();

					SceneManager::SetBall(10);
					SceneManager::SetHealth(4);

					m_pPlayer->GetHud()->GetHP_Ball()->GetComponent<Animator>()->PlayAnimation(L"HP_Ball_100", false);
					m_pPlayer->GetHud()->GetHP_Ball()->SetLifeCnt(10);
					m_pPlayer->GetHud()->SetHealthCnt(4);
				


					for (auto& Hel : m_pPlayer->GetHud()->GetHUDObj())
					{
						Hel->GetComponent<Animator>()->PlayAnimation(L"Health_Life", true);
					}
					
			

					m_bRest = true;
				}
				else
				{
					m_bRest = false;
				}
			
			}
		}


	}

	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			bIsGround = false;

			//공격받는 상태가아니고 좌우 이동중일 경우 (공격받으면 무조건 공중임)
			if (Input::GetKey(eKeyCode::LEFT) ||
				Input::GetKey(eKeyCode::RIGHT))
			{
				if (!m_bSlowTime)
				{
					SetState(EPlayerState::Jump);
				}
			}
		}



		m_fGameTriggerTime = 0.f;
		
		for (GameStartEffect* effect : m_CreateEffects)
		{
			SceneManager::DestoryObj(effect);
			delete effect;
		}
		m_CreateEffects.clear();
	}

}