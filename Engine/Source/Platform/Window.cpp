// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Window.h"

#include "../Utility/Logger/Log.h"
#include "../Utility/Math/Functions.h"

namespace FM
{
	bool Win32Window::Init(WindowDesc& desc)
	{
		mDesc = desc;

		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

		mHInstance = GetModuleHandle(NULL);

		WNDCLASSEX windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = &WndProc; // Does this need to be passed by reference?
		windowClass.cbClsExtra = NULL;
		windowClass.cbWndExtra = NULL;
		windowClass.hInstance = mHInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = mDesc.id;
		windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&windowClass))
		{
			FM_LOG(Error) << "Failed to register window class.";
			return false;
		}

		DWORD windowWindowedStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_GROUP | WS_TABSTOP;

		if (true /*resizable*/)
			windowWindowedStyle |= WS_SIZEBOX | WS_MAXIMIZEBOX;

		DWORD windowFullscreenStyle = WS_CLIPSIBLINGS | WS_GROUP | WS_TABSTOP;

		DWORD windowStyle = windowWindowedStyle;
		DWORD windowExStyle = WS_EX_APPWINDOW;

		RECT windowRect = { 0, 0, static_cast<LONG>(desc.width), static_cast<LONG>(desc.height) };

		AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowExStyle);

		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		// Center the window within the screen
		int windowX = Math::Max(0, (screenWidth - windowWidth) / 2);
		int windowY = Math::Max(0, (screenHeight - windowHeight) / 2);

		mHWnd = CreateWindowEx(
			windowExStyle,
			mDesc.id,
			mDesc.title,
			windowStyle,
			windowX, windowY,
			windowWidth, windowHeight,
			NULL,
			NULL,
			mHInstance,
			this
		);

		if (!mHWnd)
		{
			FM_LOG(Error) << "Failed to create window.";
			return false;
		}

		ShowWindow(mHWnd, SW_SHOW);

		PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
		pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 32;
		pixelFormatDesc.cDepthBits = 24;
		pixelFormatDesc.cStencilBits = 8;
		pixelFormatDesc.cAuxBuffers = 0;
		pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

		HDC hDc = GetDC(mHWnd);

		int pixelFormat = ChoosePixelFormat(hDc, &pixelFormatDesc);

		if (!pixelFormat)
		{
			FM_LOG(Warning) << "Failed to choose pixel format.";
			return false;
		}

		DescribePixelFormat(hDc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);

		if (!SetPixelFormat(hDc, pixelFormat, &pixelFormatDesc))
		{
			FM_LOG(Warning) << "Failed to set pixel format.";
			return false;
		}

		ReleaseDC(mHWnd, hDc);

		return true;
	}

	bool Win32Window::Update()
	{
		MSG msg;

		while (PeekMessage(&msg, mHWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.message != WM_QUIT;
	}

	LRESULT Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (msg == WM_KEYDOWN ||
			msg == WM_SYSKEYDOWN ||
			msg == WM_KEYUP ||
			msg == WM_SYSKEYUP)
		{
			if (wParam == 0x1b)
			{
				PostQuitMessage(0);
				return 0;
			}

			if (!window->mOnKeyboard)
			{
				return 0;
			}

			bool isKeyDown = (msg == WM_KEYDOWN) || (msg == WM_SYSKEYDOWN);
			uint32 mask = (1 << 29);
			bool isAltDown = ((lParam & mask) != 0);

			window->mOnKeyboard(isKeyDown, isAltDown, uint32(wParam), window->mUserKeyboard);
		}

		if (msg == WM_LBUTTONDOWN ||
			msg == WM_LBUTTONUP ||
			msg == WM_LBUTTONDBLCLK ||
			msg == WM_MBUTTONDOWN ||
			msg == WM_MBUTTONUP ||
			msg == WM_MBUTTONDBLCLK ||
			msg == WM_RBUTTONDOWN ||
			msg == WM_RBUTTONUP ||
			msg == WM_RBUTTONDBLCLK ||
			msg == WM_MOUSEWHEEL ||
			msg == WM_MOUSEMOVE ||
			msg == WM_XBUTTONDOWN ||
			msg == WM_XBUTTONUP ||
			msg == WM_XBUTTONDBLCLK)
		{
			if (!window->mOnMouse)
			{
				return 0;
			}

			int x = static_cast<int>((int16)LOWORD(lParam));
			int y = static_cast<int>((int16)HIWORD(lParam));
			int wheelDelta = 0;

			if (msg == WM_MOUSEWHEEL)
			{
				wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
			}

			WORD state = LOWORD(wParam);
			bool isDownL = ((state & MK_LBUTTON) != 0);
			bool isDownR = ((state & MK_RBUTTON) != 0);
			bool isDownM = ((state & MK_MBUTTON) != 0);

			window->mOnMouse(x, y, wheelDelta, isDownL, isDownM, isDownR, window->mUserMouse);
		}

		switch (msg)
		{
		case WM_CREATE:
		{
			LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
		}
		break;

		case WM_DESTROY:
		{ PostQuitMessage(0); }
		break;

		case WM_CLOSE:
		{ DestroyWindow(hWnd); }
		break;

		case WM_CHAR:
		{
			if (!window->mOnChar)
			{
				return 0;
			}

			window->mOnChar(uint32(wParam), window->mUserChar);
		}
		break;

		case WM_SIZE:
		{
			uint32 w = static_cast<uint32>(LOWORD(lParam));
			uint32 h = static_cast<uint32>(HIWORD(lParam));

			//window->mWidth = w;
			//window->mHeight = h;

			if (!window->mOnResize)
			{
				return 0;
			}

			window->mOnResize(LOWORD(lParam), HIWORD(lParam), window->mUserResize);
		}
		break;

		default:
			break;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
