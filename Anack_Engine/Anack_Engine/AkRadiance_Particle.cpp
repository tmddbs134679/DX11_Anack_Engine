#include "AkRadiance_Particle.h"
#include "AkTexture.h"
#include "AkResources.h"
#include "AkMaterial.h"
#include "AkSceneManager.h"
#include "AkMeshRenderer.h"

namespace Ak
{
	Radiance_Particle::Radiance_Particle()
	{

		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");


		std::shared_ptr<Texture> Radiance_particle
			= Resources::Load<Texture>(L"Radiance_particle_txt", L"..\\Resources\\Texture\\Monster\\Radiance_particle.png");

		std::shared_ptr<Material> Radicane_mr_particle = std::make_shared<Material>();
		Radicane_mr_particle->SetShader(shader);
		Radicane_mr_particle->SetTexture(Radiance_particle);
		Radicane_mr_particle->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radicane_mr_particle", Radicane_mr_particle);


		MeshRenderer* mr_radiance_pr = AddComponent<MeshRenderer>();
		mr_radiance_pr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr_radiance_pr->SetMaterial(Resources::Find<Material>(L"Radicane_mr_particle"));
	}

	Radiance_Particle::~Radiance_Particle()
	{


	}

	void Radiance_Particle::Initialize()
	{
		GetComponent<Transform>()->SetScale(Vector3(5.f, 5.f, 0.f));
		//SceneManager::AddGameObject(eLayerType::LayeredObj, this);
	}

	void Radiance_Particle::Update()
	{
		GameObject::Update();
	}

	void Radiance_Particle::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Radiance_Particle::Render()
	{
		GameObject::Render();
	}
}