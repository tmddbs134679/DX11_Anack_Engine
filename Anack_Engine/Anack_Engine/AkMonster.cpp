#include "AkMonster.h"
#include "AkRenderer.h"
#include "AkSceneManager.h"
#include "AkRigidBody.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkAI.h"
#include "AkRenderer.h"
#include "AkTime.h"
#include "AkAudioSource.h"

namespace Ak
{
	Monster::Monster()
		: m_MonsterInfo{}
		, m_eMonsterState(eMonsterState::Idle)
		, m_pCurScene(nullptr)
		, m_iMonsterDirX(0)
		, m_iMonsterDirY(0)
		, m_gBossBG(nullptr)
		, bDamage(false)
		, m_fDamageTime(0.f)
	{	

		AddComponent<Collider2D>();
		AddComponent<RigidBody>();
		AddComponent<AudioSource>();

	}

	Monster::~Monster()
	{
		if (m_pAI != nullptr)
			delete m_pAI;

		m_pCurScene->MinusMonsterCnt();
		SceneManager::DestoryObj(this);
	}

	void Monster::Initialize()
	{
		
	
	}

	void Monster::Update()
	{
		
		
		GameObject::Update();
	}

	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Monster::Render()
	{
		
		MonsterCB.bTest = bDamage;


		if (bDamage)
		{
			
			m_fDamageTime += Time::DeltaTime();

			if (m_fDamageTime <= 0.2f)
			{
				ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
				pConstantBuffer->SetData(&MonsterCB);
				pConstantBuffer->Bind(eShaderStage::PS);
			}
			else
			{
				bDamage = false;
				m_fDamageTime = 0.f;
			}
		}

		ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		pConstantBuffer->SetData(&MonsterCB);
		pConstantBuffer->Bind(eShaderStage::PS);


		
		GameObject::Render();
	}



}
