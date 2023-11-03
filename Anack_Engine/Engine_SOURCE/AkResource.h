#pragma once
#include "AkEntity.h"

namespace Ak
{
	class Resource
	{
	public:
		Resource(const enums::eResourceType _type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;


		void SetKey(const std::wstring& _key)
		{
			mKey = _key;
		}

		void SetPath(const std::wstring& _path)
		{
			mPath = _path;
		}


		const std::wstring& GetKey() 
		{ 
			return mKey;
		}

		const std::wstring& GetPath() 
		{ 
			return mPath; 
		}

		const enums::eResourceType GetType()
		{
			return mType;
		}
	



	private:
		const enums::eResourceType mType;
		std::wstring mKey;
		std::wstring mPath;
	};
}
