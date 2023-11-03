#pragma once
#include "../Engine_SOURCE/Commoninclude.h"
#include "../Engine_SOURCE/Anack_Engine.h"
#include "guiWidget.h"
#include "../Engine_SOURCE/AkGraphics.h"
#include "guiDebugObject.h"
#include "guiEditorObject.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const Ak::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;

	};



}