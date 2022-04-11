#pragma once
#include "Vector.h"
#include "Object3DMgr.h"

class Player
{
public:
	Player();
	~Player();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	Vector3 position;   //�v���C���[�̍��W
	Vector3 forwardVec; //�i�s����
	Vector3 playerRot;	 //�v���C���[�̉�]�p
	Object3d *object; //�v���C���[�̃I�u�W�F�N�g
private:
	Model3D model; //�v���C���[�̃��f��
};