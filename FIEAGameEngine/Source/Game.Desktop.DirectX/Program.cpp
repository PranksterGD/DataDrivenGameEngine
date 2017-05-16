#include"pch.h"
#include <iostream>
#include <stdio.h>
#pragma comment (lib, "d3d11.lib")
using namespace FieaGameEngine;

IDXGISwapChain *swapchain;
ID3D11Device *dev;
ID3D11DeviceContext *devcon;
ID3D11RenderTargetView *backbuffer;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);

	//Creating an instance of the class defined in the Library
	SList<int> list;
	list.Front();
	HWND hWnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass1", L"Our First Windowed Program", WS_OVERLAPPEDWINDOW,
		300, 300, 500, 400, NULL, NULL, instance, NULL);

	ShowWindow(hWnd, showCommand);
	InitD3D(hWnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		RenderFrame();
	}

	CleanD3D();
	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CleanD3D()
{
	swapchain->Release();
	dev->Release();
	devcon->Release();
	backbuffer->Release();
}

void InitD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &scd, &swapchain, &dev, NULL, &devcon);

	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	devcon->RSSetViewports(1, &viewport);
}

void RenderFrame(void)
{
	float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	devcon->ClearRenderTargetView(backbuffer, color);
	swapchain->Present(0, 0);
}