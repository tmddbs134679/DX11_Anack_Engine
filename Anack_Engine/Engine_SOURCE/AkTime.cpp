#include "AkTime.h"
#include "AkApplication.h"
#include "AkFontWrapper.h"

extern Ak::Application application;

namespace Ak
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	double Time::m_fSlowTime = 1.f;

	void Time::Initiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);

	
	}

	void Time::Update()
	{

	

		QueryPerformanceCounter(&mCurFrequency);

		
		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		// 초 단위 변경
		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart * m_fSlowTime;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;
		wchar_t szFloat[50] = L"가나다";

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			//wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}

		FontWrapper::DrawFont(szFloat, 300.f, 300.f, 200, FONT_RGBA(225, 225, 225, 225));
	}
}