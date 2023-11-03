#pragma once


namespace Ak
{
	class Player;

	class PlayerWeapon :
		public GameObject
	{

	public:

		PlayerWeapon();
		~PlayerWeapon();



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		void SetPlayer(GameObject* _player)
		{
			m_pPlayer = _player;
		}


		GameObject* GetPlayer()
		{
			return m_pPlayer;
		}


	private:

		GameObject* m_pPlayer;

		


	};



}