#pragma once
#include "AkComponent.h"
#include "AkGraphics.h"
#include "AkGameObject.h"

namespace Ak
{
	class Camera :
		public Component
	{
	public:

		enum class eProjectionType
		{   
			Perperctive,   //원근
			OrthoGraphic,  //등각
			NONE
		};

		Camera();
		~Camera();

	public:

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	

	public:

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType _type);
		
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType _type, bool _enable = true);

		void ZSortTransparencyGameObjects();

		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> _gameObjs);

		void EnableDepthStencilState();
		void DisableDepthStencilState();


		void AlphaSortGameObjects();
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

	public:

		void EnableLayerMasks()
		{
			mLayerMask.set();
		}

		void DisableLayerMasks()
		{
			mLayerMask.reset();
		}

	public:

		static void SetProjectionMatrix(Matrix _projection)
		{
			Projection = _projection;
		}

		static void SetGpuViewMatrix(Matrix _view)
		{
			View = _view;
		}

		void SetLookat(Vector2 _look)
		{
			m_LookAt = _look;
			float fMoveDist = (m_LookAt - m_vPrevLookAt).Length();
			m_fSpeed = fMoveDist - m_fTime;
			m_fAccTime = 0.f;
		}

		void SetTarget(GameObject* _pTarget)
		{
			m_pTargetObj = _pTarget;
		}


	public:
		

		GameObject* GetTarget()
		{
			return m_pTargetObj;
		}

		 Matrix GetViewMatrix()
		{
			return mView;
		}

		Matrix GetProjectionMatrix()
		{
			return mProjection;
		}


		float GetSize()
		{
			return mSize;
		}


		static Matrix& GetGpuViewMatrix()
		{
			return View;
		}


		static Matrix& GetGpuProjectionMatrix()
		{
			return Projection;
		}

		Vector2 GetLookAt()
		{
			return m_vCurLookAt;
		}
	
	private:
		void CalDiff();


	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;


		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;


		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;


		Vector2		m_LookAt;		//카메라
		Vector2		m_vCurLookAt;	//이전위치와 현재위치 보정 위치
		Vector2		m_vPrevLookAt;	//카메라가 보는 이전 프레임 위치
		GameObject*		m_pTargetObj;	//카메라 타겟 오브젝트
		Vector2		m_vDiff;		//해상도 중심위치와, 카메라 Lookat 값의 차이
		float		m_fTime;		//타겟을 따라가는데 걸리는 시간
		float		m_fSpeed;		//타겟을 따라가는 속도
		float		m_fAccTime;		//누적 시간


	
	};


}