
//---------------------------------------------------------------------------------
//独自のウィンドウプロシージャ実装方法
// - (1) WndBaseクラスをpublic継承する。その際の派生クラスの名前は任意。
// - (2) LocalWndProc()関数をオーバーライドし、関数定義する。
// - (3) 任意のコードを記述し、必ずWndBase::LocalWndProc()をreturnするよう注意する。
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//メインループによるウィンドウ別の処理を実装する方法
// - (a) 表示したいウィンドウの数だけオブジェクトを生成し、Init()とShow()を呼び出す。
// - (b) while()の条件を、ウィンドウの数が0になるまでループするように<WndBase::GetCount() != 0>にする。
// - (c) 作成したウィンドウの数だけメッセージを受け取るコードを記述する。
// - (d) 自分がやりたいことを記述する。
//----------------------------------------------------------------------------------------------------

#include"MyWindowBase.h"
#include<tchar.h>

using namespace std;

namespace //前方宣言
{
	// (1) WndBaseクラスをpublic継承する。その際の派生クラスの名前は任意。
	class AnyClassName : public WndBase
	{
		// (2) LocalWndProc()関数をオーバーライドし、関数定義する。
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	//例(1)(2)
	class MainWnd : public WndBase
	{
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

//例(a)(b)(c)(d)
int main()
{
	// (a) 表示したいウィンドウの数だけオブジェクトを生成し、Init()とShow()を呼び出す。
	AnyClassName aw;
	MainWnd mw;
	if (!aw.Init(_T("AnyWindowName"), 0, 0, 1000, 500)) return -1;
	if (!mw.Init(_T("Main"), 0, 0, 300, 300))  return -1;

	aw.Show(); aw.Update();
	mw.Show(); mw.Update();

	// (b) while()の条件を、ウィンドウの数が0になるまでループするように<WndBase::GetCount() != 0>にする。
	while (WndBase::GetCount() != 0)
	{
		// (c) 作成したウィンドウの数だけメッセージを受け取るコードを記述する。
		if (aw.CatchMsg())
		{
			switch (aw.GetMsg())
			{
			case WM_QUIT:
				aw.CountDown();
				break;

			default:
				break;
			}
			continue;
		}

		//この構文は上記の構文と同じことを行っています
		if (WndBase::HelperForMsgProcess(mw)) continue;

		// (d) 自分がやりたいことを記述する。
	}
}

namespace
{
	// (2) LocalWndProc()関数をオーバーライドし、関数定義する。
	LRESULT AnyClassName::LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// (3) 任意のコードを記述し、必ずWndBase::LocalWndProc()をreturnするよう注意する。
		//注意: DestroyWindow()とPostQuitMessage()を使わないでください！WndBase::LocalWndProc()内ですでに実装されています。

		return WndBase::LocalWndProc(hWnd, msg, wParam, lParam); //return文はこのように記述してください
	}

	//例(2)(3)
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