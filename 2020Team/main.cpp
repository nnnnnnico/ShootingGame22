#include"WinApi.h"
#include "DirectXSet.h"
#include "GameScene.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WinApi* winApi = nullptr;
	DirectXSet* dx = nullptr;
	Input* input = nullptr;
	GameScene* gameScene = nullptr;


	winApi = new WinApi();
	winApi->CreateGameWindow();

	dx = new DirectXSet();
	dx->Initialize(winApi);

	input = new Input();
	if (!input->Initialize(winApi->GetInstance(), winApi->GetHwnd())) {
		assert(0);
		return 1;
	}
	if (!Sprite::StaticInitialize(dx->GetDevice(), WinApi::window_width, WinApi::window_height)) {
		assert(0);
		return 1;
	}
	if(!Object3d::StaticInitialize(dx->GetDevice(), WinApi::window_width, WinApi::window_height)) {
		assert(0);
		return 1;
	}

	gameScene = new GameScene();
	gameScene->Initialize(dx,input);

	while (true) 
	{
		if (winApi->ProcessMessage()) { break; }

		input->Update();
		gameScene->Update();

		dx->PreDraw();
		gameScene->Draw();
		dx->PostDraw();
	}
	
	safe_delete(gameScene);
	safe_delete(input);
	safe_delete(dx);

	winApi->DeleteGameWIndow();
	safe_delete(winApi);

	return 0;
}