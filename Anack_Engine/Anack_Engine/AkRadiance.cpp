#include "AkRadiance.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkMonsterScript.h"
#include "AkRigidBody.h"
#include "AkSceneManager.h"
#include "AkTime.h"
#include "AkAttackState.h"
#include "AkTraceState.h"
#include "AkDeadState.h"
#include "AkAttackStartState.h"
#include "AkSkill1State.h"
#include "AkSkill2State.h"
#include "AkSkill3State.h"
#include "AkSkill4State.h"
#include "AkSkill5State.h"
#include "AkIdleState.h"


namespace Ak
{
	Radiance::Radiance()
		: m_bDisAnim(true)
	{

		SetName(L"Radiance");

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"MonsterShader");

		std::shared_ptr<Texture> Radiance_start
			= Resources::Load<Texture>(L"Radiance_start_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_start.png");

		std::shared_ptr<Texture> Radiance_start2
			= Resources::Load<Texture>(L"Radiance_start2_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_start2.png");

		std::shared_ptr<Texture> Radiance_dis
			= Resources::Load<Texture>(L"Radiance_dis_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_dis.png");

		std::shared_ptr<Texture> Radiance_attack

			= Resources::Load<Texture>(L"Radiance_attack_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack.png");

		std::shared_ptr<Texture> Radiance_test
			= Resources::Load<Texture>(L"Radiance_test_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\test.png");

		std::shared_ptr<Texture> Radiance_lie
			= Resources::Load<Texture>(L"Radiance_lie_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_lie.png");

		std::shared_ptr<Texture> Radiance_Dead
			= Resources::Load<Texture>(L"Radiance_Dead_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_dead.png");

		GetComponent<Transform>()->SetScale(14.f, 14.f, 0.f);
		GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.3f));
		GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 1.f));


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MonsterMaterial"));


		mAnimator = AddComponent<Animator>();

		mAnimator->SetMulSize(5);

		mAnimator->Create(L"Radiance_start", Radiance_start, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 4);
		mAnimator->Create(L"Radiance_start2", Radiance_start2, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 10);
		mAnimator->Create(L"Radiance_dis", Radiance_dis, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 10);
		mAnimator->Create(L"Radiance_attack", Radiance_attack, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 6);
		mAnimator->Create(L"Radiance_lie", Radiance_lie, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 5);
		mAnimator->Create(L"Radiance_Dead", Radiance_Dead, Vector2(0.0f, 0.0f), Vector2(800.f, 900.f), 2);


		mAnimator->Create(L"Radiance_test", Radiance_test, Vector2(0.0f, 0.0f), Vector2(750.f, 900.f), 1);


		RigidBody* rb = GetComponent<RigidBody>();
		rb->SetGravity(Vector2(0, 0));

		mAnimator->PlayAnimation(L"Radiance_start", true);


		m_Radiance_partcile = new GameObject();

		MeshRenderer* mr_radiance_gd = m_Radiance_partcile->AddComponent<MeshRenderer>();
		mr_radiance_gd->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_gd->SetMaterial(Resources::Find<Material>(L"radiance_test"));
		m_Radiance_partcile->GetComponent<Transform>()->SetPosition(Vector3(-5.5f, 15.2f, 1.31f));
		m_Radiance_partcile->GetComponent<Transform>()->SetScale(Vector3(20.f, 20.f, 20.f));
		SceneManager::AddGameObject(eLayerType::LayeredObj, m_Radiance_partcile);


		std::shared_ptr<AudioClip> ac = Resources::Load<AudioClip>(L"Radiance_Attack01", L"..\\Resources\\Sound\\Radiance\\radiance_sword_shoot.mp3");
		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Radiance_Attack02", L"..\\Resources\\Sound\\Radiance\\radiance_sword_create_circular.mp3");
		std::shared_ptr<AudioClip> ac3 = Resources::Load<AudioClip>(L"Radiance_Attack04_pre", L"..\\Resources\\Sound\\Radiance\\radiance_laser_prepare.mp3");
		std::shared_ptr<AudioClip> ac4 = Resources::Load<AudioClip>(L"Radiance_Attack04_lazer", L"..\\Resources\\Sound\\Radiance\\radiance_laser_burst.mp3");
		std::shared_ptr<AudioClip> ac5 = Resources::Load<AudioClip>(L"Radiance_Scream", L"..\\Resources\\Sound\\Radiance\\radiance_scream_long.mp3");
		std::shared_ptr<AudioClip> ac6 = Resources::Load<AudioClip>(L"Radiance_Scream_short", L"..\\Resources\\Sound\\Radiance\\radiance_scream_short.mp3");
		std::shared_ptr<AudioClip> ac7 = Resources::Load<AudioClip>(L"Radiance_final_hit", L"..\\Resources\\Sound\\Radiance\\radiance_final_hit.mp3");
		std::shared_ptr<AudioClip> ac8 = Resources::Load<AudioClip>(L"radiance_teleport", L"..\\Resources\\Sound\\Radiance\\radiance_teleport.mp3");
		std::shared_ptr<AudioClip> ac9 = Resources::Load<AudioClip>(L"radiance_dead", L"..\\Resources\\Sound\\Radiance\\Radiance_Dead.mp3");

		m_AudioClips.push_back(ac);
		m_AudioClips.push_back(ac2);
		m_AudioClips.push_back(ac3);
		m_AudioClips.push_back(ac4);
		m_AudioClips.push_back(ac5);
		m_AudioClips.push_back(ac6);
		m_AudioClips.push_back(ac7);
		m_AudioClips.push_back(ac8);
		m_AudioClips.push_back(ac9);
	}

	Radiance::~Radiance()
	{
		SceneManager::DestoryObj(m_Radiance_partcile);
		delete m_Radiance_partcile;

	}

	void Radiance::Initialize()
	{

		MonsterScript* RadianceScript = AddComponent<MonsterScript>();


		MonsterInfo bInfo = {};

		bInfo.fAtt = 20.f;
		bInfo.fAttackRange = 3.f;
		bInfo.fDetectRange = 3.f;
		bInfo.iHP_Count = 100;
		bInfo.fSpeed = 1.2f;

		//BaldurScript->SetMonsterInfo(bInfo);
		Monster::SetMonsterInfo(bInfo);

		pRadianceAI = new AI();

		pRadianceAI->SetOwner(this);

		pRadianceAI->AddState(new IdleState());
		pRadianceAI->AddState(new AttackState());
		pRadianceAI->AddState(new AttackStartState());
		pRadianceAI->AddState(new DeadState());
		pRadianceAI->AddState(new TraceState());
		pRadianceAI->AddState(new Skill1State());
		pRadianceAI->AddState(new Skill2State());
		pRadianceAI->AddState(new Skill3State());
		pRadianceAI->AddState(new Skill4State());
		pRadianceAI->AddState(new Skill5State());

		pRadianceAI->SetCurState(eMonsterState::Idle);
		RadianceScript->SetAI(pRadianceAI);

		pRadianceAI->Initialize();

		

	}

	void Radiance::Update()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		static float Dt = 0.f;
		Dt += Time::DeltaTime();

		m_Radiance_partcile->GetComponent<Transform>()->SetPositionXY(Vector2(pos.x, pos.y + 2.f));
		m_Radiance_partcile->GetComponent<Transform>()->SetRotation(Vector3(0, 0, Dt / 2));


		if (m_bDisAnim)
		{
			if (mAnimator->GetPlayAnimationName() == L"Radiance_dis")
			{
				m_AudioClips[7]->Play();
				m_bDisAnim = false;
			}
		}
	

		if (mAnimator->GetPlayAnimationName() == L"Radiance_attack")
		{
			GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.3f));
			GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 1.f));

				m_bDisAnim = true;
		
		}


		if (mAnimator->GetPlayAnimationName() == L"Radiance_lie")
		{
			GetComponent<Collider2D>()->SetSize(Vector2(0.5, 0.5));
			GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.f));
		}


		Monster::Update();
	}

	void Radiance::LateUpdate()
	{
		Monster::LateUpdate();
	}

	void Radiance::Render()
	{
		Monster::Render();
	}

}