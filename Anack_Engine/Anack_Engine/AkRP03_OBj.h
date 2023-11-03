#pragma once
#include "AkGameObject.h"
#include "AkRadiance_Projectile_03.h"



namespace Ak
{
	class RP03_OBj :
		public GameObject
	{

	public:
		enum RP03Pattern
		{
			pattern01 = 1,
			pattern02,
			pattern03,
		};

		RP03_OBj();
		~RP03_OBj();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:

		void ChangePattern();

		void Random();
		void AttackOn()
		{
			m_bAttack = true;
		}

		std::vector<Radiance_Projectile_03*> GetRP3()
		{
			return m_vRP;
		}

	
		
		void PatternPlus()
		{
			static_cast<RP03Pattern>(m_EPattern) + 1;

			if (static_cast<RP03Pattern>(m_EPattern) > 3)
				m_EPattern = RP03Pattern::pattern01;
		}

	private:

		std::vector<Radiance_Projectile_03*> m_vRP;

		RP03Pattern m_EPattern;

	


		float m_fTime;


		bool m_bAttack;

		int m_iPosX;
	
	};



}