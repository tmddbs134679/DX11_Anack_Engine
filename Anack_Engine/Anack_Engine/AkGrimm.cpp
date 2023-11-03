#include "AkGrimm.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkMonsterScript.h"
#include "AkRigidBody.h"
#include "AkIdleState.h"
#include "AkAttackState.h"
#include "AkTraceState.h"
#include "AkDeadState.h"
#include "AkAttackStartState.h"
#include "AkSkill1State.h"
#include "AkSkill2State.h"
#include "AkSkill3State.h"
#include "AkSkill4State.h"
#include "AkSkill5State.h"
#include "AkTime.h"

namespace Ak
{
	Grimm::Grimm()
	{

		SetName(L"Grimm");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"MonsterShader");

#pragma region Grimmtxt

		std::shared_ptr<Texture> Grimm_idle
			= Resources::Load<Texture>(L"Grimm_idle_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_idle2.png");

		std::shared_ptr<Texture> Grimm_start_01
			= Resources::Load<Texture>(L"Grimm_fin_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_stage_open_start.png");

		std::shared_ptr<Texture> Grimm_start_01_02
			= Resources::Load<Texture>(L"Grimm_fin_02_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_stage_open_start_02.png");

		
		std::shared_ptr<Texture> Grimm_start_02
			= Resources::Load<Texture>(L"Grimm_fin_back_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_stage_open_end.png");

	
		std::shared_ptr<Texture> Grimm_start_03
			= Resources::Load<Texture>(L"Grimm_start_03_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_stage_bt_start.png");
		
		std::shared_ptr<Texture> Grimm_Attack_01_start
			= Resources::Load<Texture>(L"Grimm_Attack_01_start_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_attack01_l.png");

		std::shared_ptr<Texture> Grimm_Attack_01_start_r
			= Resources::Load<Texture>(L"Grimm_Attack_01_start_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_attack01_r.png");

		std::shared_ptr<Texture> Grimm_Attack_02_01
			= Resources::Load<Texture>(L"Grimm_Attack_02_01_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack2_01.png");

		std::shared_ptr<Texture> Grimm_Attack_02_02
			= Resources::Load<Texture>(L"Grimm_Attack_02_02_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Attack2_02.png");




		std::shared_ptr<Texture> Grimm_Skill3_start
			= Resources::Load<Texture>(L"Grimm_Skill3_start_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_skill3_start.png");

		std::shared_ptr<Texture> Grimm_Skill3
			= Resources::Load<Texture>(L"Grimm_Skill3_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill03.png");



		std::shared_ptr<Texture> Grimm_Skill4_01
			= Resources::Load<Texture>(L"Grimm_Skill4_01_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill4_01.png");

		std::shared_ptr<Texture> Grimm_Skill4_02
			= Resources::Load<Texture>(L"Grimm_Skill4_02_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill4_02.png");

		std::shared_ptr<Texture> Grimm_Skill4_02_r
			= Resources::Load<Texture>(L"Grimm_Skill4_02_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill4_02_r.png");

		std::shared_ptr<Texture> Grimm_Skill4_03
			= Resources::Load<Texture>(L"Grimm_Skill4_03_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill4_03.png");


		std::shared_ptr<Texture> Grimm_Skill4_03_r
			= Resources::Load<Texture>(L"Grimm_Skill4_03_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill4_03_r.png");

		std::shared_ptr<Texture> Grimm_Dead
			= Resources::Load<Texture>(L"Grimm_Dead_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Dead.png");


		std::shared_ptr<Texture> Grimm_Skill5_01_ready_r
			= Resources::Load<Texture>(L"Grimm_Skill5_01_ready_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_01_ready.png");

		std::shared_ptr<Texture> Grimm_Skill5_01_r
			= Resources::Load<Texture>(L"Grimm_Skill5_01_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_01.png");

		std::shared_ptr<Texture> Grimm_Skill5_02_r
			= Resources::Load<Texture>(L"Grimm_Skill5_02_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_02.png");
		
		std::shared_ptr<Texture> Grimm_Skill5_03_r
			= Resources::Load<Texture>(L"Grimm_Skill5_03_r_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_03.png");


		std::shared_ptr<Texture> Grimm_Skill5_01_ready_l
			= Resources::Load<Texture>(L"Grimm_Skill5_01_ready_l_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_01_l_ready.png");

		std::shared_ptr<Texture> Grimm_Skill5_01_l
			= Resources::Load<Texture>(L"Grimm_Skill5_01_l_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_01_l.png");

		std::shared_ptr<Texture> Grimm_Skill5_02_l
			= Resources::Load<Texture>(L"Grimm_Skill5_02_l_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_02_l.png");

		std::shared_ptr<Texture> Grimm_Skill5_03_l
			= Resources::Load<Texture>(L"Grimm_Skill5_03_l_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\Grimm_Skill5_03_l.png");

		std::shared_ptr<Texture> Grimm_disappear
			= Resources::Load<Texture>(L"Grimm_disappear_txt", L"..\\Resources\\Texture\\Monster\\Grimm\\grimm_disappear.png");


		GetComponent<Transform>()->SetScale(3.f, 6.f, 0.f);
		GetComponent<Collider2D>()->SetSize(Vector2(0.5f, 1.f));


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterMaterial"));


		 mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Grimm_idle", Grimm_idle, Vector2(0.0f, 0.0f), Vector2(198.f, 202.f), 9);

		mAnimator->Create(L"Grimm_start_01", Grimm_start_01, Vector2(0.0f, 0.0f), Vector2(300.f, 246.f), 9);
		mAnimator->Create(L"Grimm_start_01_02", Grimm_start_01_02, Vector2(0.f, 0.0f), Vector2(300.f, 246.f), 1);
		mAnimator->Create(L"Grimm_start_02", Grimm_start_02, Vector2(0.0f, 0.0f), Vector2(300.f, 246.f), 10);
		mAnimator->Create(L"Grimm_start_03", Grimm_start_03, Vector2(0.0f, 0.0f), Vector2(427.f, 300.f), 14);
		mAnimator->Create(L"Grimm_Attack_01_start", Grimm_Attack_01_start, Vector2(0.0f, 0.0f), Vector2(350.f, 270.f), 8);
		mAnimator->Create(L"Grimm_Attack_01_start_r", Grimm_Attack_01_start_r, Vector2(0.0f, 0.0f), Vector2(350.f, 270.f), 8);
		mAnimator->Create(L"Grimm_Attack_02_01", Grimm_Attack_02_01, Vector2(0.0f, 0.0f), Vector2(400.f, 300.f), 6);
		mAnimator->Create(L"Grimm_Attack_02_02", Grimm_Attack_02_02, Vector2(0.0f, 0.0f), Vector2(300.f, 270.f), 6, Vector2::Zero, 0.12f);


		mAnimator->Create(L"Grimm_Skill3_start", Grimm_Skill3_start, Vector2(0.0f, 0.0f), Vector2(300.f, 300.f), 5);
		mAnimator->Create(L"Grimm_Skill3", Grimm_Skill3, Vector2(0.0f, 0.0f), Vector2(300.f, 350.f), 3);
	
		mAnimator->Create(L"Grimm_Skill4_01", Grimm_Skill4_01, Vector2(0.0f, 0.0f), Vector2(300.f, 270.f), 6);
		mAnimator->Create(L"Grimm_Skill4_02", Grimm_Skill4_02, Vector2(0.0f, 0.0f), Vector2(300.f, 240.f), 6);
		mAnimator->Create(L"Grimm_Skill4_02_r", Grimm_Skill4_02_r, Vector2(0.0f, 0.0f), Vector2(300.f, 240.f), 6, Vector2::Zero, 2.f);

		mAnimator->Create(L"Grimm_Skill4_03", Grimm_Skill4_03, Vector2(0.0f, 0.0f), Vector2(300.f, 150.f), 3);
		mAnimator->Create(L"Grimm_Skill4_03_r", Grimm_Skill4_03_r, Vector2(0.0f, 0.0f), Vector2(300.f, 150.f), 3, Vector2::Zero, 2.f);

		mAnimator->Create(L"Grimm_Skill4_03_r", Grimm_Skill4_03_r, Vector2(0.0f, 0.0f), Vector2(300.f, 150.f), 3, Vector2::Zero, 2.f);

		mAnimator->Create(L"Grimm_disappear", Grimm_disappear, Vector2(0.0f, 0.0f), Vector2(285.83f, 340.f), 6);


		mAnimator->Create(L"Grimm_Skill5_01_ready_r", Grimm_Skill5_01_ready_r, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 2);
		mAnimator->Create(L"Grimm_Skill5_01_r", Grimm_Skill5_01_r, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 5);
		mAnimator->Create(L"Grimm_Skill5_02_r", Grimm_Skill5_02_r, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 7);
		mAnimator->Create(L"Grimm_Skill5_03_r", Grimm_Skill5_03_r, Vector2(0.0f, 0.0f), Vector2(350.f, 350.f), 2);


		mAnimator->Create(L"Grimm_Skill5_01_ready_l", Grimm_Skill5_01_ready_l, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 2);
		mAnimator->Create(L"Grimm_Skill5_01_l", Grimm_Skill5_01_l, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 5);
		mAnimator->Create(L"Grimm_Skill5_02_l", Grimm_Skill5_02_l, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 7);
		mAnimator->Create(L"Grimm_Skill5_03_l", Grimm_Skill5_03_l , Vector2(0.0f, 0.0f), Vector2(350.f, 350.f), 2, Vector2::Zero, 2.f);


		mAnimator->Create(L"Grimm_Dead", Grimm_Dead, Vector2(0.0f, 0.0f), Vector2(140.f, 180.f), 1);
		//mAnimator->PlayAnimation(L"Grimm_Attack_01_start", true);


		std::shared_ptr<AudioClip> ac = Resources::Load<AudioClip>(L"GrimmAttack", L"..\\Resources\\Sound\\sword_terrain_temp.mp3");


		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Grimm_fireBall", L"..\\Resources\\Sound\\Grimm_fireball_cast.mp3");
		

		std::shared_ptr<AudioClip> ac3 = Resources::Load<AudioClip>(L"Grimm_dead_voice", L"..\\Resources\\Sound\\Grimm_dead_voice.mp3");

		//ac3->SetSoundDistance(Vector2(1000, 1000));

		std::shared_ptr<AudioClip> ac4 = Resources::Load<AudioClip>(L"grimm_Attack_sharp", L"..\\Resources\\Sound\\grimm_Attack_sharp.mp3");
		std::shared_ptr<AudioClip> ac5 = Resources::Load<AudioClip>(L"Grimm_ball", L"..\\Resources\\Sound\\grimm_balloon_shooting_fireballs_loop.mp3");
		ac5->SetLoop(true);
		std::shared_ptr<AudioClip> ac6 = Resources::Load<AudioClip>(L"Grimm_dis", L"..\\Resources\\Sound\\grimm_teleport_in.mp3");

		m_AudioClips.push_back(ac);
		m_AudioClips.push_back(ac2);
		m_AudioClips.push_back(ac3);
		m_AudioClips.push_back(ac4);
		m_AudioClips.push_back(ac5);
		m_AudioClips.push_back(ac6);

#pragma endregion
	}

	Grimm::~Grimm()
	{

	}

	void Grimm::Initialize()
	{
		RigidBody* rb = GetComponent<RigidBody>();
		rb->SetGravity(Vector2(0, 0));

		MonsterScript* GrimScript = AddComponent<MonsterScript>();


		MonsterInfo bInfo = {};

		bInfo.fAtt = 20.f;
		bInfo.fAttackRange = 3.f;
		bInfo.fDetectRange = 3.f;
		bInfo.iHP_Count = 30;
		bInfo.fSpeed = 1.2f;

		//BaldurScript->SetMonsterInfo(bInfo);
		Monster::SetMonsterInfo(bInfo);




		AI* pGrimmAI = new AI();

		pGrimmAI->SetOwner(this);

		pGrimmAI->AddState(new IdleState());
		pGrimmAI->AddState(new AttackState());
		pGrimmAI->AddState(new AttackStartState());
		pGrimmAI->AddState(new DeadState());
		pGrimmAI->AddState(new TraceState());
		pGrimmAI->AddState(new Skill1State());
		pGrimmAI->AddState(new Skill2State());
		pGrimmAI->AddState(new Skill3State());
		pGrimmAI->AddState(new Skill4State());
		pGrimmAI->AddState(new Skill5State());

		pGrimmAI->SetCurState(eMonsterState::Idle);
		GrimScript->SetAI(pGrimmAI);

		pGrimmAI->Initialize();

	}

	void Grimm::Update()
	{
		Monster::Update();

	}

	void Grimm::LateUpdate()
	{
		Monster::LateUpdate();
	}

	void Grimm::Render()
	{
		Monster::Render();
	}
}