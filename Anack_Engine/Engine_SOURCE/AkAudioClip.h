#pragma once
#include "AkResource.h"
#include "AkFmod.h"

namespace Ak
{
	using namespace Ak::math;

	class AudioClip :
		public Resource
	{

	public:
		AudioClip();
		AudioClip(const std::wstring& _name);
		~AudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);

		void SetLoop(bool loop)
		{ 
			mbLoop = loop; 
		}


		bool GetLoop()
		{
			return mbLoop;
		}

		void SetSoundDistance(Vector2 _vec)
		{
			mMinDistance = _vec.x;
			mMaxDistance = _vec.y;
		}


	
	private:

		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;


		std::wstring m_name;
	};



}