#pragma once

#include "Anack_Engine.h"

namespace Ak
{
#define LAYER_MAX (UINT)eLayerType::End
	using namespace enums;

	class Collider2D;

	class CollisionManager
	{
	public:
		union ColliderID
		{
			struct 
			{
				UINT left;
				UINT right;
			};
			UINT64 id;
		};


		static void Initialize();
		static void Update();
		static void LayerCollision(eLayerType _left, eLayerType _right);
		static void ColliderCollision(Collider2D* _left, Collider2D* _right);
		static bool Intersect(Collider2D* _left, Collider2D* _right);
		static bool CircleIntersect(Collider2D* _left, Collider2D* _right);


		static void SetLayer(eLayerType _left, eLayerType _right, bool _enable);
		static void Clear();

	private:

		static std::bitset<LAYER_MAX> mMatrix[LAYER_MAX];
		static std::map<UINT64, bool> mCollisionMap;


	};

}