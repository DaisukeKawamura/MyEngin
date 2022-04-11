#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/// <summary>
/// FPS�Ǘ��p�N���X
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

	//�R���X�g���N�^�A�f�X�g���N�^
	FPS() {};
	~FPS() {};

public:
	//������s
	void Start();
	//FPS�����̎��s
	void run();
	//�C���X�^���X�擾
	static FPS *Get();
	//�R�s�[�R���X�g���N�^�A������Z�q������
	FPS(const FPS &obj) = delete;
	FPS &operator=(const FPS &obj) = delete;
};

