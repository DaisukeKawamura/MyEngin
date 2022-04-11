#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/// <summary>
/// FPS管理用クラス
/// </summary>
class FPS final
{
private:
	const float MIN_FREAM_TIME = 1.0 / 60.0;
	float frameTime = 0;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	float fps = 0;

	//コンストラクタ、デストラクタ
	FPS() {};
	~FPS() {};

public:
	//初回実行
	void Start();
	//FPS処理の実行
	void run();
	//インスタンス取得
	static FPS *Get();
	//コピーコンストラクタ、代入演算子無効化
	FPS(const FPS &obj) = delete;
	FPS &operator=(const FPS &obj) = delete;
};

