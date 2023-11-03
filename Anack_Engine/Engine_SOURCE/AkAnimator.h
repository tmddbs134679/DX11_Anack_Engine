#pragma once
#include "AkComponent.h"
#include "AkAnimation.h"

namespace Ak
{
	class Animator :
		public Component
	{
	public:

		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

	public:

		Animator();
		~Animator();

	public:

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


		void Create(const std::wstring& _name
			, std::shared_ptr<graphics::Texture> _atlas
			, Vector2 _leftTop
			, Vector2 _size
			, UINT _columnLength
			, Vector2 _offset = Vector2::Zero
			, float _duration = 0.1f);
		
		Animation* FindAnimation(const std::wstring& _name);
		Events* FindEvents(const std::wstring& _name);
		void PlayAnimation(const std::wstring& _name, bool _loop);
		void Binds();

		std::function<void()>& StartEvent(const std::wstring _key);
		std::function<void()>& CompleteEvent(const std::wstring _key);
		std::function<void()>& EndEvent(const std::wstring _key);

		const std::wstring  GetPlayAnimationName()
		{
			return m_sPlayName;
		}

		Animation* GetAnimation()
		{
			return mActiveAnimation;
		}




		void SetMulSize(int _f)
		{
			m_fmul = _f;
		}


	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*>	   mEvents;

		 std::wstring m_sPlayName;

		Animation* mActiveAnimation;

		bool mbLoop;

		int m_fmul;

		

	};


}
