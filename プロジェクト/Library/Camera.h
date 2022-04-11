#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera final
{
private:
	//ビュー変換情報
	XMFLOAT3 _eye;		//視点
	XMFLOAT3 _target;	//注視点
	XMFLOAT3 _up;		//上ベクトル

	//ビュー行列
	XMMATRIX _matView;
	//射影変換行列
	XMMATRIX _matProjection;
	//ビュープロジェクション
	XMMATRIX _matViewProj;
	//ビルボード行列
	XMMATRIX _matBillBoard;
	//カメラローカル
	XMMATRIX camRocal;
	//カメラワールド
	XMMATRIX _camWorld;

	//コンストラクタ
	Camera(XMFLOAT3 eye_, XMFLOAT3 target_, XMFLOAT3 up_);
	Camera() {
		_eye = XMFLOAT3(0, 45, -45);
		_target = XMFLOAT3(0, 0, 0);
		_up = XMFLOAT3(0, 1, 0);

		SetProjecion();

		UpdateViewMat();
	};
	//デストラクタ
	~Camera() {};

public:
	/// インスタンス取得
	static Camera *Get() {
		static Camera ins;
		return &ins;
	}
	/// <summary>
	/// プロジェクション行列生成
	/// </summary>
	void SetProjecion();

	/// <summary>
	/// ビュー行列設定
	/// </summary>
	/// <param name="eye">視点座標</param>
	/// <param name="target">注視点座標</param>
	/// <param name="up">上方向ベクトル</param>
	void SetViewStatusEyeTargetUp(XMFLOAT3 &eye, XMFLOAT3 &target, XMFLOAT3 &up);

	/// <summary>
	/// ビュー行列設定
	/// </summary>
	/// <param name="eye">視点座標</param>
	void SetViewStatusEye(XMFLOAT3 &eye);

	/// <summary>
	/// ビュー行列設定
	/// </summary>
	/// <param name="target">注視点座標</param>
	void SetViewStatusTarget(XMFLOAT3 &target);

	/// <summary>
	/// ビュー行列設定
	/// </summary>
	/// <param name="up">上方向ベクトル設定</param>
	void SetViewStatusUp(XMFLOAT3 &up);

	/// <summary>
	/// ビュー行列取得
	/// </summary>
	/// <returns>ビュー行列返却</returns>
	XMMATRIX GetMatrixView();

	/// <summary>
	/// 射影変換行列取得
	/// </summary>
	/// <returns>射影変換（プロジェクション）行列</returns>
	XMMATRIX GetMatrixProjection();

	/// <summary>
	/// ビルボード行列取得
	/// </summary>
	/// <returns>全方向ビルボード行列返却</returns>
	XMMATRIX GetMatrixBillBoardAll();

	/// <summary>
	/// ビュープロジェクション行列取得
	/// </summary>
	/// <returns>ビューと射影を合成した行列</returns>
	XMMATRIX GetMatrixViewProjection();

	/// <summary>
	/// ビュー行列更新
	/// </summary>
	void UpdateViewMat();
};

#define camera (Camera::Get())
