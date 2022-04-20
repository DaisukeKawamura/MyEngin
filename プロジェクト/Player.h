#pragma once
#include "Vector.h"
#include "Object3DMgr.h"

class Player
{
public:
	Player();
	~Player();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	Vector3 position;   //プレイヤーの座標
	Vector3 forwardVec; //進行方向
	Vector3 playerRot;	 //プレイヤーの回転角
	Object3d *object; //プレイヤーのオブジェクト

	int flag = 0;
	Vector3 vx;
	Vector3 ax;
	Vector3 gx;
	Vector3 ss;
private:
	Model3D model; //プレイヤーのモデル
};