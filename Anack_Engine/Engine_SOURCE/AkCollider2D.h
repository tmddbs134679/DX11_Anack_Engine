#pragma once
#include "AkComponent.h"
#include "AkTransform.h"
#include "AkRenderer.h"



namespace Ak
{
	class Collider2D :
		public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* _other);
		void OnCollision(Collider2D* _other);
		void OnCollisionExit(Collider2D* _other);

	public:
		void SetType(eColliderType _type)
		{
			mType = _type;
		}

		void SetSize(Vector2 _size)
		{
			mSize = _size;
		}
		
		void SetCenter(Vector2 _size)
		{
			mCenter = _size;
		}


	public:

		UINT GetColliderID()
		{
			return mColliderID;
		}

		Vector2 GetSize()
		{
			return mSize;
		}

		Vector3 GetPosition()
		{
			return mPosition;
		}

		Vector2 GetCenter()
		{
			return mCenter;
		}

		std::wstring GetCollisionOtherName()
		{
			return m_strCollisionOtherName;
		}

	private:

		static UINT		mColliderNumber;
		UINT			mColliderID;
		eColliderType	mType;
		Transform*		mTransform;


		Vector3			mPosition;
		Vector2			mSize;
		Vector2			mCenter;

		std::wstring   m_strCollisionOtherName;

		bool m_bVisible;


	};
}

