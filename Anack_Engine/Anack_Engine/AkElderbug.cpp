#include "AkElderbug.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkNPCScript.h"
#include "AkAudioSource.h"



namespace Ak
{
	Elderbug::Elderbug()
	{
		SetName(L"Elderbug");


		std::shared_ptr<Texture> Elderbug_idle_r
			= Resources::Load<Texture>(L"Elderbug_idle_r_txt", L"..\\Resources\\Texture\\NPC\\Elderbug\\Elderbug_idle_r.png");

		std::shared_ptr<Texture> Elderbug_idle_l
			= Resources::Load<Texture>(L"Elderbug_idle_l_txt", L"..\\Resources\\Texture\\NPC\\Elderbug\\Elderbug_idle_l.png");



		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(3.f, -2.7f, 1.01f));
		tr->SetScale(3.f, 3.f, 0.f);



		Collider2D* cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(5.f, 1.f));
		


		Animator* mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Elderbug_idle_r", Elderbug_idle_r, Vector2(0.0f, 0.0f), Vector2(110.f, 170.f), 4, Vector2::Zero, 1.f);
		mAnimator->Create(L"Elderbug_idle_l", Elderbug_idle_l, Vector2(0.0f, 0.0f), Vector2(113.f, 170.f), 3, Vector2::Zero, 1.f);

		mAnimator->PlayAnimation(L"Elderbug_idle_r", true);

	
		AddComponent<AudioSource>();

		std::shared_ptr<AudioClip> ac1 = Resources::Load<AudioClip>(L"Elderbug01", L"..\\Resources\\Sound\\Elderbug 01.mp3");
		std::shared_ptr<AudioClip> ac2 = Resources::Load<AudioClip>(L"Elderbug01", L"..\\Resources\\Sound\\Elderbug 02.mp3");
		std::shared_ptr<AudioClip> ac3 = Resources::Load<AudioClip>(L"Elderbug01", L"..\\Resources\\Sound\\Elderbug 03.mp3");
		std::shared_ptr<AudioClip> ac4 = Resources::Load<AudioClip>(L"Elderbug01", L"..\\Resources\\Sound\\Elderbug 04.mp3");
		std::shared_ptr<AudioClip> ac5 = Resources::Load<AudioClip>(L"Elderbug01", L"..\\Resources\\Sound\\Elderbug 05.mp3");

		m_vAC.push_back(ac1);
		m_vAC.push_back(ac2);
		m_vAC.push_back(ac3);
		m_vAC.push_back(ac4);
		m_vAC.push_back(ac5);


		NPCScript* ns = AddComponent<NPCScript>();
		ns->SetNPC(this);

	}

	Elderbug::~Elderbug()
	{

	}

	void Elderbug::Initialize()
	{

	}

	void Elderbug::Update()
	{
		GameObject::Update();
	}

	void Elderbug::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Elderbug::Render()
	{
		GameObject::Render();
	}
}