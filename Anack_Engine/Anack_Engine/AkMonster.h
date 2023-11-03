#pragma once
#include "AkGameObject.h"
#include "Info.h"
#include "AkMonsterState.h"
#include "AkScene.h"
#include "AkBossStartTigger.h"
#include "AkRenderer.h"
#include "AkRP03_OBj.h"
#include "AkRP01_Obj.h"
#include "AkRP04_Obj01.h"
#include "AkRP04_Obj02.h"
#include "AkRP04_Obj03.h"
#include "AkRP02_Obj.h"

namespace Ak
{
	class Monster :
		public GameObject
	{

	
	public:

		Monster();
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:


	public:

		void SetMonsterInfo(const MonsterInfo& _Info)
		{
			m_MonsterInfo = _Info;
		}

		void SetMonsterHPCount(int _HP)
		{
			m_MonsterInfo.iHP_Count = _HP;
		}

	


		void SetDir(int _dir)
		{
			mDir = _dir;
		}

		void SetScene(Scene* _scene)
		{
			m_pCurScene = _scene;
		}

		void SetMonsterState(eMonsterState _estate)
		{
			m_eMonsterState = _estate;
		}

	public:

		const MonsterInfo& GetMonsterInfo()
		{
			return m_MonsterInfo;
		}


		int GetDir()
		{
			return mDir;
		}

		Scene* GetScene()
		{
			return m_pCurScene;
		}
		
		eMonsterState GetMonsterState()
		{
			return m_eMonsterState;
		}




		void SetMonsterDirX(int _dir)
		{
			m_iMonsterDirX = _dir;
		}

		void SetMonsterDirY(int _dir)
		{
			m_iMonsterDirY = _dir;
		}



		int GetMonsterDirX()
		{
			return m_iMonsterDirX;
		}

		int GetMonsterDirY()
		{
			return m_iMonsterDirY;
		}


		void SetBossTrigger(BossStartTigger* _trigger)
		{
			m_BossTrigger = _trigger;
		}

		void SetBossBG(GameObject* _obj)
		{
			m_gBossBG = _obj;
		}

		void SetLightObj(GameObject* _obj)
		{
			m_vLightObj.push_back(_obj);
		}

		void SetGrimmWall(GameObject* _obj)
		{
			m_GrimmWallObj = _obj;
		}

		void SetRadianceAttack03(RP03_OBj* _sc)
		{
			m_radianceScirpt = _sc;
		}

		void SetRadianceAttack01(RP01_Obj* _sc)
		{
			m_rp01 = _sc;
		}

		void SetRadianceAttack02(RP02_Obj* _sc)
		{
			m_rp02 = _sc;
		}


		void SetRadianceAttack04_01(RP04_Obj01* _sc)
		{
			m_rp04_01 = _sc;
		}

		void SetRadianceAttack04_02(RP04_Obj02* _sc)
		{
			m_rp04_02 = _sc;
		}

		void SetRadianceAttack04_03(RP04_Obj03* _sc)
		{
			m_rp04_03 = _sc;
		}



	public:

		RP03_OBj* GetRadianceAttack03()
		{
			return m_radianceScirpt;
		}

		RP01_Obj* GetRadianceAttack01()
		{
			return m_rp01;
		}

		RP02_Obj* GetRadianceAttack02()
		{
			return m_rp02;
		}


		RP04_Obj01* GetRadianceAttack04_01()
		{
			return m_rp04_01;
		}


		RP04_Obj02* GetRadianceAttack04_02()
		{
			return m_rp04_02;
		}

		RP04_Obj03* GetRadianceAttack04_03()
		{
			return m_rp04_03;
		}


		BossStartTigger* GetBossTrigger()
		{
			return m_BossTrigger;
		}

		GameObject* GetBossBG()
		{
			return  m_gBossBG;
		}

		std::vector<GameObject*> GetLightObj()
		{
			return m_vLightObj;
		}

		void DamageMonster()
		{
			bDamage = true;
		}

		bool GetBoolDamageMonster()
		{
			return bDamage;
		}

		std::vector<std::shared_ptr<AudioClip>> GetMonsterAC()
		{
			return m_AudioClips;
		}

		void SetSceneCamera(GameObject* _camera)
		{
			m_SceneCameraobj = _camera;
		}

		GameObject* GetSceneCamera()
		{
			return m_SceneCameraobj;
		}
		
		GameObject* GetGrimmWall()
		{
			return m_GrimmWallObj;
		}


	protected:
	
		BossStartTigger* m_BossTrigger;
	
		renderer::MonsterCB MonsterCB;

		AudioSource* m_AudioSC;

		std::vector<std::shared_ptr<AudioClip>> m_AudioClips;

		RP03_OBj*  m_radianceScirpt;
		RP01_Obj*  m_rp01;
		RP02_Obj* m_rp02;
		RP04_Obj01* m_rp04_01;
		RP04_Obj02* m_rp04_02;
		RP04_Obj03* m_rp04_03;


	private:
		
		eMonsterState    m_eMonsterState;

		MonsterInfo		 m_MonsterInfo;

	
		AI* m_pAI;

		Scene* m_pCurScene;

		int		mDir;
		int	  m_iMonsterDirX;
		int   m_iMonsterDirY;
	

		
		std::vector<GameObject*> m_vLightObj;

		bool bDamage;
		float m_fDamageTime;

		GameObject* m_gBossBG;
		GameObject* m_GrimmWallObj;
		GameObject* m_SceneCameraobj;
	};

}