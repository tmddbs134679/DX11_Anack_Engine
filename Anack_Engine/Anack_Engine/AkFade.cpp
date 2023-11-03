#include "AkFade.h"
#include "AkShader.h"
#include "AkMeshRenderer.h"
#include "AkResources.h"
#include "AkTime.h"

namespace Ak
{
	Fade::Fade()
		: c_bFadein(false)
		, c_fcolorz(1.f)
		, m_fFadeTime(0.f)
		, m_fWaitTime(0.f)
		, m_fFadeOutTime(0.f)
		, m_bFadein(true)
		, m_bFadeOut(false)
	{

		std::shared_ptr<Shader> fadeShader
			= Resources::Find<Shader>(L"FadeShader");

		std::shared_ptr<Texture> Fade
			= Resources::Load<Texture>(L"Fadetxt", L"..\\Resources\\Texture\\Fade.png");


		std::shared_ptr<Material> Fade01 = std::make_shared<Material>();
		Fade01->SetShader(fadeShader);
		Fade01->SetTexture(Fade);
		Resources::Insert(L"Fade01", Fade01);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));


		GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.7f));
		GetComponent<Transform>()->SetScale(Vector3(100.f, 100.f, 0.f));

	}

	Fade::~Fade()
	{

	}

	void Fade::Initialize()
	{
		m_fFadeTime = 0.f;
		m_fWaitTime = 0.f;
	}

	void Fade::Update()
	{
		GameObject::Update();

	
	}

	void Fade::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Fade::Render()
	{

			if (m_bFadein)
			{
				float duration = 3.f;
				m_fFadeTime += Time::DeltaTime();


				if (m_fFadeTime <= duration)
				{

					c_fcolorz = 1.f - (m_fFadeTime / duration);


					FadeCB.bFadeIn = c_bFadein;
					FadeCB.fcolorz = c_fcolorz;

					ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Fade];
					pConstantBuffer->SetData(&FadeCB);
					pConstantBuffer->Bind(eShaderStage::PS);
				}
				else
				{
					m_bFadein = false;
				}
			}
			else
			{
				c_fcolorz = 0.f;
				m_fFadeTime = 0.f;
				m_bFadein = false;
			}

			if (m_bFadeOut)
			{
				
				m_fFadeOutTime += Time::DeltaTime();
				float Outduration = 1.f;

				if (m_fFadeOutTime <= Outduration)
				{
					c_fcolorz = (m_fFadeOutTime / Outduration);


					FadeCB.bFadeIn = c_bFadein;
					FadeCB.fcolorz = c_fcolorz;

					ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Fade];
					pConstantBuffer->SetData(&FadeCB);
					pConstantBuffer->Bind(eShaderStage::PS);
				}
				else
				{
					m_bFadeOut = false;
				}

			
			}
		
			if (m_test)
			{
				FadeCB.bFadeIn = c_bFadein;
				FadeCB.fcolorz = 1;


				ConstantBuffer* pConstantBuffer = renderer::constantBuffer[(UINT)eCBType::Fade];
				pConstantBuffer->SetData(&FadeCB);
				pConstantBuffer->Bind(eShaderStage::PS);
			}
	
	
		GameObject::Render();
		
	}

}