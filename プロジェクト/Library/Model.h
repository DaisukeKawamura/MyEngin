#pragma once
#include <d3dx12.h>
#include <DirectXMath.h>
#include <wrl.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

#include "Object3DMgr.h"

//頂点データ
struct Vertex
{
	XMFLOAT3 pos;		//xyz
	XMFLOAT3 normal;	//法線
	XMFLOAT2 uv;		//uv
};

//マテリアルデータ構造体
struct Material
{
	string   mtlName;		//マテリアル名(objファイルからではない場合、使わなくていい？)
	XMFLOAT3 ambient;		//アンビエント
	XMFLOAT3 diffuse;		//ディフューズ
	XMFLOAT3 specurar;		//スペキュラー
	float    alpha;			//アルファ
	string   texFileName;	//テクスチャ名
	UINT     texNumber;		//テクスチャ番号(使用する場合必ず必要)
	//コンストラクタ
	Material() {
		ambient = { 1.0f,1.0f,1.0f };
		diffuse = { 0.8f,0.8f,0.8f };
		specurar = { 0.8f,0.8f,0.8f };
		alpha = 1.0f;
	}
};

class Object3DManager;

class Model3D
{
public:
	//頂点データ
	vector<Vertex> vertices;
	//頂点インデックス
	vector<unsigned short> indices;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデクスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibview{};
	//マテリアル
	Material material;

public:

	Model3D() {};

	//objファイル読み込み
	void LoadObjModel(const char *filename);
	//マテリアル読み込み。LoadObjModel内で実行され、materialにデータを格納
	void LoadMatarial(string fileName,string filepath);

	//xy平面を作成
	//void CreatePlaneModelXY(float x_size, float y_size, string useTexFileName, ID3D12Device *dev, Object3DManager *mgr);

	//xy平面を作成。ロード済テクスチャを使用
	void CreatePlaneModelXY(float x_size, float y_size, float uv_x, float uv_y, UINT useTexNum);
	//xz平面
	void CreatePlaneModelXZ(float x_size, float z_size, float uv_x, float uv_y, UINT useTexNum);
	//yz平面
	void CreatePlaneModelYZ(float y_size, float z_size, float uv_x, float uv_y, UINT useTexNum);

	//立方体モデルデータ作成
	void CreateBoxModel(float size, float uv_x, float uv_y, UINT useTexNum);

	//アニメーションテクスチャの使用するアニメーションの番号を変更（uv制御）
	void ChangeTexAnimationNumber(int useAnimNum);
};

