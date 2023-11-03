#pragma once
#include "AkEntity.h"
#include "AkComponent.h"
#include "AkScript.h"
#include "Akstruct.h"
#include "AkCamera.h"
#include "AkTransform.h"

namespace Ak
{
	using  namespace math;
	class GameObject
		: public Entity
	{
	public:

		struct GameObjectStatus
		{
			Vector2 Pos;
			float Scale;
		};

		GameObject();
		virtual ~GameObject();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	
		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}


		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);

				if (component != nullptr)
					comps.push_back(component);

			}

			return comps;
		}



		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			//comp->Initialize();
			
			
			return comp;
		}

		void SetLayerType(eLayerType _type)
		{
			mLayerType = _type;
		}


		//GroundSide = Ground와 옆쪽 충돌 시 Sound안나게 설정
		bool GetGroundSide()
		{
			return m_bGroundSide;
		}

		void GroundSideOn()
		{
			m_bGroundSide = true;
		}

		void GroundSideOff()
		{
			m_bGroundSide = false;
		}

		void SetState(eState _state)
		{
			mState = _state;
		}

		void GroundTrap()
		{
			m_bGroundTrap = true;
		}

		bool GetGroundTrap()
		{
			return m_bGroundTrap;
		}

		eState GetState()
		{
			return mState;
		}

		eLayerType GetLayerType()
		{
			return mLayerType;
		}


		void CoinHave()
		{
			m_bhaveCoin = true;
		}

		bool GetCoin()
		{
			return m_bhaveCoin;
		}

		void SetPlayerShadow(bool _b)
		{
			m_bPlayerShadow = _b;
		}

	public:

		Transform* mTransform;

	
		bool m_bPlayerShadow;

	private:
		eState	mState;
	std::vector<Component*> mComponents;
	std::vector<Script*>	mScripts;

	eLayerType				mLayerType;


	bool m_bGroundSide;

	bool m_bhaveCoin;

	bool m_bGroundTrap;

	
	};
}