#pragma once
#include "AkComponent.h"
#include "AkGraphics.h"

namespace Ak 
{
	using namespace graphics;
	class Light :
		public Component
	{

	public:
		Light();
		~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	public:

		void SetType(eLightType _type)
		{
			mAttribute.type = _type;
		}

		void SetRadius(float _radius)
		{
			mAttribute.radius = _radius;
		}

		void SetColor(Vector4 _color)
		{
			mAttribute.color = _color;
		}

		void SetAngle(float _angle)
		{
			mAttribute.angle = _angle;
		}

	
	public:
		LightAttribute GetAttribute()
		{
			return mAttribute;
		}

		Vector4 GetColor()
		{
			return mAttribute.color;
		}

		float GetRadius()
		{
			return mAttribute.radius;
		}

		float GetAngle()
		{
			return mAttribute.angle;
		}

		eLightType GetType()
		{
			return mAttribute.type;
		}

	private:
		LightAttribute mAttribute;
	

		
	};



}