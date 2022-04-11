#include "DX12B.h"
#include "FPS.h"
#include "Audio.h"
#include "TexManager.h"
#include "Object3DMgr.h"
#include "Sprite.h"
#include "imguiMgr.h"
#include "Player.h"

using namespace DirectX;
using namespace Microsoft::WRL;

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    WinAPI *WinApp;
    WinApp = new WinAPI;
    WinApp->CreateGameWindow();

    DX12B::Get()->Initialize(WinApp);

    myImgui::InitializeImGui(DX12B::Get()->GetDevice(), WinAPI::GetHWND());

    //オブジェクト管理
    Object3DManager::Get()->CreateObject3DManager(DX12B::Get()->GetDevice(), WinApp->window_width, WinApp->window_height);
    SpriteManager::Get()->CreateSpriteManager(DX12B::Get()->GetDevice(), DX12B::Get()->GetGCommandList(), WinApp->window_width, WinApp->window_height);
    TexManager::InitTexManager();

    //カメラ
    Camera* cam = camera;
    Vector3 eye = { 0.0f, 0.0f, -150.0f };
    Vector3 target = { 0.0f, 0.0f, 0.0f };
    Vector3 up = { 0.0f, 1.0f, 0.0f };
    cam->SetViewStatusEyeTargetUp(eye, target, up);

    //音
    Audio::Init();

#pragma endregion GameValue

    FPS::Get()->Start();

    //背景
    UINT backgroundGraph = TexManager::LoadTexture("./Resources/background.png");
    Sprite background;
    background.CreateSprite({ (float)WinAPI::window_width, (float)WinAPI::window_height }, { 0.0f, 0.0f }, backgroundGraph, true);

    //プレイヤー
    Player player;

    //ゲームループ
    while (true)
    {
        if (WinApp->ProcessMessage()) { break; }

        //更新
        Input::StartGetInputState();

        player.Update();
        
        player.object->color = { 1, 1, 1, 1 };

        Object3DManager::Get()->UpdateAllObjects();

        // 描画開始
        DX12B::Get()->StartDraw();

        // 背景描画
        SpriteManager::Get()->SetCommonBeginDraw();

        background.Draw();

        // オブジェクト描画
        Object3DManager::Get()->SetCommonBeginDrawObject3D();
  
        player.Draw();

        // 前景描画
        SpriteManager::Get()->SetCommonBeginDraw();

        // 描画終了
        DX12B::Get()->EndDraw();

        if (Input::isKey(DIK_ESCAPE))
        {
            break;
        }
        FPS::Get()->run();
    }

    myImgui::FinalizeImGui();

    WinApp->DeleteGameWindow();

    delete WinApp;
    WinApp = nullptr;

    return 0;
}
