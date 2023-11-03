#include "AkPlayerWeapon.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkAnimator.h"
#include "AkPlayer.h"
#include "AkPlayerAttackScript.h"

namespace Ak
{
	PlayerWeapon::PlayerWeapon()
		: m_pPlayer(nullptr)
	{
		SetName(L"PlayerWeapon");

		MeshRenderer* mr = AddComponent<MeshRenderer>();

		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		AddComponent<PlayerAttackScript>();

	}

	PlayerWeapon::~PlayerWeapon()
	{
		m_pPlayer = nullptr;
	}

	void PlayerWeapon::Initialize()
	{
		GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 0.f));
		Collider2D* cd = AddComponent<Collider2D>();
		cd->SetSize(Vector2(1.f, 0.5f));


		Animator* pAnimator = AddComponent<Animator>();


		std::shared_ptr<Texture> Knight_Attack_effect_r
			= Resources::Load<Texture>(L"Knight_Attack_effect_r", L"..\\Resources\\Texture\\Knight\\Knight_Attack_effect_r.png");

		std::shared_ptr<Texture> Knight_Attack_effect_l
			= Resources::Load<Texture>(L"Knight_Attack_effect_l", L"..\\Resources\\Texture\\Knight\\Knight_Attack_effect_l.png");

		std::shared_ptr<Texture> Knight_Attack_effect_d
			= Resources::Load<Texture>(L"Knight_Attack_effect_d", L"..\\Resources\\Texture\\Knight\\Knight_Attack_effect_d.png");


		pAnimator->Create(L"Knight_Attack_effect_r", Knight_Attack_effect_r, Vector2(0.0f, 0.0f), Vector2(260.f, 150.f), 4, Vector2::Zero, 0.05f);

		pAnimator->Create(L"Knight_Attack_effect_l", Knight_Attack_effect_l, Vector2(0.0f, 0.0f), Vector2(260.0f, 150.f), 4, Vector2::Zero, 0.05f);

		pAnimator->Create(L"Knight_Attack_effect_d", Knight_Attack_effect_d, Vector2(0.0f, 0.0f), Vector2(273.0f, 237.f), 4, Vector2::Zero, 0.05f);

	
		pAnimator->PlayAnimation(L"Knight_Attack_effect_d", true);
		
		GetComponent<PlayerAttackScript>()->SetPlayerWeapon(this);
	}

	void PlayerWeapon::Update()
	{
		GameObject::Update();
	}

	void PlayerWeapon::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void PlayerWeapon::Render()
	{
		GameObject::Render();
	}
}
