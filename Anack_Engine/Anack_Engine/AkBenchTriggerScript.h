#pragma once
#include "AkScript.h"


namespace Ak
{
	class BenchTriggerScript :
		public Script
	{

	public:

		BenchTriggerScript();
		virtual ~BenchTriggerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other) {};
		virtual	void OnCollision(Collider2D* _other) {};
		virtual	void OnCollisionExit(Collider2D* _other) {};
	};


}
