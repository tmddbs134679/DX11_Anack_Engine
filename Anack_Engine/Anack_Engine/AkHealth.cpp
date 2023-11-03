#include "AkHealth.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMeshRenderer.h"
#include "AkAnimator.h"
#include "AkLight.h"
#include "AkRenderer.h"


namespace Ak
{
	Health::Health()
		: m_bUI(true)
	{
		SetName(L"Health");

		std::shared_ptr<Texture> Health_Life
			= Resources::Load<Texture>(L"Health_Life_txt", L"..\\Resources\\Texture\\HUD.png");

		std::shared_ptr<Texture> Health_broken
			= Resources::Load<Texture>(L"Health_broken_txt", L"..\\Resources\\Texture\\HUD_broke.png");

		std::shared_ptr<Texture> Health_Add
			= Resources::Load<Texture>(L"Health_Add_txt", L"..\\Resources\\Texture\\HUB_ADD.png");

		std::shared_ptr<Texture> Health_Empty
			= Resources::Load<Texture>(L"Health_Empty_txt", L"..\\Resources\\Texture\\HUD_Empty.png");
		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 0.f));

		//Light* light = AddComponent<Light>();
		//light->SetColor(Vector4(0.8f, 0.8f, 0.8f,0.6f));
		//light->SetType(eLightType::Point);



		mAnimator = AddComponent<Animator>();

		mAnimator->Create(L"Health_Life", Health_Life, Vector2(0.0f, 0.0f), Vector2(80.0f, 90.f), 10);
		mAnimator->Create(L"Health_broken", Health_broken, Vector2(0.0f, 0.0f), Vector2(80.0f, 160.f), 6);
		mAnimator->Create(L"Health_Add", Health_Add, Vector2(0.0f, 0.0f), Vector2(80.0f, 90.f), 5);
		mAnimator->Create(L"Health_Empty", Health_Empty, Vector2(0.0f, 0.0f), Vector2(80.f, 90.f), 1);

		mAnimator->PlayAnimation(L"Health_Life", true );

	}

	Health::~Health()
	{
		GameObject::~GameObject();
	}

	void Health::Initialize()
	{

	}

	void Health::Update()
	{
		//추가되면 Life Anim으로 변경
		if (mAnimator->GetPlayAnimationName() == L"Health_Add")
		{
			if (mAnimator->GetAnimation()->isComplete())
			{
				mAnimator->PlayAnimation(L"Health_Life", true);
			}
		}
		GameObject::Update();
	}

	void Health::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Health::Render()
	{
		GameObject::Render();

		renderer::AnimatorCB AnimatorCB;
		AnimatorCB.bUI = m_bUI;


		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&AnimatorCB);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}