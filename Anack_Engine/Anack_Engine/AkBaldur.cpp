#include "AkBaldur.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkResources.h"
#include "AkMonsterScript.h"
#include "AkRigidBody.h"
#include "AkMonster.h"
#include "AkIdleState.h"
#include "AkAttackState.h"
#include "AkDeadState.h"
#include "AkTraceState.h"
#include "AkResources.h"
#include "AkLight.h"
#include "AkGroundScript.h"
#include "AkAttackStartState.h"

namespace Ak
{
	Baldur::Baldur()
	{
		SetName(L"Baldur");


#pragma region Text

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"MonsterShader");

		std::shared_ptr<Texture> BaldurIdle_l
			= Resources::Load<Texture>(L"Baldur_idle_l_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_idle_l.png");

		std::shared_ptr<Texture> BaldurIdle_r
			= Resources::Load<Texture>(L"Baldur_idle_r_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_idle_r.png");

		std::shared_ptr<Texture> BaldurAttackStart_l
			= Resources::Load<Texture>(L"Baldur_Attack_Start_l_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_Attack_start_l.png");

		std::shared_ptr<Texture> BaldurAttackStart_r
			= Resources::Load<Texture>(L"Baldur_Attack_Start_r_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_Attack_Start_r.png");

		std::shared_ptr<Texture> BaldurAttack
			= Resources::Load<Texture>(L"Baldur_Attack_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_Attak.png");

		std::shared_ptr<Texture> BaldurDeadL
			= Resources::Load<Texture>(L"Baldur_dead_l_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_dead_l.png");

		std::shared_ptr<Texture> BaldurDeadR
			= Resources::Load<Texture>(L"Baldur_dead_r_txt", L"..\\Resources\\Texture\\Monster\\Baldur\\Baldur_dead_r.png");

#pragma endregion



		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterMaterial"));



		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Baldur_idle_l", BaldurIdle_l, Vector2(0.0f, 0.0f), Vector2(145.0f, 70.f), 1);
		mAnimator->Create(L"Baldur_idle_r", BaldurIdle_r, Vector2(0.0f, 0.0f), Vector2(145.0f, 70.f), 1);

		mAnimator->Create(L"Baldur_Attack_start_l", BaldurAttackStart_l, Vector2(0.0f, 0.0f), Vector2(161.0f, 117.f), 7);
		mAnimator->Create(L"Baldur_Attack_start_r", BaldurAttackStart_r, Vector2(0.0f, 0.0f), Vector2(160.0f, 117.f), 7);

		mAnimator->Create(L"Baldur_Attack", BaldurAttack, Vector2(0.0f, 0.0f), Vector2(90.0f, 80.f), 4,Vector2::Zero, 0.04f);

		mAnimator->Create(L"Baldur_dead_l", BaldurDeadL, Vector2(0.0f, 0.0f), Vector2(155.0f, 118.f), 4);
		mAnimator->Create(L"Baldur_dead_r", BaldurDeadR, Vector2(0.0f, 0.0f), Vector2(155.0f, 118.f), 4);

		mAnimator->PlayAnimation(L"Baldur_idle_l", true);


	}

	Baldur::~Baldur()
	{

	}

	void Baldur::Initialize()
	{
		

		MonsterScript* BaldurScript = AddComponent<MonsterScript>();

	
	
		RigidBody* rb = GetComponent<RigidBody>();
		rb->SetMass(10.f);
		//rb->SetGravity(Vector2(0, -60.f));

		GetComponent<Transform>()->SetPosition(3.f, 3.f, 0.99f);
		GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);
		GetComponent<Collider2D>()->SetSize(Vector2(0.7f, 0.3f));


		MonsterInfo bInfo = {};
		
		bInfo.fAtt = 20.f;
		bInfo.fAttackRange = 8.f;
		bInfo.fDetectRange = 8.f;
		bInfo.iHP_Count = 2;
		bInfo.fSpeed = 1.2f;

		//BaldurScript->SetMonsterInfo(bInfo);
		Monster::SetMonsterInfo(bInfo);

	


		AI* pBaldurAI = new AI();

		pBaldurAI->SetOwner(this);
		
		pBaldurAI->AddState(new IdleState());
		pBaldurAI->AddState(new AttackState());
		pBaldurAI->AddState(new AttackStartState());
		pBaldurAI->AddState(new DeadState());
		pBaldurAI->AddState(new TraceState());


		pBaldurAI->SetCurState(eMonsterState::Idle);
		BaldurScript->SetAI(pBaldurAI);

		pBaldurAI->Initialize();




	}

	void Baldur::Update()
	{
		Monster::Update();
	}

	void Baldur::LateUpdate()
	{
		Monster::LateUpdate();
	}

	void Baldur::Render()
	{
		Monster::Render();
	}

}
