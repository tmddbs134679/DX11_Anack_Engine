#pragma once


namespace Ak::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		RigidBody,
		Gravity,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Player,
		PlayerAttack,
		Monster,
		MonsterAttack,
		Light,
		BackGround,
		Ground,
		LayeredObj,
		Trigger,
		UI,
		Camera,
		NPC,
		End = 16
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Animation,
		ComputeShader,
		Mesh,
		AudioClip,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End
	};


	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End
	};


	enum class eMoveDir
	{
		Left = 0,
		Top,
		Right,
		Bottom,
		End
	};


	enum class EVENT_TYPE
	{
		CREATE_OBJECT,
		DELETE_OBJECT,
		SCENE_CHANGE,
		CHANGE_AI_STATE,
		END
	};




}