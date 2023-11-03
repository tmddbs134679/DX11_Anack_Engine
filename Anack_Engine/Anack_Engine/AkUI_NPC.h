#pragma once
#include "AkGameObject.h"


namespace Ak
{
	class UI_NPC :
		public GameObject
	{

	public:
		UI_NPC();
		virtual ~UI_NPC();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void SetGrimmTrigger(bool _b)
		{
			m_bGrimmGrigger = _b;
		}
	private:

		
	std::vector<GameObject*> m_vObj;

	bool m_bGrimmGrigger;


	};



}