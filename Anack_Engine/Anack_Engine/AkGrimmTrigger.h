#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class GrimmTrigger :
		public GameObject
	{

	public:

		GrimmTrigger();
		virtual ~GrimmTrigger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



		void SetDoor(GameObject* _obj)
		{
			m_DoorObj = _obj;
		}

		GameObject* GetDoor()
		{
			return m_DoorObj;
		}

	private:


		GameObject* m_DoorObj;

	};



}