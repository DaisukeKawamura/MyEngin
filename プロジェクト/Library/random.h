#pragma once
#include <random>

class Random
{
public:
	//非決定的乱数
	static std::random_device rnd;
	//乱数生成に必要なほかの要素は関数実行時に生成
private:
	//コンストラクタ、デストラクタはprivate
	Random() {};
	~Random() {};
public:
	Random(const Random &obj) = delete;		//コピーコンストラクタの無効化
	Random &operator=(const Random &obj) = delete;		//代入演算子の無効化

	/// <summary>
	/// 範囲未指定の整数型乱数生成（非決定的）
	/// </summary>
	/// <returns> 生成されたint型乱数（32bit ,0~0xffffffff）</returns>
	static int intrand_nl();

	/// <summary>
	/// 範囲指定の整数型乱数生成（決定的）
	/// </summary>
	/// <param name="max"> 生成する乱数の最大値 </param>
	/// <param name="min"> 生成する乱数の最小値 </param>
	/// <returns> 生成されたint型乱数（32bit, min~maxの範囲） </returns>
	static int intrand_sl(int max, int min);

	/// <summary>
	/// 範囲指定のdouble型乱数生成
	/// </summary>
	/// <param name="max"> 生成する乱数の最大値</param>
	/// <param name="min"> 生成する乱数の最小値</param>
	/// <returns> 生成されたdouble型乱数</returns>
	static double doublerand_sl(double max, double min);

	/// <summary>
	/// 範囲指定のfloat型乱数生成
	/// </summary>
	/// <param name="max"> 生成する乱数の最大値</param>
	/// <param name="min"> 生成する乱数の最小値</param>
	/// <returns> 生成されたfloat型乱数（実際はdoubleだが、キャストでfloatにしてる）</returns>
	static float floatrand_sl(float max, float min);
};

