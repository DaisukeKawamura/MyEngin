#include "random.h"

std::random_device Random::rnd;

int Random::intrand_nl()
{
    return rnd();
}

int Random::intrand_sl(int max, int min)
{
    //�����Z���k�E�c�C�X�^����������
    std::mt19937 mt(rnd());
    //�����w��͈͂̈�l����
    std::uniform_int_distribution<> rand(min, max);

    return rand(mt);
}

double Random::doublerand_sl(double max, double min)
{
    //�����Z���k�E�c�C�X�^����������
    std::mt19937 mt(rnd());
    //�����w��͈͂̈�l����
    std::uniform_real_distribution<> rand(min, max);

    return rand(mt);
}

float Random::floatrand_sl(float max, float min)
{
    //�����Z���k�E�c�C�X�^����������
    std::mt19937 mt(rnd());
    //�����w��͈͂̈�l����
    std::uniform_real_distribution<> rand(min, max);

    return static_cast<float>(rand(mt));
}
