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

void GameScene::Initialize(DirectXSet* dx, Input* input)
{
	assert(dx);
	assert(input);

	this->dx = dx;
	this->input = input;

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
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = object3d->GetPosition();

		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_UP)) { position.y += 0.5f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 0.5f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 0.5f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 0.5f; }

		// ���W�̕ύX�𔽉f
		object3d->SetPosition(position);
	}

	if (input->mouseLeft())
	{
		XMFLOAT3 position = object3d->GetPosition();
		position.x -= 0.1f;
		object3d->SetPosition(position);
	}

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}
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
	//sprite1->Draw();
	//sprite2->Draw();
	Sprite::PostDraw();
}