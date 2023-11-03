#pragma once
#include "AkResource.h"
#include "AkShader.h"
#include "AkTexture.h"

namespace Ak::graphics
{
	class Material :
		public Resource
	{
	public:

		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		void Clear();



		void SetShader(std::shared_ptr<Shader> _shader)
		{
			mShader = _shader;
		}

		void SetTexture(std::shared_ptr<Texture> _texture)
		{
			mTexture = _texture;
		}

		void SetRenderingMode(eRenderingMode _mode)
		{
			mMode = _mode;
		}

		eRenderingMode GetRenderingMode()
		{
			return mMode;
		}

	private:

		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;

		eRenderingMode mMode;


	};


}