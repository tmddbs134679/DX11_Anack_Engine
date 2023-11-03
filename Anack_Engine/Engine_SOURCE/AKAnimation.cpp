#include "AkAnimation.h"
#include "AkTime.h"
#include "AkAnimator.h"
#include "AkRenderer.h"

namespace Ak
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.f)
		, mbComplete(false)
		, m_fmulsize(1.f)
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::Update()
	{
  
	}

	void Animation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += (float)Time::DeltaTime();

		//스프라이트 시간 종료
		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.f;
		}
		//스프라이트 마지막 도달 시
		if (mSprites.size() <= mIndex)
		{
			mIndex = mSprites.size() - 1;
			mbComplete = true;
			
		}
	}

	void Animation::Render()
	{

	}

	void Animation::Create(std::wstring _name, std::shared_ptr<graphics::Texture> _atlas, Vector2 _leftTop, 
						   Vector2 _size, UINT _columnLength, Vector2 _offset, float _duration)
	{
		SetKey(_name);
		mAtlas = _atlas;

		float width = (float)_atlas->GetWidth();
		float height = (float)_atlas->GetHeight();

		for (size_t i = 0; i < _columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = _leftTop.x + (i * _size.x) / width;
			sprite.leftTop.y = _leftTop.y / height;
			sprite.size.x = _size.x / width;
			sprite.size.y = _size.y / height;
			sprite.offset = _offset;
			sprite.atlasSize = Vector2(m_fmulsize * (200.0f / width), m_fmulsize * (200.0f / height) );
			sprite.duration = _duration;
			
			mSprites.push_back(sprite);
		}

	}

	void Animation::Binds()
	{
		//Texure Bind
		

		mAtlas->BindShader(graphics::eShaderStage::PS, 12);
		//test
		//mAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		//AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.sprtieSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

	}

	void Animation::Reset()
	{
		mTime = 0.f;
		mbComplete = false;
		mIndex = 0;

	}

}
