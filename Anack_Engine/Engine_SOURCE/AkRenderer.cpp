
#include "AkRenderer.h"
#include "AkResources.h"
#include "AkTexture.h"
#include "AkMaterial.h"
#include "AkStructedBuffer.h"
#include "AkPaintShader.h"
#include "AkParticleShader.h"



namespace renderer
{
	using namespace Ak;
	using namespace Ak::graphics;

	
	Ak::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::END] = {};

	//light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;



	Ak::Camera* mainCamera = nullptr;
	std::vector<Ak::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};


	void SetUpState()
	{

#pragma region InputLayOut
		//Input Layout정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC ArrLayOut[3] = {};

		//Pos
		ArrLayOut[0].AlignedByteOffset = 0;
		ArrLayOut[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		ArrLayOut[0].InputSlot = 0;
		ArrLayOut[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ArrLayOut[0].SemanticName = "POSITION";
		ArrLayOut[0].SemanticIndex = 0;

		//Color
		ArrLayOut[1].AlignedByteOffset = 12;
		ArrLayOut[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		ArrLayOut[1].InputSlot = 0;
		ArrLayOut[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ArrLayOut[1].SemanticName = "COLOR";
		ArrLayOut[1].SemanticIndex = 0;

		ArrLayOut[2].AlignedByteOffset = 28;
		ArrLayOut[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		ArrLayOut[2].InputSlot = 0;
		ArrLayOut[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ArrLayOut[2].SemanticName = "TEXCOORD";
		ArrLayOut[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = Ak::Resources::Find<Shader>(L"TriangleShader");

		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut,
			3,
			shader->GetVSCode(),
			shader->GetInputLayoutAddressOf());

		 shader = Ak::Resources::Find<Shader>(L"SpriteShader");

		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut,
			3,
			shader->GetVSCode(),
			shader->GetInputLayoutAddressOf());

		shader = Ak::Resources::Find<Shader>(L"GridShader");

		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut,
			3,
			shader->GetVSCode(),
			shader->GetInputLayoutAddressOf());


		shader = Ak::Resources::Find<Shader>(L"DebugShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = Ak::Resources::Find<Shader>(L"SpriteAnimationShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			 ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Ak::Resources::Find<Shader>(L"ParticleShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			  ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Ak::Resources::Find<Shader>(L"MonsterShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		//
		shader = Ak::Resources::Find<Shader>(L"PlayerShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Ak::Resources::Find<Shader>(L"FadeShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Ak::Resources::Find<Shader>(L"UIShader");
		Ak::graphics::GetDevice()->CreateInputLayout(
			ArrLayOut
			, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

	
#pragma endregion

#pragma region SamplerState
		D3D11_SAMPLER_DESC samplerdesc = {};
		samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerdesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());


		samplerdesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerdesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region RasterizerState
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());

#pragma endregion

#pragma region DepthStencilState
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());

#pragma endregion

#pragma region BlendState
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());


#pragma endregion

	}


	void LoadMesh()
	{

		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		// PointMesh
		Vertex v = {};
		v.Pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear();


		//Rect
		vertexes.resize(4);

		vertexes[0].Pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].Pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].Pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].Pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);


		//vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.Pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.Pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadBuffer()
	{
		
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		//Animator Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		//Monster 
		constantBuffer[(UINT)eCBType::Monster] = new ConstantBuffer(eCBType::Monster);
		constantBuffer[(UINT)eCBType::Monster]->Create(sizeof(MonsterCB));

		//Player 
		constantBuffer[(UINT)eCBType::Player] = new ConstantBuffer(eCBType::Player);
		constantBuffer[(UINT)eCBType::Player]->Create(sizeof(PlayerCB));

		

		//Fade 
		constantBuffer[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
		constantBuffer[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));


		//UI 
		constantBuffer[(UINT)eCBType::Ui] = new ConstantBuffer(eCBType::Ui);
		constantBuffer[(UINT)eCBType::Ui]->Create(sizeof(UICB));

		//Collider
		constantBuffer[(UINT)eCBType::Collider] = new ConstantBuffer(eCBType::Collider);
		constantBuffer[(UINT)eCBType::Collider]->Create(sizeof(ColliderCB));

		//light Structed Buffer   빛 개수
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 11, eViewType::SRV, nullptr, true);





	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		Ak::Resources::Insert(L"TriangleShader", shader);

		shader  = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Ak::Resources::Insert(L"SpriteShader", shader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		Ak::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Ak::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		Ak::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Ak::Resources::Insert(L"paintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		Ak::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	
		Ak::Resources::Insert(L"ParticleShader", particleShader);


		std::shared_ptr<Shader> monsterShader = std::make_shared<Shader>();
		monsterShader->Create(eShaderStage::VS, L"MonsterVS.hlsl", "main");
		monsterShader->Create(eShaderStage::PS, L"MonsterPS.hlsl", "main");
		Ak::Resources::Insert(L"MonsterShader", monsterShader);


		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"PlayerVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"PlayerPS.hlsl", "main");

		Ak::Resources::Insert(L"PlayerShader", playerShader);

		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"FadeVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");
		Ak::Resources::Insert(L"FadeShader", fadeShader);

		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UiVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UiPS.hlsl", "main");
		Ak::Resources::Insert(L"UIShader", uiShader);


	}

	void LoadText()
	{

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		////paint texture
		//std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		//uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		//Ak::Resources::Insert(L"PaintTexuture", uavTexture);

		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"Default_Particle", L"..\\Resources\\Texture\\Particle\\Default_Particle.png");
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\Texture\\Particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"black_soul", L"..\\Resources\\Texture\\Particle\\black_soul.png");
		Resources::Load<Texture>(L"dream_fog", L"..\\Resources\\Texture\\Particle\\dream_fog.png");
		Resources::Load<Texture>(L"Fog", L"..\\Resources\\Texture\\Particle\\Fog.png");
		Resources::Load<Texture>(L"fungus_fog", L"..\\Resources\\Texture\\Particle\\fungus_fog.png");
		Resources::Load<Texture>(L"hot_spring_smoke", L"..\\Resources\\Texture\\Particle\\hot_spring_smoke.png");

		Resources::Load<Texture>(L"Radiance_particle", L"..\\Resources\\Texture\\Particle\\Radiance_particle.png");
		Resources::Load<Texture>(L"Grimm_particle", L"..\\Resources\\Texture\\Particle\\Grimm_particle.png");
		Resources::Load<Texture>(L"Grimm_smoke1", L"..\\Resources\\Texture\\Particle\\grimm_smoke1.png");
		Resources::Load<Texture>(L"Grimm_smoke2", L"..\\Resources\\Texture\\Particle\\grimm_smoke2.png");
		Resources::Load<Texture>(L"Grimm_smoke3", L"..\\Resources\\Texture\\Particle\\grimm_smoke3.png");
		Resources::Load<Texture>(L"Knight_foot_particle", L"..\\Resources\\Texture\\Particle\\Knight_foot_particle.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");

		Resources::Load<Texture>(L"Hunter_d", L"..\\Resources\\Texture\\Particle\\Hunter_d.png");


#pragma region The Knight

		std::shared_ptr<Texture> Knightidle
			= Resources::Load<Texture>(L"TheKnight_idle", L"..\\Resources\\Texture\\Knight\\Knight_idle.png");

		std::shared_ptr<Material> Knight_idle = std::make_shared<Material>();
		Knight_idle->SetShader(spriteShader);
		Knight_idle->SetTexture(Knightidle);
		Knight_idle->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Knight_idle", Knight_idle);


#pragma endregion

#pragma region Start_Scene_BG

		
		std::shared_ptr<Texture> StartBG
			= Resources::Load<Texture>(L"StartGameBackGround", L"..\\Resources\\Texture\\BG_GameStart.png");

		std::shared_ptr<Material> Start_BGMR = std::make_shared<Material>();
		Start_BGMR->SetShader(spriteShader);
		Start_BGMR->SetTexture(StartBG);
		//Start_BGMR->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Start_BGMR", Start_BGMR);


		std::shared_ptr<Texture> TownBG01
			= Resources::Load<Texture>(L"TownBG01", L"..\\Resources\\Texture\\StartScene\\Town_BG_01.png");

		std::shared_ptr<Material> Town_BG_01 = std::make_shared<Material>();
		Town_BG_01->SetShader(spriteShader);
		Town_BG_01->SetTexture(TownBG01);
		Town_BG_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_01", Town_BG_01);


		std::shared_ptr<Texture> TownBG02
			= Resources::Load<Texture>(L"TownBG02", L"..\\Resources\\Texture\\StartScene\\Town_BG_02.png");

		std::shared_ptr<Material> Town_BG_02 = std::make_shared<Material>();
		Town_BG_02->SetShader(spriteShader);
		Town_BG_02->SetTexture(TownBG02);
		Town_BG_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_02", Town_BG_02);

		std::shared_ptr<Texture> TownBG03
			= Resources::Load<Texture>(L"TownBG03", L"..\\Resources\\Texture\\StartScene\\Town_BG_03.png");

		std::shared_ptr<Material> Town_BG_03 = std::make_shared<Material>();
		Town_BG_03->SetShader(spriteShader);
		Town_BG_03->SetTexture(TownBG03);
		Town_BG_03->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_03", Town_BG_03);



		std::shared_ptr<Texture> TownBG04
			= Resources::Load<Texture>(L"TownBG04", L"..\\Resources\\Texture\\StartScene\\Town_BG_04.png");

		std::shared_ptr<Material> Town_BG_04 = std::make_shared<Material>();
		Town_BG_04->SetShader(spriteShader);
		Town_BG_04->SetTexture(TownBG04);
		Town_BG_04->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_04", Town_BG_04);



		std::shared_ptr<Texture> TownBG05
			= Resources::Load<Texture>(L"TownBG05", L"..\\Resources\\Texture\\StartScene\\town_BG_05.png");

		std::shared_ptr<Material> Town_BG_05 = std::make_shared<Material>();
		Town_BG_05->SetShader(spriteShader);
		Town_BG_05->SetTexture(TownBG05);
		Town_BG_05->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_05", Town_BG_05);


		std::shared_ptr<Texture> TownBG06
			= Resources::Load<Texture>(L"TownBG06", L"..\\Resources\\Texture\\StartScene\\town_BG_06.png");

		std::shared_ptr<Material> Town_BG_06 = std::make_shared<Material>();
		Town_BG_06->SetShader(spriteShader);
		Town_BG_06->SetTexture(TownBG05);
		Town_BG_06->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_06", Town_BG_06);



		std::shared_ptr<Texture> TownBG07
			= Resources::Load<Texture>(L"TownBG07", L"..\\Resources\\Texture\\StartScene\\town_BG_07.png");

		std::shared_ptr<Material> Town_BG_07 = std::make_shared<Material>();
		Town_BG_07->SetShader(spriteShader);
		Town_BG_07->SetTexture(TownBG07);
		Town_BG_07->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_BG_07", Town_BG_07);




#pragma endregion Start_Scene_BG

#pragma region Start_Scene_Layerd

		std::shared_ptr<Texture> TownSmoke
			= Resources::Load<Texture>(L"Town_Smoke01", L"..\\Resources\\Texture\\StartScene\\town_smoke.png");

		std::shared_ptr<Material> Town_Smoke = std::make_shared<Material>();
		Town_Smoke->SetShader(spriteShader);
		Town_Smoke->SetTexture(TownSmoke);
		Town_Smoke->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_Smoke", Town_Smoke);



		std::shared_ptr<Texture> TownHouseOpen
			= Resources::Load<Texture>(L"Town_House_open", L"..\\Resources\\Texture\\StartScene\\town_house_open.png");

		std::shared_ptr<Material> Town_House_Open = std::make_shared<Material>();
		Town_House_Open->SetShader(spriteShader);
		Town_House_Open->SetTexture(TownHouseOpen);
		Town_House_Open->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_House_Open", Town_House_Open);


		std::shared_ptr<Texture> TownHouseClose
			= Resources::Load<Texture>(L"Town_House_close", L"..\\Resources\\Texture\\StartScene\\town_house_close.png");

		std::shared_ptr<Material> Town_House_Close = std::make_shared<Material>();
		Town_House_Close->SetShader(spriteShader);
		Town_House_Close->SetTexture(TownHouseClose);
		Town_House_Close->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_House_Close", Town_House_Close);


		std::shared_ptr<Texture> TownHouse02
			= Resources::Load<Texture>(L"Town_House02", L"..\\Resources\\Texture\\StartScene\\town_house_02.png");

		std::shared_ptr<Material> Town_House_02 = std::make_shared<Material>();
		Town_House_02->SetShader(spriteShader);
		Town_House_02->SetTexture(TownHouse02);
		Town_House_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_House_02", Town_House_02);





		std::shared_ptr<Texture> Townlayered01
			= Resources::Load<Texture>(L"town_layered01", L"..\\Resources\\Texture\\StartScene\\town_layered_01.png");

		std::shared_ptr<Material> Town_layered_01 = std::make_shared<Material>();
		Town_layered_01->SetShader(spriteShader);
		Town_layered_01->SetTexture(Townlayered01);
		Town_layered_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_layered_01", Town_layered_01);




		std::shared_ptr<Texture> Townlayered02
			= Resources::Load<Texture>(L"town_layered02", L"..\\Resources\\Texture\\StartScene\\town_layered_02.png");

		std::shared_ptr<Material> Town_layered_02 = std::make_shared<Material>();
		Town_layered_02->SetShader(spriteShader);
		Town_layered_02->SetTexture(Townlayered02);
		Town_layered_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_layered_02", Town_layered_02);

		std::shared_ptr<Texture> Townlayered03
			= Resources::Load<Texture>(L"town_layered03", L"..\\Resources\\Texture\\StartScene\\town_layered_03.png");

		std::shared_ptr<Material> Town_layered_03 = std::make_shared<Material>();
		Town_layered_03->SetShader(spriteShader);
		Town_layered_03->SetTexture(Townlayered03);
		Town_layered_03->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_layered_03", Town_layered_03);


		std::shared_ptr<Texture> Townlayered04
			= Resources::Load<Texture>(L"town_layered04", L"..\\Resources\\Texture\\StartScene\\town_layered_04.png");

		std::shared_ptr<Material> Town_layered_04 = std::make_shared<Material>();
		Town_layered_04->SetShader(spriteShader);
		Town_layered_04->SetTexture(Townlayered04);
		Town_layered_04->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_layered_04", Town_layered_04);



		std::shared_ptr<Texture> town_left_wall
			= Resources::Load<Texture>(L"town_left_wall", L"..\\Resources\\Texture\\StartScene\\leftwall.png");

		std::shared_ptr<Material> Town_left_wall01 = std::make_shared<Material>();
		Town_left_wall01->SetShader(spriteShader);
		Town_left_wall01->SetTexture(town_left_wall);
		Town_left_wall01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_left_wall01", Town_left_wall01);


		std::shared_ptr<Texture> townrightwall
			= Resources::Load<Texture>(L"town_right_wall", L"..\\Resources\\Texture\\StartScene\\right_wall.png");

		std::shared_ptr<Material> Town_right_wall_01 = std::make_shared<Material>();
		Town_right_wall_01->SetShader(spriteShader);
		Town_right_wall_01->SetTexture(townrightwall);
		Town_right_wall_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_right_wall_01", Town_right_wall_01);

#pragma endregion
		
#pragma region MenuScene

		std::shared_ptr<Texture> MenuBG
			= Resources::Load<Texture>(L"MenuBackGround", L"..\\Resources\\Texture\\BG_Menu.png");


		std::shared_ptr<Material> Menu_BGMR = std::make_shared<Material>();
		Menu_BGMR->SetShader(spriteShader);
		Menu_BGMR->SetTexture(MenuBG);
		//Menu_BGMR->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Menutexture", Menu_BGMR);



		//UI 
		std::shared_ptr<Texture> MenuTt = Resources::Load<Texture>(L"MenuTitle", L"..\\Resources\\Texture\\Menu_Title.png");

		std::shared_ptr<Material> Menu_Title = std::make_shared<Material>();
		Menu_Title->SetShader(spriteShader);
		Menu_Title->SetTexture(MenuTt);
		Menu_Title->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Menu_Title", Menu_Title);


		//
		std::shared_ptr<Texture> MenuPt
			= Resources::Load<Texture>(L"MenuPointer", L"..\\Resources\\Texture\\Menu_Pointer.png");

		std::shared_ptr<Material> Menu_Pointer = std::make_shared<Material>();
		Menu_Pointer->SetShader(spriteShader);
		Menu_Pointer->SetTexture(MenuPt);
		Menu_Pointer->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Menu_Pointer", Menu_Pointer);



		//
		std::shared_ptr<Texture> MenuLogo
			= Resources::Load<Texture>(L"Menu_Logo01", L"..\\Resources\\Texture\\MenuScene\\Menu_Logo.png");

		std::shared_ptr<Material> Menu_Logo = std::make_shared<Material>();
		Menu_Logo->SetShader(spriteShader);
		Menu_Logo->SetTexture(MenuLogo);
		Menu_Logo->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Menu_Logo", Menu_Logo);


		std::shared_ptr<Texture> MenuTitle01
			= Resources::Load<Texture>(L"Menu_Title01", L"..\\Resources\\Texture\\MenuScene\\Menu_Tile_layered01.png");

		std::shared_ptr<Material> Menu_Title_01 = std::make_shared<Material>();
		Menu_Title_01->SetShader(spriteShader);
		Menu_Title_01->SetTexture(MenuTitle01);
		Menu_Title_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Menu_Title_01", Menu_Title_01);



		std::shared_ptr<Texture> GameStart
			= Resources::Load<Texture>(L"Game_Start", L"..\\Resources\\Texture\\MenuScene\\GameStart.png");

		std::shared_ptr<Material> Game_Start01 = std::make_shared<Material>();
		Game_Start01->SetShader(spriteShader);
		Game_Start01->SetTexture(GameStart);
		Game_Start01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Game_Start01", Game_Start01);


		std::shared_ptr<Texture> GameExit
			= Resources::Load<Texture>(L"Game_Exit", L"..\\Resources\\Texture\\MenuScene\\GameExit.png");

		std::shared_ptr<Material> Game_Exit01 = std::make_shared<Material>();
		Game_Exit01->SetShader(spriteShader);
		Game_Exit01->SetTexture(GameExit);
		Game_Exit01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Game_Exit01", Game_Exit01);



		std::shared_ptr<Texture> GameStartEffect
			= Resources::Load<Texture>(L"Game_Start_Effect", L"..\\Resources\\Texture\\MenuScene\\Game_Start_effect.png");

		std::shared_ptr<Material> Game_Start_Effect01 = std::make_shared<Material>();
		Game_Start_Effect01->SetShader(spriteShader);
		Game_Start_Effect01->SetTexture(GameStartEffect);
		Game_Start_Effect01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Game_Start_Effect01", Game_Start_Effect01);



#pragma endregion

#pragma region HP_UI

		//
		std::shared_ptr<Texture> HpHUD 
			= Resources::Load<Texture>(L"HPHUD", L"..\\Resources\\Texture\\HP_HUD.png");

		std::shared_ptr<Material> HP_HUD = std::make_shared<Material>();
		HP_HUD->SetShader(spriteShader);
		HP_HUD->SetTexture(HpHUD);
		HP_HUD->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"HP_HUD", HP_HUD);


		std::shared_ptr<Texture> HPBall
			= Resources::Load<Texture>(L"HPBall", L"..\\Resources\\Texture\\HP_Ball.png");

		std::shared_ptr<Material> HP_Ball = std::make_shared<Material>();
		HP_Ball->SetShader(spriteShader);
		HP_Ball->SetTexture(HPBall);
		HP_Ball->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"HP_Ball", HP_Ball);


		std::shared_ptr<Texture> CoinHUD
			= Resources::Load<Texture>(L"CoinHUD", L"..\\Resources\\Texture\\Coin_HUD.png");

		std::shared_ptr<Material> Coin_HUD = std::make_shared<Material>();
		Coin_HUD->SetShader(spriteShader);
		Coin_HUD->SetTexture(CoinHUD);
		Coin_HUD->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Coin_HUD", Coin_HUD);



		std::shared_ptr<Texture> ShadowRing
			= Resources::Load<Texture>(L"ShadowRing_txt", L"..\\Resources\\Texture\\Knight\\shadow_ring.png");

		std::shared_ptr<Material> Shadow_Ring = std::make_shared<Material>();
		Shadow_Ring->SetShader(spriteShader);
		Shadow_Ring->SetTexture(ShadowRing);
		Shadow_Ring->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Shadow_Ring", Shadow_Ring);


		std::shared_ptr<Texture> TopUI
			= Resources::Load<Texture>(L"TopUI_txt", L"..\\Resources\\Texture\\UI\\top_fleur.png");

		std::shared_ptr<Material> Top_UI = std::make_shared<Material>();
		Top_UI->SetShader(spriteShader);
		Top_UI->SetTexture(TopUI);
		Top_UI->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Top_UI", Top_UI);

		std::shared_ptr<Texture> BottomUI
			= Resources::Load<Texture>(L"BottomUI_txt", L"..\\Resources\\Texture\\UI\\bottom_fleur.png");

		std::shared_ptr<Material> Bottom_UI = std::make_shared<Material>();
		Bottom_UI->SetShader(spriteShader);
		Bottom_UI->SetTexture(BottomUI);
		Bottom_UI->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bottom_UI", Bottom_UI);

		std::shared_ptr<Texture> BGUI
			= Resources::Load<Texture>(L"BG_UI_txt", L"..\\Resources\\Texture\\UI\\BG_UI_01.png");

		std::shared_ptr<Material> BG_UI = std::make_shared<Material>();
		BG_UI->SetShader(spriteShader);
		BG_UI->SetTexture(BGUI);
		BG_UI->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BG_UI", BG_UI);

		std::shared_ptr<Texture> BGUI02
			= Resources::Load<Texture>(L"BG_U2I_txt", L"..\\Resources\\Texture\\UI\\BG_UI_02.png");

		std::shared_ptr<Material> BGUI_02 = std::make_shared<Material>();
		BGUI_02->SetShader(spriteShader);
		BGUI_02->SetTexture(BGUI02);
		BGUI_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BGUI_02", BGUI_02);


		std::shared_ptr<Texture> BGUI03
			= Resources::Load<Texture>(L"BG_UI3_txt", L"..\\Resources\\Texture\\UI\\BG_UI_03.png");

		std::shared_ptr<Material> BG_UI03 = std::make_shared<Material>();
		BG_UI03->SetShader(spriteShader);
		BG_UI03->SetTexture(BGUI03);
		BG_UI03->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BG_UI03", BG_UI03);


	
#pragma endregion

#pragma region StartScene_Floor

		std::shared_ptr<Texture> Highway01
			= Resources::Load<Texture>(L"High_way_01", L"..\\Resources\\Texture\\StartScene\\highway1.png");

		std::shared_ptr<Material> High_way01 = std::make_shared<Material>();
		High_way01->SetShader(spriteShader);
		High_way01->SetTexture(Highway01);
		High_way01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"High_way01", High_way01);

		std::shared_ptr<Texture> Highway02
			= Resources::Load<Texture>(L"High_way_02", L"..\\Resources\\Texture\\StartScene\\highway2.png");

		std::shared_ptr<Material> High_way02 = std::make_shared<Material>();
		High_way02->SetShader(spriteShader);
		High_way02->SetTexture(Highway02);
		High_way02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"High_way02", High_way02);


		std::shared_ptr<Texture> TownFloor
			= Resources::Load<Texture>(L"Town_Floor_01", L"..\\Resources\\Texture\\StartScene\\town_floor.png");

		std::shared_ptr<Material> Town_Floor = std::make_shared<Material>();
		Town_Floor->SetShader(spriteShader);
		Town_Floor->SetTexture(TownFloor);
		Town_Floor->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_Floor", Town_Floor);



		std::shared_ptr<Texture> TownFloorlong
			= Resources::Load<Texture>(L"Town_long", L"..\\Resources\\Texture\\StartScene\\test.png");

		std::shared_ptr<Material> Town_Floor_long = std::make_shared<Material>();
		Town_Floor_long->SetShader(spriteShader);
		Town_Floor_long->SetTexture(TownFloorlong);
		Town_Floor_long->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_Floor_long", Town_Floor_long);

		std::shared_ptr<Texture> TownFloorsize06
			= Resources::Load<Texture>(L"Town_Floor_size_06", L"..\\Resources\\Texture\\StartScene\\town_floor_06.png");

		std::shared_ptr<Material> Town_Floor_size06 = std::make_shared<Material>();
		Town_Floor_size06->SetShader(spriteShader);
		Town_Floor_size06->SetTexture(TownFloorsize06);
		Town_Floor_size06->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_Floor_size06", Town_Floor_size06);


		std::shared_ptr<Texture> TownUnderWall
			= Resources::Load<Texture>(L"Town_Under_wall_01", L"..\\Resources\\Texture\\StartScene\\town_under_wall.png");

		std::shared_ptr<Material> Town_Under_Wall01 = std::make_shared<Material>();
		Town_Under_Wall01->SetShader(spriteShader);
		Town_Under_Wall01->SetTexture(TownUnderWall);
		Town_Under_Wall01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Town_Under_Wall01", Town_Under_Wall01);




#pragma endregion

#pragma region StartScene_bench

		std::shared_ptr<Texture> townbench
			= Resources::Load<Texture>(L"town_bench01", L"..\\Resources\\Texture\\StartScene\\town_bench.png");

		std::shared_ptr<Material> town_bench = std::make_shared<Material>();
		town_bench->SetShader(spriteShader);
		town_bench->SetTexture(townbench);
		town_bench->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"town_bench", town_bench);

		std::shared_ptr<Texture> townbenchlit
			= Resources::Load<Texture>(L"town_bench01lit", L"..\\Resources\\Texture\\StartScene\\town_bench_lit.png");

		std::shared_ptr<Material> town_benchlit = std::make_shared<Material>();
		town_benchlit->SetShader(spriteShader);
		town_benchlit->SetTexture(townbenchlit);
		//town_benchlit->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"town_benchlit", town_benchlit);

		std::shared_ptr<Texture> townlamp
			= Resources::Load<Texture>(L"town_lamp01", L"..\\Resources\\Texture\\StartScene\\ruin_sign_01.png");

		std::shared_ptr<Material> town_lamp = std::make_shared<Material>();
		town_lamp->SetShader(spriteShader);
		town_lamp->SetTexture(townlamp);
		town_lamp->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"town_lamp", town_lamp);


		std::shared_ptr<Texture> townlamp02
			= Resources::Load<Texture>(L"town_lamp_02", L"..\\Resources\\Texture\\StartScene\\town_lamp_b.png");

		std::shared_ptr<Material> town_lamp02 = std::make_shared<Material>();
		town_lamp02->SetShader(spriteShader);
		town_lamp02->SetTexture(townlamp02);
		town_lamp02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"town_lamp02", town_lamp02);




		//StartScene Well


		std::shared_ptr<Texture> Welltop
			= Resources::Load<Texture>(L"town_well_top", L"..\\Resources\\Texture\\StartScene\\town_well_top.png");

		std::shared_ptr<Material> Well_top = std::make_shared<Material>();
		Well_top->SetShader(spriteShader);
		Well_top->SetTexture(Welltop);
		Well_top->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Well_top", Well_top);


		std::shared_ptr<Texture> Wellfloor
			= Resources::Load<Texture>(L"town_well_floor", L"..\\Resources\\Texture\\StartScene\\town_well_front.png");

		std::shared_ptr<Material> Well_floor = std::make_shared<Material>();
		Well_floor->SetShader(spriteShader);
		Well_floor->SetTexture(Wellfloor);
		Well_floor->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Well_floor", Well_floor);


		std::shared_ptr<Texture> WellBack
			= Resources::Load<Texture>(L"town_well_back", L"..\\Resources\\Texture\\StartScene\\town_well_back.png");

		std::shared_ptr<Material> Well_back = std::make_shared<Material>();
		Well_back->SetShader(spriteShader);
		Well_back->SetTexture(WellBack);
		Well_back->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Well_back", Well_back);



#pragma endregion

#pragma region Battle_Scene

		//
		std::shared_ptr<Texture> BattleBG01
			= Resources::Load<Texture>(L"BattleBackGround01", L"..\\Resources\\Texture\\BG_Battle1.png");

		std::shared_ptr<Material> Battle_BG01 = std::make_shared<Material>();
		Battle_BG01->SetShader(spriteShader);
		Battle_BG01->SetTexture(BattleBG01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Battle_BG01", Battle_BG01);


		std::shared_ptr<Texture> BTlayeredBG
			= Resources::Load<Texture>(L"BT_Layered_BG01", L"..\\Resources\\Texture\\BattleScene\\BT_latered_bg.png");

		std::shared_ptr<Material> BT_Layered_01 = std::make_shared<Material>();
		BT_Layered_01->SetShader(spriteShader);
		BT_Layered_01->SetTexture(BTlayeredBG);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Layered_01", BT_Layered_01);



		std::shared_ptr<Texture> BTlayeredBG02
			= Resources::Load<Texture>(L"BT_Layered_BG02", L"..\\Resources\\Texture\\BattleScene\\BT_larered_bg_02.png");

		std::shared_ptr<Material> BT_Layered_02 = std::make_shared<Material>();
		BT_Layered_02->SetShader(spriteShader);
		BT_Layered_02->SetTexture(BTlayeredBG02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Layered_02", BT_Layered_02);




		std::shared_ptr<Texture> BTFG01
			= Resources::Load<Texture>(L"BT_FG01", L"..\\Resources\\Texture\\BattleScene\\FG_01.png");

		std::shared_ptr<Material> BT_FG_01 = std::make_shared<Material>();
		BT_FG_01->SetShader(spriteShader);
		BT_FG_01->SetTexture(BTFG01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_FG_01", BT_FG_01);


		std::shared_ptr<Texture> BTFG02
			= Resources::Load<Texture>(L"BT_FG02", L"..\\Resources\\Texture\\BattleScene\\FG_02.png");

		std::shared_ptr<Material> BT_FG_02 = std::make_shared<Material>();
		BT_FG_02->SetShader(spriteShader);
		BT_FG_02->SetTexture(BTFG02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_FG_02", BT_FG_02);



		std::shared_ptr<Texture> BtBGChain
			= Resources::Load<Texture>(L"BT_BG_Chain01", L"..\\Resources\\Texture\\BattleScene\\BG_chain.png");

		std::shared_ptr<Material> BT_BG_Chain = std::make_shared<Material>();
		BT_BG_Chain->SetShader(spriteShader);
		BT_BG_Chain->SetTexture(BtBGChain);
		BT_BG_Chain->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_BG_Chain", BT_BG_Chain);


		std::shared_ptr<Texture> BtWall01
			= Resources::Load<Texture>(L"BT_wall_01", L"..\\Resources\\Texture\\BattleScene\\BT_wall01.png");

		std::shared_ptr<Material> Bt_wall01 = std::make_shared<Material>();
		Bt_wall01->SetShader(spriteShader);
		Bt_wall01->SetTexture(BtWall01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bt_wall01", Bt_wall01);


		std::shared_ptr<Texture> BTWallBG01
			= Resources::Load<Texture>(L"BT_Wall_BG_01", L"..\\Resources\\Texture\\BattleScene\\BT_wall_BG.png");

		std::shared_ptr<Material> Bt_wall_bg01 = std::make_shared<Material>();
		Bt_wall_bg01->SetShader(spriteShader);
		Bt_wall_bg01->SetTexture(BTWallBG01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bt_wall_bg01", Bt_wall_bg01);

		std::shared_ptr<Texture> BTWallBG02
			= Resources::Load<Texture>(L"BT_Wall_BG_02", L"..\\Resources\\Texture\\BattleScene\\BT_wall01_l.png");

		std::shared_ptr<Material> Bt_wall_bg02 = std::make_shared<Material>();
		Bt_wall_bg02->SetShader(spriteShader);
		Bt_wall_bg02->SetTexture(BTWallBG02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bt_wall_bg02", Bt_wall_bg02);



		std::shared_ptr<Texture> BtChain
			= Resources::Load<Texture>(L"BT_Chain01", L"..\\Resources\\Texture\\BattleScene\\BT_chain.png");

		std::shared_ptr<Material> BT_Chain = std::make_shared<Material>();
		BT_Chain->SetShader(spriteShader);
		BT_Chain->SetTexture(BtChain);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Chain", BT_Chain);

		std::shared_ptr<Texture> Btwallright01
			= Resources::Load<Texture>(L"BT_Wall_right01", L"..\\Resources\\Texture\\BattleScene\\wall_right01.png");

		std::shared_ptr<Material> BT_Wall_right_01 = std::make_shared<Material>();
		BT_Wall_right_01->SetShader(spriteShader);
		BT_Wall_right_01->SetTexture(Btwallright01);
		BT_Wall_right_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Wall_right_01", BT_Wall_right_01);




		std::shared_ptr<Texture> Btwallright02
			= Resources::Load<Texture>(L"BT_Wall_right02", L"..\\Resources\\Texture\\BattleScene\\wall_right02.png");

		std::shared_ptr<Material> BT_Wall_right_02 = std::make_shared<Material>();
		BT_Wall_right_02->SetShader(spriteShader);
		BT_Wall_right_02->SetTexture(Btwallright02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Wall_right_02", BT_Wall_right_02);

		std::shared_ptr<Texture> Btwallright03
			= Resources::Load<Texture>(L"BT_Wall_right03", L"..\\Resources\\Texture\\BattleScene\\wall_right03.png");

		std::shared_ptr<Material> BT_Wall_right_03 = std::make_shared<Material>();
		BT_Wall_right_03->SetShader(spriteShader);
		BT_Wall_right_03->SetTexture(Btwallright03);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Wall_right_03", BT_Wall_right_03);



		std::shared_ptr<Texture> BtFloor01
			= Resources::Load<Texture>(L"BT_Floor01", L"..\\Resources\\Texture\\BattleScene\\BT_floor_01.png");

		std::shared_ptr<Material> BT_floor_01 = std::make_shared<Material>();
		BT_floor_01->SetShader(spriteShader);
		BT_floor_01->SetTexture(BtFloor01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_floor_01", BT_floor_01);


		std::shared_ptr<Texture> BTtemple
			= Resources::Load<Texture>(L"BT_temple", L"..\\Resources\\Texture\\BattleScene\\bt_temlpe.png");

		std::shared_ptr<Material> BT_Temple_01 = std::make_shared<Material>();
		BT_Temple_01->SetShader(spriteShader);
		BT_Temple_01->SetTexture(BTtemple);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Temple_01", BT_Temple_01);


		std::shared_ptr<Texture> BtHomesFloor
			= Resources::Load<Texture>(L"Bt_homesfloor", L"..\\Resources\\Texture\\BattleScene\\BT_Homes_floor.png");

		std::shared_ptr<Material> Bt_homes_floor_01 = std::make_shared<Material>();
		Bt_homes_floor_01->SetShader(spriteShader);
		Bt_homes_floor_01->SetTexture(BtHomesFloor);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bt_homes_floor_01", Bt_homes_floor_01);


		std::shared_ptr<Texture> BtHomesFloor02
			= Resources::Load<Texture>(L"Bt_homesfloor02", L"..\\Resources\\Texture\\BattleScene\\BT_Homes_floor2.png");

		std::shared_ptr<Material> Bt_homes_floor_02 = std::make_shared<Material>();
		Bt_homes_floor_02->SetShader(spriteShader);
		Bt_homes_floor_02->SetTexture(BtHomesFloor02);
		Bt_homes_floor_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bt_homes_floor_02", Bt_homes_floor_02);


		std::shared_ptr<Texture> BtRope
			= Resources::Load<Texture>(L"BT_Rope01", L"..\\Resources\\Texture\\BattleScene\\BT_rope.png");

		std::shared_ptr<Material> BT_rope = std::make_shared<Material>();
		BT_rope->SetShader(spriteShader);
		BT_rope->SetTexture(BtRope);
		//BT_rope->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_rope", BT_rope);

		std::shared_ptr<Texture> BTHang
			= Resources::Load<Texture>(L"BT_Hang01", L"..\\Resources\\Texture\\BattleScene\\BT_Hang.png");

		std::shared_ptr<Material> BT_Hang = std::make_shared<Material>();
		BT_Hang->SetShader(spriteShader);
		BT_Hang->SetTexture(BTHang);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Hang", BT_Hang);



		std::shared_ptr<Texture> BtBlackBg
			= Resources::Load<Texture>(L"BT_Black_BG01", L"..\\Resources\\Texture\\BattleScene\\BT_Black_bg.png");

		std::shared_ptr<Material> BT_Black_BG = std::make_shared<Material>();
		BT_Black_BG->SetShader(spriteShader);
		BT_Black_BG->SetTexture(BtBlackBg);
		//BT_Black_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_Black_BG", BT_Black_BG);



		std::shared_ptr<Texture> BtFloorLayered
			= Resources::Load<Texture>(L"BT_Floor_layered01", L"..\\Resources\\Texture\\BattleScene\\BT_floor_layered.png");

		std::shared_ptr<Material> BT_floor_layered = std::make_shared<Material>();
		BT_floor_layered->SetShader(spriteShader);
		BT_floor_layered->SetTexture(BtFloorLayered);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_floor_layered", BT_floor_layered);


		std::shared_ptr<Texture> BtFloorLayered02
			= Resources::Load<Texture>(L"BT_Floor_layered02", L"..\\Resources\\Texture\\BattleScene\\BT_floor_layered_02.png");

		std::shared_ptr<Material> BT_floor_layered_02 = std::make_shared<Material>();
		BT_floor_layered_02->SetShader(spriteShader);
		BT_floor_layered_02->SetTexture(BtFloorLayered02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BT_floor_layered_02", BT_floor_layered_02);

		std::shared_ptr<Texture> BTlowFloor
			= Resources::Load<Texture>(L"Bt_low_floor01", L"..\\Resources\\Texture\\BattleScene\\low_floor.png");

		std::shared_ptr<Material> bt_low_floor_01 = std::make_shared<Material>();
		bt_low_floor_01->SetShader(spriteShader);
		bt_low_floor_01->SetTexture(BTlowFloor);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"bt_low_floor_01", bt_low_floor_01);


		std::shared_ptr<Texture> Brokelayered01
			= Resources::Load<Texture>(L"BT_broke_layere01", L"..\\Resources\\Texture\\BattleScene\\Broke_01.png");

		std::shared_ptr<Material> Broke_layered_01 = std::make_shared<Material>();
		Broke_layered_01->SetShader(spriteShader);
		Broke_layered_01->SetTexture(Brokelayered01);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Broke_layered_01", Broke_layered_01);


		std::shared_ptr<Texture> Brokelayered02
			= Resources::Load<Texture>(L"BT_broke_layere02", L"..\\Resources\\Texture\\BattleScene\\Broke_02.png");

		std::shared_ptr<Material> Broke_layered_02 = std::make_shared<Material>();
		Broke_layered_02->SetShader(spriteShader);
		Broke_layered_02->SetTexture(Brokelayered02);
		//Battle_BG01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Broke_layered_02", Broke_layered_02);

		std::shared_ptr<Texture> wallBreak
			= Resources::Load<Texture>(L"wallBreak_txt", L"..\\Resources\\Texture\\BattleScene\\wall_break.png");

		std::shared_ptr<Material> Wall_Break = std::make_shared<Material>();
		Wall_Break->SetShader(spriteShader);
		Wall_Break->SetTexture(wallBreak);
		Wall_Break->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Wall_Break", Wall_Break);


		std::shared_ptr<Texture> wallBreak2
			= Resources::Load<Texture>(L"wallBreak2_txt", L"..\\Resources\\Texture\\BattleScene\\wall_break_2.png");

		std::shared_ptr<Material> Wall_Break2 = std::make_shared<Material>();
		Wall_Break2->SetShader(spriteShader);
		Wall_Break2->SetTexture(wallBreak2);
		Wall_Break2->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Wall_Break2", Wall_Break2);


#pragma endregion


#pragma region Radiance

		std::shared_ptr<Texture> RadianceBG
			= Resources::Load<Texture>(L"RadianceBG", L"..\\Resources\\Texture\\Dream\\Radiance_BG.png");

		std::shared_ptr<Material> Radiance_BG = std::make_shared<Material>();
		Radiance_BG->SetShader(spriteShader);
		Radiance_BG->SetTexture(RadianceBG);
		//Start_BGMR->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radiance_BG", Radiance_BG);

		std::shared_ptr<Texture> RadianceBG2
			= Resources::Load<Texture>(L"RadianceBG2_txt", L"..\\Resources\\Texture\\Dream\\Radiance_BG2.png");

		std::shared_ptr<Material> Radiance_BG2 = std::make_shared<Material>();
		Radiance_BG2->SetShader(spriteShader);
		Radiance_BG2->SetTexture(RadianceBG2);
		Radiance_BG2->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radiance_BG2", Radiance_BG2);



		std::shared_ptr<Texture> RadianceGround
			= Resources::Load<Texture>(L"RadianceGround", L"..\\Resources\\Texture\\Dream\\Dreamer_ground.png");

		std::shared_ptr<Material> Radiance_Ground = std::make_shared<Material>();
		Radiance_Ground->SetShader(spriteShader);
		Radiance_Ground->SetTexture(RadianceGround);
		Radiance_Ground->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radiance_Ground", Radiance_Ground);

		std::shared_ptr<Texture> radiancetest
			= Resources::Load<Texture>(L"radiance_test_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_Back.png");

		std::shared_ptr<Material> radiance_test = std::make_shared<Material>();
		radiance_test->SetShader(spriteShader);
		radiance_test->SetTexture(radiancetest);
		radiance_test->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"radiance_test", radiance_test);

		std::shared_ptr<Texture> RadianceGroundL
			= Resources::Load<Texture>(L"RadianceGroundL_txt", L"..\\Resources\\Texture\\Dream\\Ground_l.png");

		std::shared_ptr<Material> Radiance_Ground_L = std::make_shared<Material>();
		Radiance_Ground_L->SetShader(spriteShader);
		Radiance_Ground_L->SetTexture(RadianceGroundL);
		Radiance_Ground_L->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Radiance_Ground_L", Radiance_Ground_L);

		std::shared_ptr<Texture> RadianceGroundS
			= Resources::Load<Texture>(L"RadianceGroundS_txt", L"..\\Resources\\Texture\\Dream\\Ground_s.png");

		std::shared_ptr<Material> Radiance_Ground_S = std::make_shared<Material>();
		Radiance_Ground_S->SetShader(spriteShader);
		Radiance_Ground_S->SetTexture(RadianceGroundS);
		Radiance_Ground_S->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Radiance_Ground_S", Radiance_Ground_S);


		std::shared_ptr<Texture> Cloud01
			= Resources::Load<Texture>(L"Cloud01_txt", L"..\\Resources\\Texture\\Dream\\cloud01.png");

		std::shared_ptr<Material> Cloud_01 = std::make_shared<Material>();
		Cloud_01->SetShader(spriteShader);
		Cloud_01->SetTexture(Cloud01);
		Cloud_01->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Cloud_01", Cloud_01);


		std::shared_ptr<Texture> Cloud02
			= Resources::Load<Texture>(L"Cloud02_txt", L"..\\Resources\\Texture\\Dream\\cloud02.png");

		std::shared_ptr<Material> Cloud_02 = std::make_shared<Material>();
		Cloud_02->SetShader(spriteShader);
		Cloud_02->SetTexture(Cloud02);
		Cloud_02->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Cloud_02", Cloud_02);


		std::shared_ptr<Texture> Cloud03
			= Resources::Load<Texture>(L"Cloud03_txt", L"..\\Resources\\Texture\\Dream\\cloud03.png");

		std::shared_ptr<Material> Cloud_03 = std::make_shared<Material>();
		Cloud_03->SetShader(spriteShader);
		Cloud_03->SetTexture(Cloud03);
		Cloud_03->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Cloud_03", Cloud_03);


		std::shared_ptr<Texture> Cloudc
			= Resources::Load<Texture>(L"Cloudc_txt", L"..\\Resources\\Texture\\Dream\\cloud_c.png");

		std::shared_ptr<Material> Cloud_c = std::make_shared<Material>();
		Cloud_c->SetShader(spriteShader);
		Cloud_c->SetTexture(Cloudc);
		Cloud_c->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Cloud_c", Cloud_c);



		std::shared_ptr<Texture> Cloudl
			= Resources::Load<Texture>(L"Cloudl_txt", L"..\\Resources\\Texture\\Dream\\cloud_l.png");

		std::shared_ptr<Material> cloud_l = std::make_shared<Material>();
		cloud_l->SetShader(spriteShader);
		cloud_l->SetTexture(Cloudl);
		cloud_l->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"cloud_l", cloud_l);




		std::shared_ptr<Texture> RadianceAttack01
			= Resources::Load<Texture>(L"RadianceAttack01_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack01.png");

		std::shared_ptr<Material> Radiance_Attack_01 = std::make_shared<Material>();
		Radiance_Attack_01->SetShader(spriteShader);
		Radiance_Attack_01->SetTexture(RadianceAttack01);
		Radiance_Attack_01->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Radiance_Attack_01", Radiance_Attack_01);


		std::shared_ptr<Texture> RadianceAttack02
			= Resources::Load<Texture>(L"RadianceAttack02_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack02.png");

		std::shared_ptr<Material> Radiance_Attack_02 = std::make_shared<Material>();
		Radiance_Attack_02->SetShader(spriteShader);
		Radiance_Attack_02->SetTexture(RadianceAttack02);
		Radiance_Attack_02->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Radiance_Attack_02", Radiance_Attack_02);


		std::shared_ptr<Texture> RadianceAttack03
			= Resources::Load<Texture>(L"RadianceAttack03_txt", L"..\\Resources\\Texture\\Monster\\Radiance\\Radiance_attack03.png");

		std::shared_ptr<Material> Radiance_Attack_03 = std::make_shared<Material>();
		Radiance_Attack_03->SetShader(spriteShader);
		Radiance_Attack_03->SetTexture(RadianceAttack03);
		Radiance_Attack_03->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Radiance_Attack_03", Radiance_Attack_03);


#pragma endregion


#pragma region BossScene


		//
		std::shared_ptr<Texture> BossBG = 
			Resources::Load<Texture>(L"Boss_BG01", L"..\\Resources\\Texture\\BossScene\\Grimm_Battle_BG.png");

		std::shared_ptr<Material> Boss_BG = std::make_shared<Material>();
		Boss_BG->SetShader(spriteShader);
		Boss_BG->SetTexture(BossBG);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_BG", Boss_BG);

		//
		std::shared_ptr<Texture> BossBG02 =
			Resources::Load<Texture>(L"BossBG_02", L"..\\Resources\\Texture\\BossScene\\Grimm_Battle_BG_02.png");

		std::shared_ptr<Material> Boss_BG_02 = std::make_shared<Material>();
		Boss_BG_02->SetShader(spriteShader);
		Boss_BG_02->SetTexture(BossBG02);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_BG_02", Boss_BG_02);



		//
		std::shared_ptr<Texture> BossFloor =
			Resources::Load<Texture>(L"Boss_floor01", L"..\\Resources\\Texture\\BossScene\\ruinhouse_floor.png");

		std::shared_ptr<Material> Boss_Floor_01 = std::make_shared<Material>();
		Boss_Floor_01->SetShader(spriteShader);
		Boss_Floor_01->SetTexture(BossFloor);
		Boss_Floor_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Floor_01", Boss_Floor_01);


		std::shared_ptr<Texture> BossFloor02 =
			Resources::Load<Texture>(L"Boss_floor02", L"..\\Resources\\Texture\\BossScene\\Grimm_floor_02.png");

		std::shared_ptr<Material> Boss_Floor_02 = std::make_shared<Material>();
		Boss_Floor_02->SetShader(spriteShader);
		Boss_Floor_02->SetTexture(BossFloor02);
		Boss_Floor_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Floor_02", Boss_Floor_02);


		std::shared_ptr<Texture> GrimmBGLayered01 =
			Resources::Load<Texture>(L"GrimmBGLayered01_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_BG_layered_01.png");

		std::shared_ptr<Material> Grimm_BG_Layered_01 = std::make_shared<Material>();
		Grimm_BG_Layered_01->SetShader(spriteShader);
		Grimm_BG_Layered_01->SetTexture(GrimmBGLayered01);
		Grimm_BG_Layered_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_BG_Layered_01", Grimm_BG_Layered_01);


		std::shared_ptr<Texture> GrimmBGLayered02 =
			Resources::Load<Texture>(L"GrimmBGLayered02_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_layered_02.png");

		std::shared_ptr<Material> Grimm_BG_Layered_02 = std::make_shared<Material>();
		Grimm_BG_Layered_02->SetShader(spriteShader);
		Grimm_BG_Layered_02->SetTexture(GrimmBGLayered02);
		Grimm_BG_Layered_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_BG_Layered_02", Grimm_BG_Layered_02);


		//
		std::shared_ptr<Texture> BossCurtain01 =
			Resources::Load<Texture>(L"BossCurtain01_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_curtain_01.png");

		std::shared_ptr<Material> Boss_Curtain_01 = std::make_shared<Material>();
		Boss_Curtain_01->SetShader(spriteShader);
		Boss_Curtain_01->SetTexture(BossCurtain01);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Curtain_01", Boss_Curtain_01);


		//
		std::shared_ptr<Texture> Bossragtent =
			Resources::Load<Texture>(L"Bossragtent_txt", L"..\\Resources\\Texture\\BossScene\\grimm_rag_main_tent.png");

		std::shared_ptr<Material> Boss_rag_tent = std::make_shared<Material>();
		Boss_rag_tent->SetShader(spriteShader);
		Boss_rag_tent->SetTexture(Bossragtent);
		Boss_rag_tent->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_rag_tent", Boss_rag_tent);

		//
		std::shared_ptr<Texture> tentChain =
			Resources::Load<Texture>(L"tentChain_txt", L"..\\Resources\\Texture\\BossScene\\tent_chain.png");

		std::shared_ptr<Material> Tent_Chain_01 = std::make_shared<Material>();
		Tent_Chain_01->SetShader(spriteShader);
		Tent_Chain_01->SetTexture(tentChain);
		Tent_Chain_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Tent_Chain_01", Tent_Chain_01);


		//
		std::shared_ptr<Texture> tentChain02 =
			Resources::Load<Texture>(L"tentChain02_txt", L"..\\Resources\\Texture\\BossScene\\tent_chain_02.png");

		std::shared_ptr<Material> Tent_Chain_02 = std::make_shared<Material>();
		Tent_Chain_02->SetShader(spriteShader);
		Tent_Chain_02->SetTexture(tentChain02);
		Tent_Chain_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Tent_Chain_02", Tent_Chain_02);



		//
		std::shared_ptr<Texture> BossPillar =
			Resources::Load<Texture>(L"BossPillar_txt", L"..\\Resources\\Texture\\BossScene\\grimm_Pillar.png");

		std::shared_ptr<Material> Boss_Pillar = std::make_shared<Material>();
		Boss_Pillar->SetShader(spriteShader);
		Boss_Pillar->SetTexture(BossPillar);
		Boss_Pillar->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Pillar", Boss_Pillar);


		//
		std::shared_ptr<Texture> BossDoor =
			Resources::Load<Texture>(L"Boss_Door_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_door.png");

		std::shared_ptr<Material> Boss_Door = std::make_shared<Material>();
		Boss_Door->SetShader(spriteShader);
		Boss_Door->SetTexture(BossDoor);
		Boss_Door->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Door", Boss_Door);


		//
		std::shared_ptr<Texture> Bossflooreffect =
			Resources::Load<Texture>(L"Bossflooreffect_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_floor_effecr.png");

		std::shared_ptr<Material> Boss_floor_effect = std::make_shared<Material>();
		Boss_floor_effect->SetShader(spriteShader);
		Boss_floor_effect->SetTexture(Bossflooreffect);
		Boss_floor_effect->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_floor_effect", Boss_floor_effect);

		std::shared_ptr<Texture> Bossflooreffect02 =
			Resources::Load<Texture>(L"Bossflooreffect02_txt", L"..\\Resources\\Texture\\BossScene\\central light.png");

		std::shared_ptr<Material> Boss_floor_effect_02 = std::make_shared<Material>();
		Boss_floor_effect_02->SetShader(spriteShader);
		Boss_floor_effect_02->SetTexture(Bossflooreffect02);
		Boss_floor_effect_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_floor_effect_02", Boss_floor_effect_02);


		//
		std::shared_ptr<Texture> BossTopCenter =
			Resources::Load<Texture>(L"Boss_Top_Center01", L"..\\Resources\\Texture\\BossScene\\ruin_top_center.png");

		std::shared_ptr<Material> Boss_Top_c_01 = std::make_shared<Material>();
		Boss_Top_c_01->SetShader(spriteShader);
		Boss_Top_c_01->SetTexture(BossTopCenter);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Top_c_01", Boss_Top_c_01);


		//
		std::shared_ptr<Texture> BossTopLeft =
			Resources::Load<Texture>(L"Boss_Top_Left01", L"..\\Resources\\Texture\\BossScene\\ruin_top_l.png");

		std::shared_ptr<Material> Boss_Top_l_01 = std::make_shared<Material>();
		Boss_Top_l_01->SetShader(spriteShader);
		Boss_Top_l_01->SetTexture(BossTopLeft);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Top_l_01", Boss_Top_l_01);


		//
		std::shared_ptr<Texture> BossTopRight =
			Resources::Load<Texture>(L"Boss_Right01", L"..\\Resources\\Texture\\BossScene\\ruin_top_r.png");

		std::shared_ptr<Material> Boss_Top_Right_01 = std::make_shared<Material>();
		Boss_Top_Right_01->SetShader(spriteShader);
		Boss_Top_Right_01->SetTexture(BossTopRight);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_Top_Right_01", Boss_Top_Right_01);


		//
		std::shared_ptr<Texture> Bosslight =
			Resources::Load<Texture>(L"Boss_light01", L"..\\Resources\\Texture\\BossScene\\ruin_light.png");

		std::shared_ptr<Material> Boss_light_01 = std::make_shared<Material>();
		Boss_light_01->SetShader(spriteShader);
		Boss_light_01->SetTexture(Bosslight);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_light_01", Boss_light_01);

		//
		std::shared_ptr<Texture> BosswallL =
			Resources::Load<Texture>(L"Boss_wall_L01", L"..\\Resources\\Texture\\BossScene\\wall_l.png");

		std::shared_ptr<Material> Boss_wall_L_01 = std::make_shared<Material>();
		Boss_wall_L_01->SetShader(spriteShader);
		Boss_wall_L_01->SetTexture(BosswallL);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_wall_L_01", Boss_wall_L_01);

	
			//
		std::shared_ptr<Texture> BosswallR =
		Resources::Load<Texture>(L"Boss_wall_R01", L"..\\Resources\\Texture\\BossScene\\wall_r.png");

		std::shared_ptr<Material> Boss_wall_R_01 = std::make_shared<Material>();
		Boss_wall_R_01->SetShader(spriteShader);
		Boss_wall_R_01->SetTexture(BosswallR);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Boss_wall_R_01", Boss_wall_R_01);

		std::shared_ptr<Texture> GrimmBG01 =
			Resources::Load<Texture>(L"Grimm_BG_01_txt", L"..\\Resources\\Texture\\BossScene\\grimm_BG01.png");

		std::shared_ptr<Material> Grimm_BG_01 = std::make_shared<Material>();
		Grimm_BG_01->SetShader(spriteShader);
		Grimm_BG_01->SetTexture(GrimmBG01);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_BG_01", Grimm_BG_01);



		std::shared_ptr<Texture> GrimmInFloor01 =
			Resources::Load<Texture>(L"GrimminFloor01_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_floor_01.png");

		std::shared_ptr<Material> Grimm_In_Floor_01 = std::make_shared<Material>();
		Grimm_In_Floor_01->SetShader(spriteShader);
		Grimm_In_Floor_01->SetTexture(GrimmInFloor01);
		//Boss_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_In_Floor_01", Grimm_In_Floor_01);

		std::shared_ptr<Texture> GrimmroundBG =
			Resources::Load<Texture>(L"Grimm_round_BG_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_round_BG.png");

		std::shared_ptr<Material> Grimm_round_BG = std::make_shared<Material>();
		Grimm_round_BG->SetShader(spriteShader);
		Grimm_round_BG->SetTexture(GrimmroundBG);
		Grimm_round_BG->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_round_BG", Grimm_round_BG);


		std::shared_ptr<Texture> GrimmroundBG02 =
			Resources::Load<Texture>(L"GrimmroundBG02_txt", L"..\\Resources\\Texture\\BossScene\\Grimm_round_BG_02.png");

		std::shared_ptr<Material> Grimm_round_BG_02 = std::make_shared<Material>();
		Grimm_round_BG_02->SetShader(spriteShader);
		Grimm_round_BG_02->SetTexture(GrimmroundBG02);
		Grimm_round_BG_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Grimm_round_BG_02", Grimm_round_BG_02);



#pragma endregion

#pragma region Light

		std::shared_ptr<Texture> StartLight
			= Resources::Load<Texture>(L"Light01", L"..\\Resources\\Texture\\StartScene\\Light.png");

		std::shared_ptr<Material> Start_Light = std::make_shared<Material>();
		Start_Light->SetShader(spriteShader);
		Start_Light->SetTexture(StartLight);
		Start_Light->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Start_Light", Start_Light);


#pragma endregion



#pragma region AbyssScene


		std::shared_ptr<Texture> AbyssBG01
			= Resources::Load<Texture>(L"AbyssBG01_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_BG01.png");

		std::shared_ptr<Material> Abyss_bg_01 = std::make_shared<Material>();
		Abyss_bg_01->SetShader(spriteShader);
		Abyss_bg_01->SetTexture(AbyssBG01);
		//Start_BGMR->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_bg_01", Abyss_bg_01);



		std::shared_ptr<Texture> AbyssBGceil01
			= Resources::Load<Texture>(L"AbyssBGceil01_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_BG_ceil.png");

		std::shared_ptr<Material> Abyss_BG_ceil_01 = std::make_shared<Material>();
		Abyss_BG_ceil_01->SetShader(spriteShader);
		Abyss_BG_ceil_01->SetTexture(AbyssBGceil01);
		Abyss_BG_ceil_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_BG_ceil_01", Abyss_BG_ceil_01);


		std::shared_ptr<Texture> AbyssWall
			= Resources::Load<Texture>(L"AbyssWall_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_wall.png");

		std::shared_ptr<Material> Abyss_Wall = std::make_shared<Material>();
		Abyss_Wall->SetShader(spriteShader);
		Abyss_Wall->SetTexture(AbyssWall);
		Abyss_Wall->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Wall", Abyss_Wall);

		std::shared_ptr<Texture> Abysslayered01
			= Resources::Load<Texture>(L"Abysslayered01_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_layered_01.png");

		std::shared_ptr<Material> Abyss_layered_01 = std::make_shared<Material>();
		Abyss_layered_01->SetShader(spriteShader);
		Abyss_layered_01->SetTexture(Abysslayered01);
		Abyss_layered_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_layered_01", Abyss_layered_01);


		std::shared_ptr<Texture> AbyssBGceilflat
			= Resources::Load<Texture>(L"AbyssBGceilflat_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_BG_ceil_flat.png");

		std::shared_ptr<Material> Abyss_BG_ceil_flat = std::make_shared<Material>();
		Abyss_BG_ceil_flat->SetShader(spriteShader);
		Abyss_BG_ceil_flat->SetTexture(AbyssBGceilflat);
		Abyss_BG_ceil_flat->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_BG_ceil_flat", Abyss_BG_ceil_flat);



		std::shared_ptr<Texture> AbyssBGceilflat02
			= Resources::Load<Texture>(L"AbyssBGceilflat02_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_plat2.png");

		std::shared_ptr<Material> Abyss_BG_flat_02 = std::make_shared<Material>();
		Abyss_BG_flat_02->SetShader(spriteShader);
		Abyss_BG_flat_02->SetTexture(AbyssBGceilflat02);
		Abyss_BG_flat_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_BG_flat_02", Abyss_BG_flat_02);

		std::shared_ptr<Texture> AbyssBGceilflat03
			= Resources::Load<Texture>(L"AbyssBGceilflat03_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_BG_ceil_falt3.png");

		std::shared_ptr<Material> Abyss_BG_flat_03 = std::make_shared<Material>();
		Abyss_BG_flat_03->SetShader(spriteShader);
		Abyss_BG_flat_03->SetTexture(AbyssBGceilflat03);
		Abyss_BG_flat_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_BG_flat_03", Abyss_BG_flat_03);

		std::shared_ptr<Texture> AbyssBG_black
			= Resources::Load<Texture>(L"AbyssBG_black_txt", L"..\\Resources\\Texture\\Abyss\\abyss_black_solid.png");

		std::shared_ptr<Material> Abyss_bg_black = std::make_shared<Material>();
		Abyss_bg_black->SetShader(spriteShader);
		Abyss_bg_black->SetTexture(AbyssBG_black);
		Abyss_bg_black->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_bg_black", Abyss_bg_black);


		std::shared_ptr<Texture> AbyssFloor01
			= Resources::Load<Texture>(L"AbyssFloor01_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_floor_01.png");

		std::shared_ptr<Material> Abyss_Floor_01 = std::make_shared<Material>();
		Abyss_Floor_01->SetShader(spriteShader);
		Abyss_Floor_01->SetTexture(AbyssFloor01);
		Abyss_Floor_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Floor_01", Abyss_Floor_01);


		std::shared_ptr<Texture> AbyssFloor02
			= Resources::Load<Texture>(L"AbyssFloor02_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_floor_02.png");

		std::shared_ptr<Material> Abyss_Floor_02 = std::make_shared<Material>();
		Abyss_Floor_02->SetShader(spriteShader);
		Abyss_Floor_02->SetTexture(AbyssFloor02);
		Abyss_Floor_02->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Abyss_Floor_02", Abyss_Floor_02);


		std::shared_ptr<Texture> AbyssFloor03
			= Resources::Load<Texture>(L"AbyssFloor03_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_floor_03.png");

		std::shared_ptr<Material> Abyss_Floor_03 = std::make_shared<Material>();
		Abyss_Floor_03->SetShader(spriteShader);
		Abyss_Floor_03->SetTexture(AbyssFloor03);
		Abyss_Floor_03->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Abyss_Floor_03", Abyss_Floor_03);



		std::shared_ptr<Texture> AbyssFloor04
			= Resources::Load<Texture>(L"AbyssFloor04_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_floor_04.png");

		std::shared_ptr<Material> Abyss_Floor_04 = std::make_shared<Material>();
		Abyss_Floor_04->SetShader(spriteShader);
		Abyss_Floor_04->SetTexture(AbyssFloor04);
		Abyss_Floor_04->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Abyss_Floor_04", Abyss_Floor_04);

		std::shared_ptr<Texture> AbyssCFloor01
			= Resources::Load<Texture>(L"Abyss_c_Floor01_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_C_Floor_01.png");

		std::shared_ptr<Material> Abyss_C_Floor_01 = std::make_shared<Material>();
		Abyss_C_Floor_01->SetShader(spriteShader);
		Abyss_C_Floor_01->SetTexture(AbyssCFloor01);
		Abyss_C_Floor_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_C_Floor_01", Abyss_C_Floor_01);

		std::shared_ptr<Texture> AbyssCFloor02
			= Resources::Load<Texture>(L"Abyss_c_Floor02_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_C_Floor_02.png");

		std::shared_ptr<Material> Abyss_C_Floor_02 = std::make_shared<Material>();
		Abyss_C_Floor_02->SetShader(spriteShader);
		Abyss_C_Floor_02->SetTexture(AbyssCFloor02);
		Abyss_C_Floor_02->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_C_Floor_02", Abyss_C_Floor_02);


		std::shared_ptr<Texture> AbyssCFloor03
			= Resources::Load<Texture>(L"Abyss_c_Floor03_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_C_Floor_03.png");

		std::shared_ptr<Material> Abyss_C_Floor_03 = std::make_shared<Material>();
		Abyss_C_Floor_03->SetShader(spriteShader);
		Abyss_C_Floor_03->SetTexture(AbyssCFloor03);
		Abyss_C_Floor_03->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_C_Floor_03", Abyss_C_Floor_03);




		std::shared_ptr<Texture> AbyssPrickle
			= Resources::Load<Texture>(L"AbyssPrickle_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_prickle.png");

		std::shared_ptr<Material> Abyss_Prickle_01 = std::make_shared<Material>();
		Abyss_Prickle_01->SetShader(spriteShader);
		Abyss_Prickle_01->SetTexture(AbyssPrickle);
		Abyss_Prickle_01->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Prickle_01", Abyss_Prickle_01);

		std::shared_ptr<Texture> AbyssPrickleunder
			= Resources::Load<Texture>(L"AbyssPrickleunder_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_prickle_under.png");

		std::shared_ptr<Material> Abyss_Prickle_under = std::make_shared<Material>();
		Abyss_Prickle_under->SetShader(spriteShader);
		Abyss_Prickle_under->SetTexture(AbyssPrickleunder);
		Abyss_Prickle_under->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Prickle_under", Abyss_Prickle_under);

		std::shared_ptr<Texture> AbyssPrickleright
			= Resources::Load<Texture>(L"AbyssPrickleright_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_prickle_right.png");

		std::shared_ptr<Material> Abyss_Prickle_right = std::make_shared<Material>();
		Abyss_Prickle_right->SetShader(spriteShader);
		Abyss_Prickle_right->SetTexture(AbyssPrickleright);
		Abyss_Prickle_right->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Prickle_right", Abyss_Prickle_right);



		std::shared_ptr<Texture> AbyssPrickleover
			= Resources::Load<Texture>(L"AbyssPrickleover_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_prickle_over.png");

		std::shared_ptr<Material> Abyss_Prickle_over = std::make_shared<Material>();
		Abyss_Prickle_over->SetShader(spriteShader);
		Abyss_Prickle_over->SetTexture(AbyssPrickleover);
		Abyss_Prickle_over->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Abyss_Prickle_over", Abyss_Prickle_over);


		std::shared_ptr<Texture> AbyssPricklceil
			= Resources::Load<Texture>(L"AbyssPricklceil_txt", L"..\\Resources\\Texture\\Abyss\\Abyss_prickle_ceil.png");

		std::shared_ptr<Material> Abyss_Prickle_ceil = std::make_shared<Material>();
		Abyss_Prickle_ceil->SetShader(spriteShader);
		Abyss_Prickle_ceil->SetTexture(AbyssPricklceil);
		Abyss_Prickle_ceil->SetRenderingMode(eRenderingMode::Transparent);

		Resources::Insert(L"Abyss_Prickle_ceil", Abyss_Prickle_ceil);



		std::shared_ptr<Texture> Radiancein
			= Resources::Load<Texture>(L"Radiance_in_txt", L"..\\Resources\\Texture\\Abyss\\Radiance_in.png");

		std::shared_ptr<Material> Radiance_In = std::make_shared<Material>();
		Radiance_In->SetShader(spriteShader);
		Radiance_In->SetTexture(Radiancein);
		Radiance_In->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radiance_In", Radiance_In);

		std::shared_ptr<Texture> Radiancelayered
			= Resources::Load<Texture>(L"Radiancelayered_txt", L"..\\Resources\\Texture\\Abyss\\Radiance_layered.png");

		std::shared_ptr<Material> Radiance_layered = std::make_shared<Material>();
		Radiance_layered->SetShader(spriteShader);
		Radiance_layered->SetTexture(Radiancelayered);
		Radiance_layered->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Radiance_layered", Radiance_layered);

#pragma endregion

	




	}

	void LoadMaterial()
	{
		//sprite
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");

		
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial", material);
		
		 texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		 material = std::make_shared<Material>();
		 material->SetShader(shader);
		 material->SetTexture(texture);
		 material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SpriteMaterial02", material);

		//spriteAnimationShader
			shader
				= Resources::Find<Shader>(L"SpriteAnimationShader");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SpriteAnimaionMaterial", material);

		//grid
		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		//debug
		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		//Paricle
		shader
			= Resources::Find<Shader>(L"ParticleShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);

		std::shared_ptr<Texture> particleTexx
			= Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(particleTexx);
		Resources::Insert(L"ParticleMaterial", material);

		//Monster
		shader
			= Resources::Find<Shader>(L"MonsterShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"MonsterMaterial", material);


		//Player
		shader
			= Resources::Find<Shader>(L"PlayerShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"PlayerMaterial", material);

		//fade
		shader
			= Resources::Find<Shader>(L"FadeShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"FadeMaterial", material);

		//fade
		shader
			= Resources::Find<Shader>(L"UIShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIMaterial", material);


	}


	
	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		LoadText();
		SetUpState();
		LoadMaterial();


		//texture->BindShader(eShaderStage::PS, 0);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightAttributes.data(), lightAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);

	}


	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void PushDebugMeshInfo(DebugMesh& mesh)
	{
		debugMeshs.push_back(mesh);
	}


	void Render()
	{
		BindNoiseTexture();
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
	}

}