#pragma once
#include "AkScript.h"
#include "../Anack_Engine/AkPlayerWeapon.h"
#include "AkUI_HUD.h"
namespace Ak
{
	class PlayerAttackScript :
		public Script
	{

	public:
		PlayerAttackScript();
		~PlayerAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other) override;
		virtual	void OnCollision(Collider2D* _other) override;
		virtual	void OnCollisionExit(Collider2D* _other) override;


		void SetPlayerWeapon(PlayerWeapon* _weapon)
		{
			m_pPlayerWeapon = _weapon;
		}


		void SetHUD(UI_HUD* _hud)
		{
			m_HUD = _hud;
		}

	private:
		PlayerWeapon* m_pPlayerWeapon;
	


	

		UI_HUD* m_HUD;


	};
}