#pragma once
#include "Task.h"
#include "SceneChanger.h"

class SceneBase : public Task{
public:
    SceneBase(SceneChanger *changer);
    SceneBase() {}
    virtual ~SceneBase() {
    }

    virtual void Initialize() override {}    //�����������I�[�o�[���C�h
    virtual void Finalize() override {}      //�I�������I�[�o�[���C�h
    virtual void Update() override {}        //�X�V�����I�[�o�[���C�h
    virtual void Draw() override {}          //�`�揈���I�[�o�[���C�h
};