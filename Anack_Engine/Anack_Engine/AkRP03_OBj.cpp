#include "AkRP03_OBj.h"
#include "AkTime.h"
#include "AkSceneManager.h"

Ak::RP03_OBj::RP03_OBj()
	: m_fTime(0.f)
	, m_bAttack(false)
	, m_iPosX(0)

{
	
}

Ak::RP03_OBj::~RP03_OBj()
{
	SceneManager::DestoryObj(this);

	for (const auto& test : m_vRP)
	{
		SceneManager::DestoryObj(test);
		delete test;
		
	}

	m_vRP.clear();

}

void Ak::RP03_OBj::Initialize()
{
	m_EPattern = RP03Pattern::pattern01;

	Radiance_Projectile_03* RP01 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP02 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP03 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP04 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP05 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP06 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP07 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP08 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP09 = new Radiance_Projectile_03();

	Radiance_Projectile_03* RP10 = new Radiance_Projectile_03();


	
	m_vRP.push_back(RP01);
	m_vRP.push_back(RP02);
	m_vRP.push_back(RP03);
	m_vRP.push_back(RP04);
	m_vRP.push_back(RP05);
	m_vRP.push_back(RP06);
	m_vRP.push_back(RP07);
	m_vRP.push_back(RP08);
	m_vRP.push_back(RP09);
	m_vRP.push_back(RP10);
	


	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP01);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP02);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP03);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP04);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP05);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP06);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP07);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP08);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP09);
	SceneManager::AddGameObject(eLayerType::MonsterAttack, RP10);

}

void Ak::RP03_OBj::Update()
{
	
	for (const auto& test : m_vRP)
	{
		if (test != nullptr)
		{
			if (test->Dis())
			{
				ChangePattern();
				test->DisOff();
				
			}
		}
		test->AttackOn();

	}
	

	GameObject::Update();
}

void Ak::RP03_OBj::LateUpdate()
{
	GameObject::LateUpdate();
}

void Ak::RP03_OBj::Render()
{
	GameObject::Render();
}

void Ak::RP03_OBj::ChangePattern()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// 무작위로 선택할 수 있는 열거형 멤버 개수 계산
	const int numPatterns = 3; // 열거형 멤버 개수

	// 무작위로 패턴 선택
	RP03Pattern randomPattern = static_cast<RP03Pattern>(1 + std::rand() % numPatterns);


	m_EPattern = randomPattern;

	switch (m_EPattern)
	{
	case Ak::RP03_OBj::pattern01:

		m_iPosX = 0;
		for (int i = 0; i < 10; ++i)
		{
			
			m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_iPosX + i, -2.2f, 1.f));
		}

		break;

	case Ak::RP03_OBj::pattern02:

		m_iPosX = -9;
		for (int i = 0; i < 10; ++i)
		{
			m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_iPosX + i, -2.2f, 1.f));
		}

		break;

	case Ak::RP03_OBj::pattern03:

		m_iPosX = -9;
		for (int i = 0; i < 10; ++i)
		{
			if (i >= 5)
			{
				m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_iPosX + i + 9, -2.2f, 1.f));
			}
			else
			{
				m_vRP[i]->GetComponent<Transform>()->SetPosition(Vector3(m_iPosX + i, -2.2f, 1.f));
			}

			
		}

		break;

	default:
		break;
	}



	
}

void Ak::RP03_OBj::Random()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(1, 3); 
	// 1, 2, 3 중 하나를 랜덤으로 선택

	int randomNumber = distribution(gen);

	// randomNumber에 따라 패턴을 설정
	switch (randomNumber)
	{
	case 1:
		m_EPattern = RP03Pattern::pattern01;
		break;
	case 2:
		m_EPattern = RP03Pattern::pattern02;
		break;
	case 3:
		m_EPattern = RP03Pattern::pattern03;
		break;
	default:
		// 예외 처리 또는 기본값 설정
		break;
	}

}
