#pragma once
#include "AkResource.h"
#include "AkTexture.h"

namespace Ak
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation :
		public Resource
	{
	public:

		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float	duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.f)
			{

			}

		};
	public:

		Animation();
		~Animation();

	

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring _name
			, std::shared_ptr<graphics::Texture> _atlas
			, Vector2 _leftTop
			, Vector2 _size
			, UINT _columnLength
			, Vector2 _offset = Vector2::Zero
			, float _duration = 0.0f);


		void Binds();
		void Reset();


		void SetMulSize(float _f)
		{
			m_fmulsize = _f;
		}


		virtual HRESULT Load(const std::wstring& _path)
		{
			return S_FALSE;
		};


		bool isComplete()
		{
			return mbComplete;
		}

	private:

		std::shared_ptr<graphics::Texture> mAtlas;

		Animator* mAnimator;
		std::vector<Sprite> mSprites;

		int		mIndex;
		float	mTime;
		bool	mbComplete;

		float   m_fmulsize;

	};


}

