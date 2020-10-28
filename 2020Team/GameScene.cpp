#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {

}

GameScene::~GameScene()
{
	safe_delete(object3d);
}

void GameScene::Initialize(DirectXSet* dx)
{
	assert(dx);

	this->dx = dx;

	object3d = Object3d::Create();
	object3d->Update();
}

void GameScene::Update()
{
	object3d->Update();
}

void GameScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dx->GetCommandList();
	dx->ClearDepthBuffer();

	Object3d::PreDraw(cmdList);

	object3d->Draw();

	Object3d::PostDraw();
}