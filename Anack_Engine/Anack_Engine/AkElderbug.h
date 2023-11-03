#pragma once
#include "AkGameObject.h"
#include "AkAudioClip.h"

namespace Ak
{
	class Elderbug :
		public GameObject
	{

	public:
		Elderbug();
		virtual ~Elderbug();


	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	public:
		std::vector<std::shared_ptr<AudioClip>> GetAC()
		{
			return m_vAC;
		}

	private:
		std::vector<std::shared_ptr<AudioClip>> m_vAC;

	};



}