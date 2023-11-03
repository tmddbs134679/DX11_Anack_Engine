#pragma once
#include "AkScript.h"


namespace Ak
{

	class GroundScript :
		public Script
	{
	
	public:
		GroundScript();
		virtual ~GroundScript();



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollision(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:


	};


}