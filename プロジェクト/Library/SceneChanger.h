#pragma once

class SceneChanger
{
	virtual ~SceneChanger() = 0;
	virtual void ChangeScene(int nextScene) = 0;
};

