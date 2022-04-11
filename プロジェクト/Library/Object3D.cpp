#include "Object3D.h"
#include "TexManager.h"
#include "DX12B.h"

void Object3d::InitObject3D(ID3D12Device *dev)
{
	//親にヌルを代入
	parent = nullptr;

	HRESULT result;
	const auto HEAP_PROP = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto RESDESC = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff);
	
	//定数バッファb0生成
	result =  dev->CreateCommittedResource(
		&HEAP_PROP,
		D3D12_HEAP_FLAG_NONE,
		&RESDESC,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0)
	);

	//定数バッファb1生成
	result = dev->CreateCommittedResource(
		&HEAP_PROP,
		D3D12_HEAP_FLAG_NONE,
		&RESDESC,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1)
	);

}

void Object3d::SetLoadedModelData(Model3D *loadedModel)
{
	model = loadedModel;

	isDirty = true;
}

void Object3d::UpdateObject3D()
{
	//ダーティフラグの挙動は検討中
	isDirty = true;

	//ダーティフラグが有効な時更新（通常オブジェクト）
	if (isDirty && isBillBoard != true) {

		XMMATRIX matScale, matRot, matTrans;

		// スケール、回転、平行行列の計算

		matScale = XMMatrixScaling(scale.x, scale.y, scale.z);

		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
		matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
		matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));

		matTrans = XMMatrixTranslation(position.x, position.y, position.z);

		matWorld = XMMatrixIdentity();
		matWorld *= matScale;
		matWorld *= matRot;
		matWorld *= matTrans;

		if (parent != nullptr)
		{
			matWorld *= parent->matWorld;
		}

		//定数バッファB0データ転送
		ConstBufferDataB0 *ConstMapB0 = nullptr;
		if (SUCCEEDED(constBuffB0->Map(0, nullptr, (void **)&ConstMapB0)))
		{
			ConstMapB0->mat = matWorld * camera->GetMatrixView() * Object3DManager::Get()->matProjection;
			ConstMapB0->color = this->color;
			constBuffB0->Unmap(0, nullptr);
		}

		//定数バッファB1データ転送
		ConstBufferDataB1 *ConstMapB1 = nullptr;
		if (SUCCEEDED(constBuffB1->Map(0, nullptr, (void **)&ConstMapB1)))
		{
			ConstMapB1->amdient = model->material.ambient;
			ConstMapB1->diffuse = model->material.diffuse;
			ConstMapB1->specular = model->material.specurar;
			ConstMapB1->alpha = model->material.alpha;
			constBuffB1->Unmap(0, nullptr);
		}

		//ダーティフラグリセット
		isDirty = false;
	}
	//ビルボードのとき
	else if (isDirty && isBillBoard) {
		UpdateBillBoard3D();

		isDirty = false;
	}
}

void Object3d::UpdateBillBoard3D()
{
	//ワールド変換用
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);

	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));

	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	matWorld = XMMatrixIdentity();

	matWorld *= camera->GetMatrixBillBoardAll();

	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;

	if (parent != nullptr)
	{
		matWorld *= parent->matWorld;
	}

	//定数バッファB0データ転送
	ConstBufferDataB0 *ConstMapB0 = nullptr;
	if (SUCCEEDED(constBuffB0->Map(0, nullptr, (void **)&ConstMapB0)))
	{
		ConstMapB0->mat = matWorld * camera->GetMatrixView() * Object3DManager::Get()->matProjection;
		ConstMapB0->color = this->color;
		constBuffB0->Unmap(0, nullptr);
	}

	//定数バッファB1データ転送
	ConstBufferDataB1 *ConstMapB1 = nullptr;
	if (SUCCEEDED(constBuffB1->Map(0, nullptr, (void **)&ConstMapB1)))
	{
		ConstMapB1->amdient		= model->material.ambient;
		ConstMapB1->diffuse		= model->material.diffuse;
		ConstMapB1->specular	= model->material.specurar;
		ConstMapB1->alpha		= model->material.alpha;
		constBuffB1->Unmap(0, nullptr);
	}
}

void Object3d::DrawModel3D(Object3d *obj, ID3D12GraphicsCommandList *cmd, ID3D12Device *dev)
{
	//頂点バッファ設定
	cmd->IASetVertexBuffers(0, 1, &obj->model->vbView);
	//インデックスバッファ設定
	cmd->IASetIndexBuffer(&obj->model->ibview);
	//定数バッファ設定
	cmd->SetGraphicsRootConstantBufferView(0, obj->constBuffB0->GetGPUVirtualAddress());
	//定数バッファ設定
	cmd->SetGraphicsRootConstantBufferView(1, obj->constBuffB1->GetGPUVirtualAddress());

	//シェーダーリソースビューをセット
	cmd->SetGraphicsRootDescriptorTable(2,
	CD3DX12_GPU_DESCRIPTOR_HANDLE(Object3DManager::Get()->descheap->GetGPUDescriptorHandleForHeapStart(),
	obj->model->material.texNumber, dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//描画
	cmd->DrawIndexedInstanced(obj->model->indices.size(), 1, 0, 0, 0);
}

void Object3d::DrawModel3D(ID3D12GraphicsCommandList *cmd, ID3D12Device *dev)
{
	//頂点バッファ設定
	cmd->IASetVertexBuffers(0, 1, &model->vbView);
	//インデックスバッファ設定
	cmd->IASetIndexBuffer(&model->ibview);
	//定数バッファ設定
	cmd->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	//定数バッファ設定
	cmd->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());

	//シェーダーリソースビューをセット
	cmd->SetGraphicsRootDescriptorTable(2,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(TexManager::texDsvHeap.Get()->GetGPUDescriptorHandleForHeapStart(),
			model->material.texNumber, dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//描画
	cmd->DrawIndexedInstanced(model->indices.size(), 1, 0, 0, 0);
}

void Object3d::DrawModel3DSelectTexture(UINT useTexNum)
{
	if (TexManager::textureData[useTexNum].texBuff == nullptr) {

		return;
	}

	DX12B_CMD->IASetVertexBuffers(0, 1, &model->vbView);
	DX12B_CMD->IASetIndexBuffer(&model->ibview);
	DX12B_CMD->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	DX12B_CMD->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());
	DX12B_CMD->SetGraphicsRootDescriptorTable(2,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(TexManager::texDsvHeap.Get()->GetGPUDescriptorHandleForHeapStart(),
			useTexNum, DX12B_DEV->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//描画
	DX12B_CMD->DrawIndexedInstanced(model->indices.size(), 1, 0, 0, 0);
}

