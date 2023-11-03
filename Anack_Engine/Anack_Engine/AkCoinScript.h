#pragma once
#include "AkScript.h"
#include "AkCoin.h"
namespace Ak
{
	class CoinScript :
		public Script
	{
	public:

		CoinScript();
		virtual ~CoinScript();



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollision(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetCoin(Coin* _coin)
		{
			m_Coin = _coin;
		}

	private:
		Coin* m_Coin;
	};



}