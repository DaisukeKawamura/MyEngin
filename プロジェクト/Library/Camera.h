#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera final
{
private:
	//�r���[�ϊ����
	XMFLOAT3 _eye;		//���_
	XMFLOAT3 _target;	//�����_
	XMFLOAT3 _up;		//��x�N�g��

	//�r���[�s��
	XMMATRIX _matView;
	//�ˉe�ϊ��s��
	XMMATRIX _matProjection;
	//�r���[�v���W�F�N�V����
	XMMATRIX _matViewProj;
	//�r���{�[�h�s��
	XMMATRIX _matBillBoard;
	//�J�������[�J��
	XMMATRIX camRocal;
	//�J�������[���h
	XMMATRIX _camWorld;

	//�R���X�g���N�^
	Camera(XMFLOAT3 eye_, XMFLOAT3 target_, XMFLOAT3 up_);
	Camera() {
		_eye = XMFLOAT3(0, 45, -45);
		_target = XMFLOAT3(0, 0, 0);
		_up = XMFLOAT3(0, 1, 0);

		SetProjecion();

		UpdateViewMat();
	};
	//�f�X�g���N�^
	~Camera() {};

public:
	/// �C���X�^���X�擾
	static Camera *Get() {
		static Camera ins;
		return &ins;
	}
	/// <summary>
	/// �v���W�F�N�V�����s�񐶐�
	/// </summary>
	void SetProjecion();

	/// <summary>
	/// �r���[�s��ݒ�
	/// </summary>
	/// <param name="eye">���_���W</param>
	/// <param name="target">�����_���W</param>
	/// <param name="up">������x�N�g��</param>
	void SetViewStatusEyeTargetUp(XMFLOAT3 &eye, XMFLOAT3 &target, XMFLOAT3 &up);

	/// <summary>
	/// �r���[�s��ݒ�
	/// </summary>
	/// <param name="eye">���_���W</param>
	void SetViewStatusEye(XMFLOAT3 &eye);

	/// <summary>
	/// �r���[�s��ݒ�
	/// </summary>
	/// <param name="target">�����_���W</param>
	void SetViewStatusTarget(XMFLOAT3 &target);

	/// <summary>
	/// �r���[�s��ݒ�
	/// </summary>
	/// <param name="up">������x�N�g���ݒ�</param>
	void SetViewStatusUp(XMFLOAT3 &up);

	/// <summary>
	/// �r���[�s��擾
	/// </summary>
	/// <returns>�r���[�s��ԋp</returns>
	XMMATRIX GetMatrixView();

	/// <summary>
	/// �ˉe�ϊ��s��擾
	/// </summary>
	/// <returns>�ˉe�ϊ��i�v���W�F�N�V�����j�s��</returns>
	XMMATRIX GetMatrixProjection();

	/// <summary>
	/// �r���{�[�h�s��擾
	/// </summary>
	/// <returns>�S�����r���{�[�h�s��ԋp</returns>
	XMMATRIX GetMatrixBillBoardAll();

	/// <summary>
	/// �r���[�v���W�F�N�V�����s��擾
	/// </summary>
	/// <returns>�r���[�Ǝˉe�����������s��</returns>
	XMMATRIX GetMatrixViewProjection();

	/// <summary>
	/// �r���[�s��X�V
	/// </summary>
	void UpdateViewMat();
};

#define camera (Camera::Get())
