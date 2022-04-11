#include "Player.h"
#include "Input.h"

Player::Player() :
	position(0.0f, 0.0f, 0.0f),
	forwardVec(1.0f, 0.0f, 0.0f),
	playerRot(-90, 0, 0),
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

	object->position = position;
	object->rotation = playerRot;
}

void Player::Draw()
{
	DrawObject3d(object);
}
