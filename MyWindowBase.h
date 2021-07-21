#pragma once

#include<Windows.h>

class MyWindowBase 
{
public:

	int _x, _y;          //ウィンドウの左上座標
	int _width, _height; //ウィンドウのサイズ
	LPCWSTR _name;       //ウィンドウの名前

	MyWindowBase();

	UINT       GetMsg() const;
	static int GetCount();

	bool Init(LPCWSTR name, int posX = 0, int posY = 0, int width = 0, int height = 0);
	bool Show() const;
	bool Update() const;
	bool WindowsExist() const;
	bool Close(unsigned short key) const; //使用禁止
	bool CatchMsg();
	void Quit();
	void CountDown();
	bool ShutDown() const;

	static bool    HelperForMsgProcess(MyWindowBase& wnd);
	static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual ~MyWindowBase();

protected:

	HWND _hwnd;
	virtual LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:

	static int _count;
	WNDCLASSEX _wndClass;
	MSG        _msg;

	MyWindowBase(const MyWindowBase&) = delete;
	MyWindowBase& operator=(const MyWindowBase&) = delete;
};

using WindowBase = MyWindowBase;
using WndBase = WindowBase;

//-------------------------------------------------------------------------------------------------
// 
// WindowBaseクラスinline定義
// 
//-------------------------------------------------------------------------------------------------

//メッセージの取得
UINT MyWindowBase::GetMsg() const
{
	return _msg.message;
}

//作成されたウィンドウの合計数を返す
inline int MyWindowBase::GetCount()
{
	return WndBase::_count;
}

//ウィンドウ表示
inline bool MyWindowBase::Show() const
{
	return ::ShowWindow(_hwnd, SW_SHOW) ? true : false;
}

//ウィンドウの再描画
inline bool MyWindowBase::Update() const
{
	return ::UpdateWindow(_hwnd) ? true : false;
}

//ウィンドウが存在するならTrueを返す
inline bool MyWindowBase::WindowsExist() const
{
	return MyWindowBase::_count > 0;
}

//何らかのメッセージを受け取るとTrueを返す
inline bool MyWindowBase::CatchMsg()
{
	if (::PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&_msg);
		::DispatchMessage(&_msg);
		return true;
	}
	return false;
}

//廃止予定 : CountDown()を推奨
inline void MyWindowBase::Quit()
{
	--MyWindowBase::_count;
}

//ウィンドウの数をカウントダウン
inline void MyWindowBase::CountDown()
{
	--MyWindowBase::_count;
}
