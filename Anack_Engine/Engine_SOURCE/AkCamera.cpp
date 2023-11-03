#include "AkCamera.h"
#include "AkTransform.h"
#include "AkGameObject.h"
#include "AkApplication.h"
#include "AkRenderer.h"
#include "AkScene.h"
#include "AkSceneManager.h"
#include "AkMeshRenderer.h"
#include "AkTime.h"

extern Ak::Application application;

namespace Ak
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			<= b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}


	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perperctive)
		, mAspectRatio(1.f)
		, mNear(1.f)
		, mFar(1000.f)
		, mSize(5.f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
		, m_pTargetObj(nullptr)
		, m_fTime(1.f)
		, m_fAccTime(1.f)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{

	}

	void Camera::Update()
	{

	}

	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();

	}

	void Camera::Render()
	{
		// Opaque : ������, CutOut : ����, Transparent : ����

		View = mView;
		Projection = mProjection;

		//�з��۾�
		AlphaSortGameObjects();
		//������ ��ü�� ���� �� ������� �׷��� -> ������ ��ü���� ���� ���ļ� ������ �Ǵ� ��� ���� �޶����� ����
		ZSortTransparencyGameObjects();
		RenderOpaque();

		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}


	//������ǥ -> ī�޶���ǥ
	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		//View Rotation Matrix
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Forword();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x;  viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y;  viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z;  viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}
	

	//3D -> 2D �������� ��ȯ�ϴ� ��� 
	//������� ���� = Perspective : ���������� ����Ͽ� �ݿ�, OrthoGraphic : ����ȿ��x
	bool Camera::CreateProjectionMatrix(eProjectionType _type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;

		if (_type == eProjectionType::OrthoGraphic)
		{
			float OrthorGraphicRatio = mSize / 1000.f;
			width *= OrthorGraphicRatio;
			height *= OrthorGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.f, mAspectRatio, mNear, mFar);
		}

		
		return true;
	}

	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}


	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs = layer.GetGameObjects();
				//layer�� ���ӿ�����Ʈ�� �������

				DivideAlphaBlendGameObjects(gameObjs);
			}
		}
	}

	//���ϴ� ������Ʈ�鸸 ���̰� ���� -> ?ī�޶� ��ü���� ����ϴ� ���̾� ����ũ�� �����Ͽ� �������� ������Ʈ�� ������.
	void Camera::TurnLayerMask(eLayerType _type, bool _enable)
	{
		mLayerMask.set((UINT)_type, _enable);
	}

	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderCutOut()
	{

		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != eState::Active)
				continue;

			gameObj->Render();

		}
	}

	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != eState::Active)
				continue;


			gameObj->Render();

		}
	}
	

		
	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
				, mCutOutGameObjects.end()
				, CompareZSort);

		std::sort(mTransparentGameObjects.begin()
				, mTransparentGameObjects.end()
				, CompareZSort);
		
	}	
		
	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> _gameObjs)
	{	
		for (GameObject* obj : _gameObjs)
		{
			//������ ������Ʈ�� ���ٸ�
			MeshRenderer* mr = obj->GetComponent<MeshRenderer>();
			if (mr == nullptr)
				continue;

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();

			switch (mode)
			{
				//������
			case Ak::graphics::eRenderingMode::Opaque:

				mOpaqueGameObjects.push_back(obj);

				break;
				//����
			case Ak::graphics::eRenderingMode::CutOut:

				mCutOutGameObjects.push_back(obj);

				break;
				//������   ex) ��ü�� �׸���, ����, ����, ��ƼŬ ȿ�� ��
			case Ak::graphics::eRenderingMode::Transparent:

				mTransparentGameObjects.push_back(obj);

				break;
			default:
				break;
			}
		}
	}	
		
	void Camera::EnableDepthStencilState()
	{	
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}	
		
	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];

		GetDevice()->BindDepthStencilState(dsState.Get());
	}


	void Camera::CalDiff()
	{
		m_fAccTime += Time::DeltaTime();

		if (m_fTime <= m_fAccTime)
		{
			m_vCurLookAt = m_LookAt;
		}
		else
		{
			Vector2 vLookDir = m_LookAt - m_vPrevLookAt;

			float fLen = (float(sqrt(vLookDir.x * vLookDir.x + vLookDir.y * vLookDir.y)));

			assert(fLen != 0.f);

			vLookDir.x /= fLen;
			vLookDir.y /= fLen;

			if (!(vLookDir == Vector2(0.f, 0.f)))
			{
				m_vCurLookAt = m_vPrevLookAt + vLookDir * m_fSpeed * Time::DeltaTime();
			}

		}

		Vector2 vResolution = Vector2(application.GetWidth(), application.GetHeight());
		Vector2 vCenter = vResolution / 2;

		m_vDiff = m_vCurLookAt - vCenter;
		m_vPrevLookAt = m_vCurLookAt;

	}

}