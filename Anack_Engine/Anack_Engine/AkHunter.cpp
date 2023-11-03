#include "AkHunter.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkResources.h"
#include "AkMonsterScript.h"
#include "AkRigidBody.h"

#include "AkIdleState.h"
#include "AkAttackState.h"
#include "AkAttackStartState.h"
#include "AkDeadState.h"
#include "AkTraceState.h"
#include "AkRenderer.h"

namespace Ak
{
	Hunter::Hunter()
	{
		SetName(L"Hunter");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"MonsterShader");

#pragma region Huntertxt

		std::shared_ptr<Texture> HunterPatrol_l
			= Resources::Load<Texture>(L"Hunter_Patrol_l_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_patrol_l.png");

		std::shared_ptr<Texture> HunterPatrol_r
			= Resources::Load<Texture>(L"Hunter_Patrol_r_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_patrol_r.png");

		std::shared_ptr<Texture> HunterDetect_l
			= Resources::Load<Texture>(L"Hunter_Detect_l_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_detect_l.png");

		std::shared_ptr<Texture> HunterDetect_r
			= Resources::Load<Texture>(L"Hunter_Detect_r_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_detect_r.png");

		std::shared_ptr<Texture> HunterAttack_l
			= Resources::Load<Texture>(L"Hunter_Attack_l_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_Attack_l.png");

		std::shared_ptr<Texture> HunterAttack_r
			= Resources::Load<Texture>(L"Hunter_Attack_r_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_Attack_r.png");

		std::shared_ptr<Texture> HunterDead_l
			= Resources::Load<Texture>(L"Hunter_Dead_l_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_dead_l.png");

		std::shared_ptr<Texture> HunterDead_r
			= Resources::Load<Texture>(L"Hunter_Dead_r_txt", L"..\\Resources\\Texture\\Monster\\Hunter\\Hunter_dead_r.png");
#pragma endregion

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterMaterial"));


		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Hunter_Patrol_l", HunterPatrol_l, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);
		mAnimator->Create(L"Hunter_Patrol_r", HunterPatrol_r, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);

		mAnimator->Create(L"Hunter_Detect_l", HunterDetect_l, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);
		mAnimator->Create(L"Hunter_Detect_r", HunterDetect_r, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);

		mAnimator->Create(L"Hunter_Attack_l", HunterAttack_l, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);
		mAnimator->Create(L"Hunter_Attack_r", HunterAttack_r, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);

		mAnimator->Create(L"Hunter_Dead_l", HunterDead_l, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);
		mAnimator->Create(L"Hunter_Dead_r", HunterDead_r, Vector2(0.0f, 0.0f), Vector2(150.0f, 130.f), 4);

		mAnimator->PlayAnimation(L"Hunter_Patrol_l", true);
		


		RigidBody* rb = GetComponent<RigidBody>();
		rb->SetGravity(Vector2(0, 0));

		std::shared_ptr<AudioClip> ac = Resources::Load<AudioClip>(L"HunterDeath", L"..\\Resources\\Sound\\enemy death sword.mp3");
		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Hunter_Trace", L"..\\Resources\\Sound\\Hunter_Trace.mp3");
		
		std::shared_ptr<AudioClip> ac3 = Resources::Load<AudioClip>(L"Hunter_Fly", L"..\\Resources\\Sound\\Hunter_Fly.mp3");

		std::shared_ptr<AudioClip> ac4 = Resources::Load<AudioClip>(L"Hunter_Dead", L"..\\Resources\\Sound\\Hunter_Dead.mp3");

		m_AudioClips.push_back(ac);
		m_AudioClips.push_back(ac2);
		m_AudioClips.push_back(ac3);
		m_AudioClips.push_back(ac4);

	}

	Hunter::~Hunter()
	{

	}

	void Hunter::Initialize()
	{
		Monster::Initialize();



		MonsterInfo bInfo = {};

		bInfo.fAtt = 20.f;
		bInfo.fAttackRange = 1.f;
		bInfo.fDetectRange = 3.f;
		bInfo.iHP_Count = 4;
		bInfo.fSpeed = 0.6f;

		//m_pAI->GetOwner()->SetMonsterInfo(bInfo);
		Monster::SetMonsterInfo(bInfo);


		MonsterScript* HunterScript = AddComponent<MonsterScript>();
		//HunterScript->SetMonsterInfo(bInfo);

		GetComponent<Transform>()->SetPosition(3.f, 3.f, 0.99f);
		GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);

		Collider2D* cd = GetComponent<Collider2D>();
		//cd->SetSize(Vector2(0.5f, 0.5f));

		pHunterAI  = new AI();

		pHunterAI->SetOwner(this);

		pHunterAI->AddState(new IdleState());
		pHunterAI->AddState(new AttackState());
		pHunterAI->AddState(new AttackStartState());
		pHunterAI->AddState(new DeadState());
		pHunterAI->AddState(new TraceState());

		pHunterAI->SetCurState(eMonsterState::Idle);
		HunterScript->SetAI(pHunterAI);

		pHunterAI->Initialize();


	}

	void Hunter::Update()
	{
		
		
		Monster::Update();
		

	}

	void Hunter::LateUpdate()
	{
		
		Monster::LateUpdate();
	}

	void Hunter::Render()
	{

		Monster::Render();
	}

}
