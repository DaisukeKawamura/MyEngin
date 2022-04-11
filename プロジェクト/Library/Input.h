#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
#include "Vector.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#pragma region InputKeyCode
// マウス入力
#define MOUSE_L			0x00		//マウス左
#define MOUSE_R			0x01		//マウス右
#define MOUSE_CENTER	0x02		//マウス中央

#pragma endregion InputKeyCode

using namespace Microsoft::WRL;

class Input final
{
private:
	//入力デバイス
	static IDirectInput8       *dinput      ;
	//キーボード
	static IDirectInputDevice8 *devkeyBoard ;
	//マウス
	static IDirectInputDevice8 *devMouse;

	//キーボード
	static BYTE keys[256];
	static BYTE oldkeys[256];
	//マウス
	static DIMOUSESTATE mouseState;		//マウス入力情報
	static DIMOUSESTATE oldMouseState;	//1F前のマウス入力情報
	static POINT		pos;			//マウス座標

	//コンストラクタ、デストラクタを隠蔽
	Input() {}
	~Input() {}

public:

	/// <summary>
	/// 入力系初期化
	/// </summary>
	/// <param name="w">ウィンドウクラス</param>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <returns>成否</returns>
	bool Init(WNDCLASSEX w, HWND hwnd);

	//入力情報の取得開始
	static void StartGetInputState();

	//キーが入力されているか？
	static bool isKey(int key);
	//トリガー判定
	static bool isKeyTrigger(int key);
	//リリース判定
	static bool isKeyReleased(int key);

	static bool isMouseClicking(int keyCode);

	static bool isMouseClickTrigger(int keyCode);

	static bool isMouseClicked(int keyCode);

	static XMFLOAT2 getMousePos();

	static XMFLOAT2 getMouseVelocity();

	//インスタンス取得
	static Input *Get();

	//コピーコンストラクタ、代入演算子無効化
	Input(const Input &obj) = delete;
	Input &operator=(const Input &obj) = delete;
};

namespace mouse {
}

namespace pad {
}
