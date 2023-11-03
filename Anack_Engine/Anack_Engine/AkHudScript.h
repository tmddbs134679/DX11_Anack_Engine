#pragma once
#include "AkScript.h"


namespace Ak
{
	class HudScript :
		public Script
	{
	public:
		HudScript();
		~HudScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	//	void SetHUD(std::vector<GameObject*> _obj)
	//	{
	//		m_objHUDCount = _obj;
	//	}

	//private:



	//	std::vector<GameObject*> m_objHUDCount;
	};



}