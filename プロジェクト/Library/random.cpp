#include "random.h"

std::random_device Random::rnd;

int Random::intrand_nl()
{
    return rnd();
}

int Random::intrand_sl(int max, int min)
{
    //メルセンヌ・ツイスタ乱数生成器
    std::mt19937 mt(rnd());
    //引数指定範囲の一様乱数
    std::uniform_int_distribution<> rand(min, max);

    return rand(mt);
}

double Random::doublerand_sl(double max, double min)
{
    //メルセンヌ・ツイスタ乱数生成器
    std::mt19937 mt(rnd());
    //引数指定範囲の一様乱数
    std::uniform_real_distribution<> rand(min, max);

    return rand(mt);
}

float Random::floatrand_sl(float max, float min)
{
    //メルセンヌ・ツイスタ乱数生成器
    std::mt19937 mt(rnd());
    //引数指定範囲の一様乱数
    std::uniform_real_distribution<> rand(min, max);

    return static_cast<float>(rand(mt));
}
