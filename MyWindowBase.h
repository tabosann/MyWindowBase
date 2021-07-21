#pragma once

#include<Windows.h>

class MyWindowBase 
{
public:

	int _x, _y;          //�E�B���h�E�̍�����W
	int _width, _height; //�E�B���h�E�̃T�C�Y
	LPCWSTR _name;       //�E�B���h�E�̖��O

	MyWindowBase();

	UINT       GetMsg() const;
	static int GetCount();

	bool Init(LPCWSTR name, int posX = 0, int posY = 0, int width = 0, int height = 0);
	bool Show() const;
	bool Update() const;
	bool WindowsExist() const;
	bool Close(unsigned short key) const; //�g�p�֎~
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
// WindowBase�N���Xinline��`
// 
//-------------------------------------------------------------------------------------------------

//���b�Z�[�W�̎擾
UINT MyWindowBase::GetMsg() const
{
	return _msg.message;
}

//�쐬���ꂽ�E�B���h�E�̍��v����Ԃ�
inline int MyWindowBase::GetCount()
{
	return WndBase::_count;
}

//�E�B���h�E�\��
inline bool MyWindowBase::Show() const
{
	return ::ShowWindow(_hwnd, SW_SHOW) ? true : false;
}

//�E�B���h�E�̍ĕ`��
inline bool MyWindowBase::Update() const
{
	return ::UpdateWindow(_hwnd) ? true : false;
}

//�E�B���h�E�����݂���Ȃ�True��Ԃ�
inline bool MyWindowBase::WindowsExist() const
{
	return MyWindowBase::_count > 0;
}

//���炩�̃��b�Z�[�W���󂯎���True��Ԃ�
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

//�p�~�\�� : CountDown()�𐄏�
inline void MyWindowBase::Quit()
{
	--MyWindowBase::_count;
}

//�E�B���h�E�̐����J�E���g�_�E��
inline void MyWindowBase::CountDown()
{
	--MyWindowBase::_count;
}
