
#include<WindowBase.h>

using namespace wbl;

//WindowBaseクラスを継承することで、独自の動作を実装できる。
class GameWindow : public WindowBase
{
public:

	//下記２つの関数のみ、オーバーライドによる独自の実装ができます。
	LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void	MainLoop();
};

static int gGameCounter	 = 0;	//ゲーム処理が通った回数
static int gMsgCounter	 = 0;	//メッセージを処理した回数
static int gPaintCounter = 0;	//WM_PAINTメッセージを処理した回数

int main()
{
	GameWindow hwnd;

	WNDCLASSEX wndClass = hwnd.GetWndClass();					//(必須)元のウィンドウ設定を取得
	wndClass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);	//新しいウィンドウの設定を行う
	hwnd.SetWindowClass(wndClass);								//その新しい設定を適用する

	if (hwnd.Begin(_T("GameWindow")))
	{
		//Begin関数とEnd関数の間でウィンドウの操作を行う
		hwnd.ShowWindow();
		hwnd.UpdateWindow();
		hwnd.MainLoop();

		hwnd.End();
	}
}

// 可変長引数を扱える文字列の作成
static int CreateStr(TCHAR* dst, const TCHAR* format, ...);

LRESULT GameWindow::LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	++gMsgCounter;

	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(hwnd, _T("ようこそ！サンプルプログラムへ！"), _T("サンプルプログラム"), 0);
		break;
	}
	case WM_PAINT:
	{
		++gPaintCounter;

		//クライアント領域への描画開始
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// NOTE : BeginPaint関数とEndPaint関数の間に描画処理を記述

		//文字が占める枠の大きさを取得できる
		TEXTMETRIC metric;
		GetTextMetrics(hdc, &metric);

		//文字列を表示する座標を設定(基準点は左上)
		POINT drawPos = { 0, 0 };

		//クライアント領域の中心にWM_PAINTが呼ばれた回数を描画
		int	   length;
		TCHAR* str = nullptr;
		length = CreateStr(str, _T("gGameCounter : %d"), gGameCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		drawPos.y += metric.tmHeight; //改行

		length = CreateStr(str, _T("gMsgCounter : %d"), gMsgCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		drawPos.y += metric.tmHeight; //改行

		length = CreateStr(str, _T("gPaintCounter : %d"), gPaintCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		//描画終了(これ以降は描画禁止)
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_KEYDOWN:
	{
		//Spaceキーを押下するとウィンドウを閉じる(破棄)
		if (wparam == VK_SPACE) DestroyWindow(hwnd);
		break;
	}
	default:
		break;
	}
	return WindowBase::LocalWndProc(hwnd, msg, wparam, lparam);
}

void GameWindow::MainLoop()
{
	MSG	 msg;
	while (true)
	{
		//ウィンドウが破棄されていたらループを抜ける。
		if (IsWindow(_hwnd) == 0) break;

		//メッセージ処理
		if (PeekMessage(&msg, _hwnd, NULL, NULL, PM_REMOVE))
		{
			//メッセージ処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		//ゲーム処理
		++gGameCounter;
	}
}

int CreateStr(TCHAR* dst, const TCHAR* format, ...)
{
	int length = -1;
	va_list args;
	va_start(args, format);

	// 文字列のバッファサイズを算出
	size_t size = _vsctprintf(format, args) + 1;

	// 文字列の作成
	if (dst = new TCHAR[size])
		length = _vstprintf_s(dst, size, format, args);

	va_end(args);
	return length;
}
