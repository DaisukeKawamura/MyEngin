#pragma once
#include <iostream>
#include <vector>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXTex.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include "Camera.h"
#include "Object3D.h"
#include "Model.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

typedef struct Pipeline3D
{
	//パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;

}PipelineSet;

extern class Object3d;
extern class Camera;

class Object3DManager
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	//標準パイプラインステート
	Pipeline3D object3dPipelineSet;
	//即時描画用パイプライン
	Pipeline3D quickDrawPipelineSet;

	//グラフィックスパイプラインステート構造体
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipelineStateDesc;

	//シェーダーオブジェクト（標準）
	ComPtr<ID3DBlob> obj_VS;
	ComPtr<ID3DBlob> obj_GS;
	ComPtr<ID3DBlob> obj_PS;

	//シェーダーオブジェクト（即時描画用）
	ComPtr<ID3DBlob> qd_BoxGS;

	vector<Object3d*> objects;

	//デフォルトテクスチャの色
	XMFLOAT4 defColor = { 1.0,0.0,0.0,1.0 };

	//コンストラクタ、デストラクタ
	Object3DManager() {};
	~Object3DManager() {};

public:
	//コピーコンストラクタ無効化
	Object3DManager(const Object3DManager &obj) = delete;
	//代入演算子無効化
	Object3DManager &operator=(const Object3DManager &obj) = delete;

	//インスタンス取得
	static Object3DManager *Get() {
		static Object3DManager obj;
		return &obj;
	}

	//共通射影行列
	XMMATRIX matProjection{};
	//共通ビューポート行列
	XMMATRIX matViewport{};
	//テクスチャ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descheap;
	//テクスチャリソース配列
	ComPtr<ID3D12Resource> texbuff[256];
	//ウィンドウサイズ
	int window_width, window_height;

	/// <summary>
	/// <para>NY_Object3DManagerの生成</para>
	/// </summary>
	/// <param name="dev">ID3D12Deviceのポインタ</param>
	/// <param name="window_width">ウィンドウ横幅</param>
	/// <param name="window_height">ウィンドウ縦幅</param>
	/// <returns>成否</returns>
	bool CreateObject3DManager(ID3D12Device *dev, int window_w, int window_h);

	/// <summary>
	/// 貼り付けるテクスチャの読み込み
	/// </summary>
	/// <param name="texNumber">テクスチャ番号を取得する変数</param>
	/// <param name="filename">ロードするテクスチャのパス（）</param>
	/// <param name="dev"></param>
	void LoadObject3DTexture(UINT &texNumber, string filename, ID3D12Device *dev);

	/// <summary>
	/// object3dの作成、コンテナに格納
	/// </summary>
	Object3d *CreateObject3d(Model3D *modelData);

	/// <summary>
	/// オブジェクトの削除
	/// </summary>
	/// <param name="obj">消すObject3Dのポインタ</param>
	void DeleteObject3d(Object3d *obj);

	/// <summary>
	/// 生成済オブジェクトの一括更新
	/// </summary>
	void UpdateAllObjects();

	/// <summary>
	/// 3Dオブジェクトの描画を実行するための前準備を行う
	/// </summary>
	/// <param name="cmd">ID3D12GraphicsCommandListのポインタ</param>
	void SetCommonBeginDrawObject3D();

	static ID3D12Device *GetDev() {
		return dev;
	}

private:
	bool isUpdated = false;

	//デバイスのポインタ
	static ID3D12Device *dev;

	/// <summary>
	/// 即時描画用ジオメトリシェーダーのコンパイル
	/// </summary>
	/// <returns>全シェーダーコンパイルの成否</returns>
	HRESULT QuickDrawShadersCompile();

	/// <summary>
	/// クラス内で使用するグラフィックスパイプラインの生成
	/// </summary>
	/// <param name="dev">ID3D12Deviceのポインタ</param>
	/// <returns>作成したPipeline3D構造体</returns>
	Pipeline3D Create3DPipelineState(ID3D12Device *dev);
};

/// <summary>
/// Object3DManagerの初期化
/// </summary>
/// <param name="dev">ID3D12Deviceのポインタ</param>
/// <param name="window_w">ウィンドウ横幅</param>
/// <param name="window_h">ウィンドウ縦幅</param>
inline void InitializeObject3DManager(ID3D12Device *dev, int window_w, int window_h) {
	Object3DManager::Get()->CreateObject3DManager(dev, window_w, window_h);
}

/// <summary>
/// Object3dの生成、管理クラスのコンテナに格納
/// </summary>
/// <param name="modelData">Model3Dのモデルデータ</param>
/// <param name="pos">初期位置を設定する</param>
/// <returns>生成されたObject3dを示すポインタ</returns>
Object3d *CreateObject3d(Model3D *modelData, Vector3 pos = { 0,0,0 });

/// <summary>
/// Object3dデータの削除
/// </summary>
/// <param name="obj"></param>
inline void DeleteObject3d(Object3d *obj) {
	Object3DManager::Get()->DeleteObject3d(obj);
}

inline void UpdateObject() {
	//全オブジェクトの更新
	Object3DManager::Get()->UpdateAllObjects();
}

//描画関数
void DrawObject3d(Object3d *obj);