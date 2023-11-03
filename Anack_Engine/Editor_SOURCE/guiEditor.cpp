#include "guiEditor.h"
#include "../Engine_SOURCE/AkMesh.h"
#include "../Engine_SOURCE/AkResources.h"
#include "../Engine_SOURCE/AkTransform.h"
#include "../Engine_SOURCE/AkMaterial.h"
#include "../Engine_SOURCE/AkRenderer.h"
#include "../Engine_SOURCE/AkMeshRenderer.h"
#include "../Anack_Engine/AkGridScript.h"

namespace gui
{
	using namespace Ak::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};



	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Ak::Mesh> mesh = Ak::Resources::Find<Ak::Mesh>(L"DebugRect");
		std::shared_ptr<Ak::Material> material = Ak::Resources::Find<Ak::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Ak::Transform>();

		Ak::MeshRenderer* mr = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Ak::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);
	
		EditorObject* grid = new EditorObject();
		grid->SetName(L"Gird");

		mr = grid->AddComponent<Ak::MeshRenderer>();
		mr->SetMesh(Ak::Resources::Find<Ak::Mesh>(L"RectMesh"));
		mr->SetMaterial(Ak::Resources::Find<Ak::Material>(L"GridMaterial"));
		Ak::GridScript* gridSc = grid->AddComponent<Ak::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();

	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const Ak::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshs.clear();
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}


		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const Ak::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		Ak::Transform* tr = debugObj->GetComponent<Ak::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();
		
		//main camera
		Ak::Camera* mainCamera = renderer::mainCamera;

		Ak::Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
		Ak::Camera::SetProjectionMatrix(mainCamera->GetProjectionMatrix());

		debugObj->Render();

	}

}