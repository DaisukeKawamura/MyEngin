#include "Player.h"
#include "Input.h"

Player::Player() :
	position(0.0f, 50.0f, 0.0f),
	forwardVec(1.0f, 0.0f, 0.0f),
	playerRot(-90, 0, 0),
	vx(0.0f,0.0f,0.0f),
	ax(0.0f, 0.0f, 0.0f),
	gx(0.0f, 0.0f, 0.0f),
	ss(0.0f, 0.0f, 0.0f),
	model{},
	object(nullptr)
{
	model.LoadObjModel("player");
	object = CreateObject3d(&model);
	object->position = Vector3(0.0f, 0.0f, 0.0f);
	object->scale = { 10.0f, 10.0f, 10.0f };
	object->rotation = Vector3(-90, 0, 0);
	object->color = { 1, 1, 1, 1 };
}

Player::~Player()
{
	if (object != nullptr)
	{
		DeleteObject3d(object);
		object = nullptr;
	}
}

void Player::Update()
{
	if (Input::isKey(DIK_W) || Input::isKey(DIK_UP))
	{
		forwardVec = { 0.0f, 1.0f, 0.0f };
		position += forwardVec * 1.0f;
		playerRot = Vector3(-90, 0, 0);
	}
	if (Input::isKey(DIK_A) || Input::isKey(DIK_LEFT))
	{
		forwardVec = { -1.0f, 0.0f, 0.0f };
		position += forwardVec * 1.0f;
		playerRot = Vector3(-180, 90, 270);
	}
	if (Input::isKey(DIK_S) || Input::isKey(DIK_DOWN))
	{
		forwardVec = { 0.0f, -1.0f, 0.0f };
		position += forwardVec * 1.0f;
		playerRot = Vector3(-270, 90, 270);
	}
	if (Input::isKey(DIK_D) || Input::isKey(DIK_RIGHT))
	{
		forwardVec = { 1.0f, 0.0f, 0.0f };
		position += forwardVec * 1.0f;
		playerRot = Vector3(-180, -90, 90);
	}

	if (Input::isKeyTrigger(DIK_1))
	{
		position.x = 0.0f;
		position.y = 50.0f;
		ax.y = 0.0f;
		ax.x = 0.0f;
		vx.y = 0.0f;
		vx.x = 0.0f;
		flag = 1;
	}
	if (Input::isKeyTrigger(DIK_2))
	{
		position.x = -120.0f;
		position.y = 30.0f;
		ax.y = 0.0f;
		ax.x = 0.0f;
		vx.y = 0.0f;
		vx.x = 0.0f;
		flag = 2;
	}

	if (flag == 1)
	{
		gx.y = 9.8f / 1000.0f;
		ax.y -= gx.y;

		if (Input::isKey(DIK_R))
		{
			position.x = 0.0f;
			position.y = 50.0f;
			ax.y = 0.0f;
			ax.x = 0.0f;
			vx.y = 0.0f;
			vx.x = 0.0f;
			flag = 0;
		}
	}

	if (flag == 2)
	{
		gx.y = 9.8f / 1000.0f;
		ax.y -= gx.y;
		ax.x = 350.0f / 1000.0f;

		if (Input::isKey(DIK_R))
		{
			position.x = -120.0f;
			position.y = 30.0f;
			ax.y = 0.0f;
			ax.x = 0.0f;
			vx.y = 0.0f;
			vx.x = 0.0f;
			flag = 0;
		}
	}

	position = position + vx;
	vx = vx + ax;

	object->position = position;
	object->rotation = playerRot;
}

void Player::Draw()
{
	DrawObject3d(object);
}
