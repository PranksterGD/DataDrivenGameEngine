#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
// function prototypes
void InitD3D(HWND hWnd);     // sets up and initializes Direct3D
void CleanD3D(void);         // closes Direct3D and releases memory
void RenderFrame(void);     // renders a single frame

							 // the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);