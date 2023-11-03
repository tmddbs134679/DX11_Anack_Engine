#pragma once
#include "../Engine_SOURCE/AkGameObject.h"

namespace gui
{
	class DebugObject
		: public Ak::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};


}