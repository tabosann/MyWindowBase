#include"MyWindowBase.h"
#include<tchar.h>

using namespace std;

namespace // Forward declaration
{
	class AnyClassName : public WndBase
	{
		// Override this function if you want to use your own window procedure.
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	// e.g.
	class MainWnd : public WndBase
	{
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

int main()
{
	AnyClassName aw;
	MainWnd mw;
	if (!aw.Init(_T("AnyWindowName"), 0, 0, 1000, 500)) return -1;
	if (!mw.Init(_T("Main"), 0, 0, 300, 300))  return -1;

	aw.Show(); aw.Update();
	mw.Show(); mw.Update();

	// Refer to the following main loop syntax
	while (WndBase::GetCount() != 0)
	{
		if (aw.CatchMsg())
		{
			if (aw.GetMsg() == WM_QUIT)
				aw.Quit();
			continue;
		}

		// This syntax is equal to above one.
		if (WndBase::HelperForMsgProcess(mw)) continue;

		// Any syntaxes...
	}
}

namespace
{
	LRESULT AnyClassName::LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Any syntaxes...
		// NOTE: DO NOT USE DestroyWindow() AND PostQuitMessage()! THEY ARE USED IN WndBase::LocalWndProc().

		return WndBase::LocalWndProc(hWnd, msg, wParam, lParam); // Necessary
	}

	// e.g.
	LRESULT MainWnd::LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CREATE:
			MessageBox(_hwnd, _T("Main Window is being created..."), 0, 0);
			break;
		}
		return WndBase::LocalWndProc(hWnd, msg, wParam, lParam);
	}
}