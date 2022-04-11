#include "FPS.h"

void FPS::Start()
{
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) {
		return; 
	}
	QueryPerformanceCounter(&timeStart);
}

void FPS::run()
{
	QueryPerformanceCounter(&timeEnd);

	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME) { 
		// ƒ~ƒŠ•b‚É•ÏŠ·
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);
		return;
	}

	if (frameTime > 0.0) {
		fps = (fps * 0.99f) + (0.01f / frameTime);
	}
	timeStart = timeEnd;
}

FPS *FPS::Get()
{
	static FPS ins;
	return &ins;
}
