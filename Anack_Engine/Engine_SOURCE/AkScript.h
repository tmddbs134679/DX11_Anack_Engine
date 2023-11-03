#pragma once
#include "AkComponent.h"
#include "AkCollider2D.h"

namespace Ak

{
	class Script
		: public Component
	{
	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other) {};
		virtual	void OnCollision(Collider2D* _other) {};
		virtual	void OnCollisionExit(Collider2D* _other) {};
		
	private:
	};

}
