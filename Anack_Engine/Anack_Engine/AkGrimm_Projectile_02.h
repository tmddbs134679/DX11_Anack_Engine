#pragma once
#include "AkGameObject.h"

namespace Ak
{
	class Grimm_Projectile_02 :
		public GameObject
	{
	public:

		Grimm_Projectile_02();
		virtual ~Grimm_Projectile_02();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:

		Vector2 CalculateDirection(float angle);

		void SetInt(int _int)
		{
			iObj = _int;
		}

		void SetMonPos(Vector2 _vec)
		{
			m_vMonPos = _vec;
		}

		void SetAngle(float _ang)
		{
			m_fAngle = _ang;
		}


	private:
		int iObj;
		Vector2  m_vMonPos;
		float fTime;

		int m_iCreatePJ;

		float m_fAngle;


	};



}