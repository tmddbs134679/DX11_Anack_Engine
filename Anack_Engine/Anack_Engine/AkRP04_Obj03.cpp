#include "AkRP04_Obj03.h"
#include "AkSceneManager.h"
#include "AkTime.h"


namespace Ak
{
	RP04_Obj03::RP04_Obj03()
		: m_bChRot(true)
		, m_bAttack(true)
	{

	}

	RP04_Obj03::~RP04_Obj03()
	{
		SceneManager::DestoryObj(this);

		SceneManager::DestoryObj(m_RP);
		delete m_RP;
		m_RP = nullptr;


	}

	void RP04_Obj03::Initialize()
	{
		
  		m_RP = new Radiance_Projectile_04();
		m_RP->GetComponent<Transform>()->SetScale(Vector3(4.f, 100.f, 1.f));
		
		SceneManager::AddGameObject(eLayerType::MonsterAttack, m_RP);
	

	}

	void RP04_Obj03::Update()
	{
		
		if (m_RP != nullptr)
		{
			if (m_bAttack)
			{
				if (m_bChRot)
				{
					float rotz = Random();
					GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, rotz));
					m_bChRot = false;
				}

				//위치고정
				Vector3 monpos = m_Owner->GetComponent<Transform>()->GetPosition();
				Vector3 rot = GetComponent<Transform>()->GetRotation();


				m_RP->GetComponent<Transform>()->SetPosition(Vector3(monpos.x, monpos.y - 41.f, 1.3f));
				m_RP->GetComponent<Transform>()->SetRotation(Vector3(rot));

				static float fTime = 0.f;

				fTime += Time::DeltaTime();

				if (fTime <= 0.3f)
				{
					if (!(m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_ready"))
						m_RP->GetComponent<Animator>()->PlayAnimation(L"attack04_ready", false);

				}
				else if (fTime > 0.3f && fTime <= 0.6f)
				{
					if (!(m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_set"))
					{
						m_RP->GetComponent<Animator>()->PlayAnimation(L"attack04_set", true);
						m_RP->GetAC()[0]->Play();
					}
				}
				else if (fTime > 0.6f && fTime <= 0.9f)
				{
					if (!(m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_beam"))
					{
						m_RP->GetComponent<Animator>()->PlayAnimation(L"attack04_beam", true);

						m_RP->GetAC()[1]->Play();
					}

				}
				else if (fTime > 0.9f && fTime <= 1.3f)
				{
					if (!(m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"))
						m_RP->GetComponent<Animator>()->PlayAnimation(L"attack04_dis", false);
				}
				else if (m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"
					&& m_RP->GetComponent<Animator>()->GetAnimation()->isComplete())
				{
					fTime = 0.f;
					m_bChRot = true;
				}
			}
			else
			{
				if (!(m_RP->GetComponent<Animator>()->GetPlayAnimationName() == L"attack04_dis"))
					m_RP->GetComponent<Animator>()->PlayAnimation(L"attack04_dis", false);
			}
			
		}

		GameObject::Update();
	}

	void RP04_Obj03::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RP04_Obj03::Render()
	{
		GameObject::Render();
	}

	float RP04_Obj03::Random()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(-0.2f, 0.2f);

		float randomValue = dis(gen);
		GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, randomValue));
		
		return randomValue;
	}

}