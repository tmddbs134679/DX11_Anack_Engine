#include "AkCollider2D.h"
#include "AkGameObject.h"
#include "AkRenderer.h"

namespace Ak 
{

	UINT Collider2D::mColliderNumber = 0;

	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, m_bVisible(false)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}

	Collider2D::~Collider2D()
	{

	}

	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		
		mCenter = GetCenter();

	}

	void Collider2D::Update()
	{

	}

	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;
		
		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(mesh);
		
		

	}

	void Collider2D::Render()
	{
		
		
	}

	void Collider2D::OnCollisionEnter(Collider2D* _other)
	{
		m_strCollisionOtherName = _other->GetName();

		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(_other);
		}
	}

	void Collider2D::OnCollision(Collider2D* _other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollision(_other);
		}
	}

	void Collider2D::OnCollisionExit(Collider2D* _other)
	{

		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(_other);
		}
	}


}