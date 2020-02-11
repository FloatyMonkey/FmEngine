// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

// TODO: This shouldn't get included in a header file.
#include <windows.h>

#include "../../Utility/CoreTypes.h"

namespace FM
{
	typedef void(*MouseCallback)(int x, int y, int wheelDelta, bool leftDown, bool middleDown, bool rightDown, void* user);
	typedef void(*KeyboardCallback)(bool keyDown, bool altDown, uint32 keyCode, void* user);
	typedef void(*CharCallback)(uint32 keyCode, void* user);
	typedef void(*ResizeCallback)(uint32 w, uint32 h, void* user);

	struct WindowDesc
	{
		const char* id;
		const char* title;

		unsigned int width;
		unsigned int height;
	};

	class Win32Window
	{
	public:

		bool Init(WindowDesc& desc);

		bool Update();

	public:

		unsigned int GetWidth() const { return mDesc.width; }
		unsigned int GetHeight() const { return mDesc.height; }

		void* GetInstanceHandle() const { return mHInstance; }
		void* GetWindowHandle() const { return mHWnd; }

	public:

		void SetMouseCallback(MouseCallback func, void* user = nullptr)
		{
			mOnMouse = func;
			mUserMouse = user;
		}

		void SetKeyboardCallback(KeyboardCallback func, void* user = nullptr)
		{
			mOnKeyboard = func;
			mUserKeyboard = user;
		}

		void SetCharCallback(CharCallback func, void* user = nullptr)
		{
			mOnChar = func;
			mUserChar = user;
		}

		void SetResizeCallback(ResizeCallback func, void* user = nullptr)
		{
			mOnResize = func;
			mUserResize = user;
		}

	private:

		HINSTANCE mHInstance;
		HWND mHWnd;

		WindowDesc mDesc;

	private:

		MouseCallback mOnMouse;
		void* mUserMouse;
		KeyboardCallback mOnKeyboard;
		void* mUserKeyboard;
		CharCallback mOnChar;
		void* mUserChar;
		ResizeCallback mOnResize;
		void* mUserResize;

	private:

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
