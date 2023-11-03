#pragma once
#include "AkScript.h"


namespace Ak
{
	class GrimmTriggerScript :
		public Script
	{
	public:

		GrimmTriggerScript();
		~GrimmTriggerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual	void OnCollisionEnter(Collider2D* _other);
		virtual	void OnCollision(Collider2D* _other);
		virtual	void OnCollisionExit(Collider2D* _other);

	};


}
