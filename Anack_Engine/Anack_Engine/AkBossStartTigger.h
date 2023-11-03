#pragma once
#include "AkGameObject.h"
#include "AkBrumm.h"

namespace Ak
{
    class BossStartTigger :
        public GameObject
    {

	public:

		BossStartTigger();
		virtual ~BossStartTigger();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	public:

		void SetBrumm(Brumm* _brumm)
		{
			m_bBrumm = _brumm;
		}
	private:
		float fTime;

		Brumm* m_bBrumm;

		
    };




}