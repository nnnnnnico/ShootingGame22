#include "Input.h"
#include <cassert>
#include<stdio.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̐���	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// �L�[�{�[�h�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// ���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	result = devMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// �r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	result = devMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return true;
}

void Input::Update(HWND hwnd)
{
	HRESULT result;

	result = devkeyboard->Acquire();	// �L�[�{�[�h����J�n
	result = devMouse->Acquire();

	// �O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�̓���
	result = devkeyboard->GetDeviceState(sizeof(key), key);
	result = devMouse->GetDeviceState(sizeof(Mouse), &Mouse);

	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);
}

bool Input::PushKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0�łȂ���Ή����Ă���
	if (key[keyNumber]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::LeftPush()
{
	if (Mouse.rgbButtons[0]) {
		return true;
	}

	return false;
}

bool Input::RightPush()
{
	if (Mouse.rgbButtons[1]) {
		return true;
	}

	return false;
}

bool Input::mouseX()
{
	if (pos.x = Mouse.lX) {
		return true;
	}
	return false;
}
