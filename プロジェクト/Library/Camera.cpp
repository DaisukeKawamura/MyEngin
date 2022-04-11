#include "Camera.h"
#include "WinAPI.h"

Camera::Camera(XMFLOAT3 eye_, XMFLOAT3 target_, XMFLOAT3 up_)
{
	_eye = eye_;
	_target = target_;
	_up = up_;

	//�r���[�s��i�[
	_matView = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));

	//�v���W�F�N�V�����s�񐶐�
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinAPI::window_width / (float)WinAPI::window_height,
		0.1f, 1000.0f
	);

	//���[�J�����W����
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
	//�v���W�F�N�V�����s�񐶐�
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
	//�X�V
	UpdateViewMat();
}

void Camera::SetViewStatusEye(XMFLOAT3 &eye)
{
	_eye = eye;
	//�X�V
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

	//�v���W�F�N�V�����s�񐶐�
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinAPI::window_width / (float)WinAPI::window_height,
		0.1f, 1000.0f
	);
	//�r���[�v���W�F�N�V�����s��
	_matViewProj = _matView * _matProjection;

	//XMVECTOR
	XMVECTOR eyeVec = XMLoadFloat3(&_eye);
	XMVECTOR targetVec = XMLoadFloat3(&_target);
	XMVECTOR upVec = XMLoadFloat3(&_up);

	//Z��
	XMVECTOR axisZ = XMVectorSubtract(targetVec, eyeVec);
	axisZ = XMVector3Normalize(axisZ);
	//x��
	XMVECTOR axisX = XMVector3Cross(upVec, axisZ);
	axisX = XMVector3Normalize(axisX);
	//y��
	XMVECTOR axisY = XMVector3Cross(axisZ, axisX);

	//��]�s��
	XMMATRIX camrot;
	camrot.r[0] = axisX;
	camrot.r[1] = axisY;
	camrot.r[2] = axisZ;
	camrot.r[3] = XMVectorSet(0, 0, 0, 1);

	//�S�����r���{�[�h�v�Z
	_matBillBoard = camrot;
}
