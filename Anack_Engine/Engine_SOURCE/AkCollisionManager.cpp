#include "AkCollisionManager.h"
#include "AkScene.h"
#include "AkSceneManager.h"
#include "AkLayer.h"
#include "AkCollider2D.h"


namespace Ak
{

	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{

	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; ++column)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; ++row)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType _left, eLayerType _right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts = activeScene->GetLayer(_left).GetGameObjects();
		const std::vector<GameObject*>& rights = activeScene->GetLayer(_right).GetGameObjects();

		for (GameObject* leftobj : lefts)
		{
			Collider2D* leftCol = leftobj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftobj->GetState() != eState::Active)
				continue;

			for (GameObject* rightobj : rights)
			{
				Collider2D* rightCol = rightobj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftobj == rightobj)
					continue;
				if (rightobj->GetState() != eState::Active)
					continue;
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* _left, Collider2D* _right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = _left->GetColliderID();
		id.right = _right->GetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(_left, _right))
		{
			// 충돌
			if (iter->second == false)
			{
				//최초 충돌
  				_left->OnCollisionEnter(_right);
				_right->OnCollisionEnter(_left);
				iter->second = true;
			}
			else
			{
				// 충돌 중
				_left->OnCollision(_right);
				_right->OnCollision(_left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				_left->OnCollisionExit(_right);
				_right->OnCollisionExit(_left);
				iter->second = false;
			}
		}

	}

	bool CollisionManager::Intersect(Collider2D* _left, Collider2D* _right)
	{
		//충돌이론
		// 0 --- 1
		// |     |
		// 3 --- 2

		Vector3 arrLocalPos[4]
		{
			 Vector3{-0.5f, 0.5f, 0.f}   // 0
			,Vector3{0.5f, 0.5f, 0.f}	 // 1
			,Vector3{0.5f, -0.5f, 0.f}   // 2
			,Vector3{-0.5f, -0.5f, 0.f}  // 3
		};
		
		Transform* leftTr = _left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = _right->GetOwner()->GetComponent<Transform>();


		Vector3 leftPos = leftTr->GetPosition();
		leftPos.x += _left->GetCenter().x;
		leftPos.y += _left->GetCenter().y;

		Vector3 rightPos = rightTr->GetPosition();
		rightPos.x += _right->GetCenter().x;
		rightPos.y += _right->GetCenter().y;


		Matrix leftMatrix = leftTr->GetOffSetMatrix(leftPos);
		Matrix rightMatrix = rightTr->GetOffSetMatrix(rightPos);

	/*	Matrix leftMatrix = leftTr->GetMatrix();
		Matrix rightMatrix = rightTr->GetMatrix();*/

		Vector3 Axis[4] = {};

		Vector3 leftScale = Vector3(_left->GetSize().x, _left->GetSize().y, 1.f);
		//Scale-> Matrix 변환하면 다른 변환 행렬과 결합하여 객체의 변환을 쉽게 조작할 수 있다.
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;

		Vector3 rightScale = Vector3(_right->GetSize().x, _right->GetSize().y, 1.f);
		Matrix finalright = Matrix::CreateScale(rightScale);
		finalright *= rightMatrix;

		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalright);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalright);


		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalright);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalright);


		//2D상에서 Z축은 렌더링 위치를 결정하기 때문에 충돌처리를 위해 한 Z축으로 모아준다.
		for (size_t i = 0; i < 4; ++i)
			Axis[i].z = 0.0f;
		
	

		Vector3 vc = leftPos - rightPos;
		vc.z = 0.0f;

		Vector3 centerDir = vc;


		for (size_t i = 0; i < 4; ++i)
		{
			Vector3 vA = Axis[i];

			float projDistance = 0.f;

			for (size_t j = 0; j < 4; ++j)
			{
				
				projDistance += fabs(Axis[j].Dot(vA) / 2.f);
			}

			
			if (projDistance < fabs(centerDir.Dot(vA)))
				return false;
		}

		return true;
	}

	bool CollisionManager::CircleIntersect(Collider2D* _left, Collider2D* _right)
	{

		return false;
	}

	void CollisionManager::SetLayer(eLayerType _left, eLayerType _right, bool _enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)_left;
		UINT iRight = (UINT)_right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = _enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}

}