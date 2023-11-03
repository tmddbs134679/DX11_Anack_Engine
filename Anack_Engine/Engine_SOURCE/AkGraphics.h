#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")


#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_Grid				2
#define CBSLOT_ANIMATION2D		3
#define CBSLOT_PARTICLE			4
#define CBSLOT_NOISE			5
#define CBSLOT_MONSTER			6
#define CBSLOT_FADE				7
#define CBSLOT_UI				8
#define CBSLOT_PLAYER			9
#define CBSLOT_COLLIDER			10


namespace Ak::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		END
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Animator,
		Particle,
		Noise,
		Monster,
		Fade,
		Ui,
		Player,
		Collider,
		END
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		END
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		END,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		END
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		END
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		END
	};

	//ShaderResourceView
	enum class eViewType
	{
		None,
		SRV,
		UAV,
		End
	};



	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
	};


	struct LightAttribute
	{
		math::Vector4	color;
		math::Vector4	position;
		math::Vector4	direction;

		enums::eLightType type;
		float radius;
		float angle;
		int	  pad;

	};

	struct Particle
	{
		math::Vector4 position;
		math::Vector4 direction;

		float endTime;
		float time;
		float speed;
		UINT active;
		float size;
		int pad;
	};

	struct ParticleShared
	{
		UINT sharedActiveCount;
	};

}