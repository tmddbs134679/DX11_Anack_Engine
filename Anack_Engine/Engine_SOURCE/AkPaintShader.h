#pragma once
#include "AkComputeShader.h"


namespace Ak::graphics
{
	class PaintShader :
		public ComputeShader
	{
	public:
	

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<class Texture> _target)
		{
			 mTarget = _target;
		}

	private:

		std::shared_ptr<class Texture> mTarget;

	};



}