#pragma once
#include "ISceneManager.h"

class SceneManager final
{
private:
	static ISceneManager *mgr;

	SceneManager(){}
	~SceneManager() {
		delete mgr;
	}
};

