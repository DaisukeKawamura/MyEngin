#include "Input.h"
#include "WinAPI.h"

BYTE Input::keys[256]    = {};
BYTE Input::oldkeys[256] = {};
DIMOUSESTATE Input::mouseState;
DIMOUSESTATE Input::oldMouseState;
POINT        Input::pos;

IDirectInput8       *Input::dinput      = nullptr;
IDirectInputDevice8 *Input::devkeyBoard = nullptr;
IDirectInputDevice8 *Input::devMouse	= nullptr;

bool Input::Init(WNDCLASSEX w, HWND hwnd)
{
	HRESULT result;
	//初期化
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);
	if (result != S_OK) { return false; }

	//キーボードデバイス生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyBoard, NULL);
	if (result != S_OK) { return false; }
	//マウスデバイス生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (result != S_OK) { return false; }

	//入力データ形式セット
	result = devkeyBoard->SetDataFormat(&c_dfDIKeyboard);//標準
	if (result != S_OK) { return false; }
	result = devMouse->SetDataFormat(&c_dfDIMouse);
	if (result != S_OK) { return false; }

	//排他制御レベルセット
	result = devkeyBoard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (result != S_OK) { return false; }
	result = devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (result != S_OK) { return false; }

	return true;
}

void Input::StartGetInputState()
{
	//前フレームの入力情報を取得
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//キー入力状態取得開始
	devkeyBoard->Acquire();
	//全キーの入力状態を取得
	devkeyBoard->GetDeviceState(sizeof(keys), keys);

	//マウスの前フレームの入力状態を取得
	oldMouseState = mouseState;
	//マウス入力状態取得開始
	devMouse->Acquire();
	//マウスの入力状態を取得
	devMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
}

bool Input::isKey(int key)
{
	return keys[key];
}

bool Input::isKeyTrigger(int key)
{
	return keys[key] && !oldkeys[key];
}

bool Input::isKeyReleased(int key)
{
	return oldkeys[key] && !keys[key];
}

bool Input::isMouseClicking(int keyCode)
{
	//マウスが押されている
	return mouseState.rgbButtons[keyCode] & (0x80);
}

bool Input::isMouseClickTrigger(int keyCode)
{
	BYTE onValue = 0x80;
	//前フレームは押されておらず、現フレームで押されている
	return (mouseState.rgbButtons[keyCode] == onValue) & (oldMouseState.rgbButtons[keyCode] != onValue);
}

bool Input::isMouseClicked(int keyCode)
{
	BYTE onValue = 0x80;
	//前フレームで押されており、現フレームで押されていない
	return (mouseState.rgbButtons[keyCode] != onValue) & (oldMouseState.rgbButtons[keyCode] == onValue);
}

XMFLOAT2 Input::getMousePos()
{
	//デスクトップ座標を取得
	GetCursorPos(&pos);
	//クライアント領域座標変換
	ScreenToClient(WinAPI::GetHWND(), &pos);
	//戻り値に格納
	XMFLOAT2 result(pos.x, pos.y);
	//返却
	return result;
}

XMFLOAT2 Input::getMouseVelocity()
{
	XMFLOAT2 result;
	result.x = mouseState.lX;
	result.y = mouseState.lY;

	return result;
}

Input *Input::Get()
{
	static Input instance;
	return &instance;
}
