#include "Camera.h"
#include "WinAPI.h"

Camera::Camera(XMFLOAT3 eye_, XMFLOAT3 target_, XMFLOAT3 up_)
{
	_eye = eye_;
	_target = target_;
	_up = up_;

	//ビュー行列格納
	_matView = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));

	//プロジェクション行列生成
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinAPI::window_width / (float)WinAPI::window_height,
		0.1f, 1000.0f
	);

	//ローカル座標生成
	camRocal = XMMatrixIdentity();

	camRocal.r[0].m128_f32[0] = _eye.x;
	camRocal.r[0].m128_f32[1] = _eye.y;
	camRocal.r[0].m128_f32[2] = _eye.z;
	camRocal.r[0].m128_f32[3] = 1;
	camRocal.r[1].m128_f32[0] = _up.x - _eye.x;
	camRocal.r[1].m128_f32[1] = _up.y - _eye.y;
	camRocal.r[1].m128_f32[2] = _up.z - _eye.z;
	camRocal.r[1].m128_f32[3] = 0;
	camRocal.r[2].m128_f32[0] = _target.x;
	camRocal.r[2].m128_f32[1] = _target.y;
	camRocal.r[2].m128_f32[2] = _target.z;
	camRocal.r[2].m128_f32[3] = 1;
	camRocal.r[3].m128_f32[3] = 0;

	UpdateViewMat();
}

void Camera::SetProjecion()
{
	//プロジェクション行列生成
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinAPI::window_width / (float)WinAPI::window_height,
		0.1f, 1000.0f
	);
}

void Camera::SetViewStatusEyeTargetUp(XMFLOAT3 &eye, XMFLOAT3 &target, XMFLOAT3 &up)
{
	_eye	= eye;
	_target = target;
	_up		= up;
	//更新
	UpdateViewMat();
}

void Camera::SetViewStatusEye(XMFLOAT3 &eye)
{
	_eye = eye;
	//更新
	UpdateViewMat();
}

void Camera::SetViewStatusTarget(XMFLOAT3 &target)
{
	_target = target;
	UpdateViewMat();
}

void Camera::SetViewStatusUp(XMFLOAT3 &up) 
{
	_up = up;
	UpdateViewMat();
}

XMMATRIX Camera::GetMatrixView()
{
	return _matView;
}

XMMATRIX Camera::GetMatrixViewProjection()
{
	return _matViewProj;
}

XMMATRIX Camera::GetMatrixBillBoardAll()
{
	return _matBillBoard;
}

XMMATRIX Camera::GetMatrixProjection()
{
	return _matProjection;
}

void Camera::UpdateViewMat() {

	_matView = XMMatrixIdentity();

	_matView = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));

	//プロジェクション行列生成
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinAPI::window_width / (float)WinAPI::window_height,
		0.1f, 1000.0f
	);
	//ビュープロジェクション行列
	_matViewProj = _matView * _matProjection;

	//XMVECTOR
	XMVECTOR eyeVec = XMLoadFloat3(&_eye);
	XMVECTOR targetVec = XMLoadFloat3(&_target);
	XMVECTOR upVec = XMLoadFloat3(&_up);

	//Z軸
	XMVECTOR axisZ = XMVectorSubtract(targetVec, eyeVec);
	axisZ = XMVector3Normalize(axisZ);
	//x軸
	XMVECTOR axisX = XMVector3Cross(upVec, axisZ);
	axisX = XMVector3Normalize(axisX);
	//y軸
	XMVECTOR axisY = XMVector3Cross(axisZ, axisX);

	//回転行列
	XMMATRIX camrot;
	camrot.r[0] = axisX;
	camrot.r[1] = axisY;
	camrot.r[2] = axisZ;
	camrot.r[3] = XMVectorSet(0, 0, 0, 1);

	//全方向ビルボード計算
	_matBillBoard = camrot;
}
