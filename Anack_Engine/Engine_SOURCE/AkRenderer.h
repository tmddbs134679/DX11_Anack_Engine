#pragma once
#include "Anack_Engine.h"
#include"AkGraphicDevice_Dx11.h"
#include "AkMesh.h"
#include "AkShader.h"
#include "AkConstantBuffer.h"
#include "AkCamera.h"
#include "AkLight.h"


using namespace Ak::math;
using namespace Ak::graphics;

namespace renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_Grid)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2		spriteLeftTop;
		Vector2		sprtieSize;
		Vector2		spriteOffset;
		Vector2		atlasSize;
		UINT		animationType;
		bool		bUI;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT particleElementCount;
		float particleElpasedTime;
		float particleDeltaTime;
		float particleStartSpeed;
		Vector4 particleDirection;
		float particleDestoryTime;
		Vector3 particleOffset;
		Vector3 particlePos;
		float particleRandom;
		//float particleStartSize;
		//float particleEndSize;
		bool bParticleTest;

		float particleStartRotation;
		float particleRotationSpeed;

		float particleScale;

		float particleAngle1;
		float particleAngle2;
		bool  particleRandomDirection;


	};


	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	CBUFFER(MonsterCB, CBSLOT_MONSTER)
	{
		bool bTest;
	};

	CBUFFER(PlayerCB, CBSLOT_PLAYER)
	{
		bool bTest2;
	};


	CBUFFER(FadeCB, CBSLOT_MONSTER)
	{
		bool bFadeIn;
		char padding[3];
		float fcolorz;
	};

	CBUFFER(UICB, CBSLOT_UI)
	{
		Vector2		spriteLeftTop;
		Vector2		sprtieSize;
		Vector2		spriteOffset;
		Vector2		atlasSize;
		UINT		animationType;
	};

	CBUFFER(ColliderCB, CBSLOT_COLLIDER)
	{
		bool bVisible;
	};


	void Initialize();
	void BindLights();
	void Release();
	void Render();

	void PushDebugMeshAttribute(DebugMesh mesh);

	extern std::vector<Ak::Light*> lights;
	extern Ak::Camera* mainCamera;
	extern std::vector<Ak::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;
	

	extern Ak::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];


	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
}
