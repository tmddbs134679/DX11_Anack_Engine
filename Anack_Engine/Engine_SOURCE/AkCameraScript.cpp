#include "AkCameraScript.h"
#include "AkTransform.h"
#include "AkGameObject.h"
#include "AkTime.h"
#include "AkInput.h"
#include "../Anack_Engine/AkPlayer.h"
#include "AkScene.h"
#include "AkSceneManager.h"

namespace Ak
{
	

	void CameraScript::Update()
	{

	
		if (m_pPlayer != nullptr)
		{

			Transform* Cameratr = GetOwner()->GetComponent<Transform>();
			Vector3 CameraPos = Cameratr->GetPosition();

			Vector3	 PlayerPos = m_pPlayer->GetComponent<Transform>()->GetPosition();

			Cameratr->SetPosition(PlayerPos.x, PlayerPos.y + 4.5f , CameraPos.z);
	
			if (m_BackGround != nullptr)
			{
				if (m_BackGround->GetName() == L"Battle_bg")
				{
					Transform* BackGroundTr = m_BackGround->GetComponent<Transform>();
					m_BackGround->GetComponent<Transform>()->SetPosition(0, 0.f, 1.5f);
					BackGroundTr->SetPosition(CameraPos.x, CameraPos.y, PlayerPos.z);
				}
				else if(m_BackGround->GetName() == L"StartBG")
				{
					Transform* BackGroundTr = m_BackGround->GetComponent<Transform>();

					BackGroundTr->SetPosition(PlayerPos.x, PlayerPos.y + 10.f, PlayerPos.z);
					
				}
				else if (m_BackGround->GetName() == L"shadow")
				{
					Transform* BackGroundTr = m_BackGround->GetComponent<Transform>();

					BackGroundTr->SetPosition(PlayerPos.x, PlayerPos.y, 0.f);
				}
		
			}
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();


			if (Input::GetKey(eKeyCode::W))
			{
				pos.z += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				pos.z -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			/*else if (Input::GetKey(eKeyCode::A))
			{
				pos.x -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::D))
			{
				pos.x += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}*/
			else if (Input::GetKey(eKeyCode::Q))
			{
				pos.y -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::E))
			{
				pos.y += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		else
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();


			if (Input::GetKey(eKeyCode::W))
			{
				pos.z += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				pos.z -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::A))
			{
				pos.x -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::D))
			{
				pos.x += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::Q))
			{
				pos.y -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (Input::GetKey(eKeyCode::E))
			{
				pos.y += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}

		}


	
		if (m_bBossDeadCamera)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			Vector3 PrePos = pos;

			static float m_fShakeDuration = 7.f;
			static float m_fShakeMagnitude = 0.3f;

			if (m_fShakeTime >= 0.0f)
			{
				m_fShakeTime += Time::DeltaTime();

				if (m_fShakeTime <= m_fShakeDuration)
				{
					float ShakeAmount = (m_fShakeTime / m_fShakeDuration) * m_fShakeMagnitude;
					float ShakeOffSet = ((rand() % 2000 - 1000) / 1000.0f) * ShakeAmount;
					tr->SetPositionXY(Vector2(pos.x + ShakeOffSet, pos.y + ShakeOffSet));
				}
				else
				{

					m_fShakeTime = 0.f;
					tr->SetPositionXY(Vector2(PrePos));
					m_bBossDeadCamera = false;

				}
			}
		}
	

		if (m_bShakeCamera)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			Vector3 PrePos = pos;

			static float m_fShakeDuration = 1.f;
			static float m_fShakeMagnitude = 0.1f;

			if (m_fShakeTime >= 0.0f)
			{
				m_fShakeTime += Time::DeltaTime();

				if (m_fShakeTime <= m_fShakeDuration)
				{
					float ShakeAmount = (m_fShakeTime / m_fShakeDuration) * m_fShakeMagnitude;
					float ShakeOffSet = ((rand() % 2000 - 1000) / 1000.0f) * ShakeAmount;
					tr->SetPositionXY(Vector2(pos.x + ShakeOffSet, pos.y));
				}
				else
				{
					
					m_fShakeTime = 0.f;
					tr->SetPositionXY(Vector2(PrePos));
					m_bShakeCamera = false;

				}
			}
		}

		//Item Open½Ã Anim ½ÇÇà
		if (m_bBattleAnim)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 BoxPos = m_pPlayer->GetBattleBox()->GetComponent<Transform>()->GetPosition();
			Vector3 PlayerPos = m_pPlayer->GetComponent<Transform>()->GetPosition();
			static Vector3 PrePos = PlayerPos;
			
			float m_cameraMoveDuration = 5.f;

			if (m_fBattleAnimTime >= 0.0f)
			{
				m_fBattleAnimTime += Time::DeltaTime();

				if (m_fBattleAnimTime <= m_cameraMoveDuration)
				{
					float f = m_fBattleAnimTime / m_cameraMoveDuration;
					Vector3 newPos = Vector3::Lerp(PlayerPos, BoxPos, f);
					tr->SetPositionXY(Vector2(newPos.x, newPos.y));
				}
				else if(m_fBattleAnimTime <= m_cameraMoveDuration + 1 && m_fBattleAnimTime > m_cameraMoveDuration)
				{
					tr->SetPositionXY(Vector2(BoxPos.x, BoxPos.y));
				}
				else
				{
					tr->SetPositionXY(Vector2(PrePos.x, PrePos.y + 4.5f));
					m_bBattleAnim = false;
				}
				
				
			}
	
		}
	}



}