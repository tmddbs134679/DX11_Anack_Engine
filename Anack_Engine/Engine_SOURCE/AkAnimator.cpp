#include "AkAnimator.h"


namespace Ak
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
		, m_fmul(1)
	{

	}

	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void Animator::Initialize()
	{

	}

	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		if (mActiveAnimation->isComplete() && mbLoop)
		{
			Events* events = FindEvents(mActiveAnimation->GetKey());

 			if (events)
				events->completeEvent();

			mActiveAnimation->Reset();

		}

		mActiveAnimation->LateUpdate();

	}

	void Animator::LateUpdate()
	{

	}

	void Animator::Render()
	{

	}

	void Animator::Create(const std::wstring& _name, std::shared_ptr<graphics::Texture> _atlas, Vector2 _leftTop, Vector2 _size,
						   UINT _columnLength, Vector2 _offset, float _duration)
	{
		Animation* animation = FindAnimation(_name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetKey(_name);

		animation->SetMulSize(m_fmul);

		animation->Create(_name
						, _atlas
						, _leftTop
						, _size
						, _columnLength
						, _offset
						, _duration);

		mAnimations.insert(std::make_pair(_name, animation));


		Events* events = FindEvents(_name);
		if (events != nullptr)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(_name, events));
	}

	Animation* Animator::FindAnimation(const std::wstring& _name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(_name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& _name)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(_name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& _name, bool _loop)
	{
		Animation* prevAnimation = mActiveAnimation;

		m_sPlayName = _name;

		Events* events;
		if (nullptr != prevAnimation)
		{

			events = FindEvents(prevAnimation->GetKey());
			if (events)
				events->endEvent();
		}

		Animation* animation = FindAnimation(_name);

		if (animation)
		{
			mActiveAnimation = animation;
		}

		events = FindEvents(mActiveAnimation->GetKey());
		if (events)
			events->startEvent();

		mbLoop = _loop;
		mActiveAnimation->Reset();

	}

	void Animator::Binds()
	{
		if (nullptr == mActiveAnimation)
			return;

		mActiveAnimation->Binds();


	}

	std::function<void()>& Animator::StartEvent(const std::wstring _key)
	{
		Events* events = FindEvents(_key);

		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::CompleteEvent(const std::wstring _key)
	{
		Events* events = FindEvents(_key);

		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::EndEvent(const std::wstring _key)
	{
		Events* events = FindEvents(_key);
	
		return events->endEvent.mEvent;
	}

}