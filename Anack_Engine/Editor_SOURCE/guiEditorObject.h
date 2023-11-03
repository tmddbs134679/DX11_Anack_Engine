#pragma once
#include "../Engine_SOURCE/AkGameObject.h"


namespace gui
{
	class EditorObject
		: public Ak::GameObject	
	{
	public:
		EditorObject();
		~EditorObject();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};


}
