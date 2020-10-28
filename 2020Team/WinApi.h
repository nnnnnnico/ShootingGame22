#pragma once
#include <Windows.h>

class WinApi
{
public:
	static const int window_width = 1280;//�E�B���h�E�̉��̑傫��
	static const int window_height = 720;//�E�B���h�E�̏c�̑傫��
	static const wchar_t windowClassName[];

public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	void CreateGameWindow();

	void DeleteGameWIndow();

	bool ProcessMessage();

	HWND GetHwnd() { return hwnd; }

	HINSTANCE GetInstance() { return wndClass.hInstance; }
private:
	HWND hwnd = nullptr;
	WNDCLASSEX wndClass{};
};
