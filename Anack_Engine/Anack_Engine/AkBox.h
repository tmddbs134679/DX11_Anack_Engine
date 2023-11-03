#pragma once
#include "AkGameObject.h"
#include "AkScene.h"
#include "AkAnimator.h"

namespace Ak
{
	class Box :
		public GameObject
	{

	public:

		Box();
		virtual ~Box();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void SetOpenCount(int _cnt)
		{
			m_iOpenCnt = _cnt;
		}
		void SetScene(Scene* _scene)
		{
			m_pCurScene = _scene;
		}

	private:

		int m_iOpenCnt;

		Scene* m_pCurScene;

		bool m_bBoxOpen;
		bool m_bCreateCoin;

		Animator* mAnimator;
		std::shared_ptr<AudioClip>  m_AC;

	};



}