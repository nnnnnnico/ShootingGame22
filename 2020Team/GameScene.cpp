#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {

}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(object3d);
}

void GameScene::Initialize(DirectXSet* dx)
{
	assert(dx);

	this->dx = dx;

	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

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
	//�w�ʂɉ摜��\�����鏊
	Sprite::PreDraw(cmdList);
	spriteBG->Draw();
	Sprite::PostDraw();
	dx->ClearDepthBuffer();

	Object3d::PreDraw(cmdList);

	object3d->Draw();

	Object3d::PostDraw();
	//�O�ʂɉ摜��\�����鏊
	Sprite::PreDraw(cmdList);
	Sprite::PostDraw();
}