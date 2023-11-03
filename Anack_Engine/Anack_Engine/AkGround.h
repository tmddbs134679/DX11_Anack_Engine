#pragma once
#include "AkGameObject.h"


namespace Ak
{

	class Ground :
		public GameObject
	{
	public:
		Ground();
		virtual ~Ground();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;





	private:

	};


}
