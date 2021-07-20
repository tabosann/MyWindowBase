
//---------------------------------------------------------------------------------
//�Ǝ��̃E�B���h�E�v���V�[�W���������@
// - (1) WndBase�N���X��public�p������B���̍ۂ̔h���N���X�̖��O�͔C�ӁB
// - (2) LocalWndProc()�֐����I�[�o�[���C�h���A�֐���`����B
// - (3) �C�ӂ̃R�[�h���L�q���A�K��WndBase::LocalWndProc()��return����悤���ӂ���B
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//���C�����[�v�ɂ��E�B���h�E�ʂ̏���������������@
// - (a) �\���������E�B���h�E�̐������I�u�W�F�N�g�𐶐����AInit()��Show()���Ăяo���B
// - (b) while()�̏������A�E�B���h�E�̐���0�ɂȂ�܂Ń��[�v����悤��<WndBase::GetCount() != 0>�ɂ���B
// - (c) �쐬�����E�B���h�E�̐��������b�Z�[�W���󂯎��R�[�h���L�q����B
// - (d) ��������肽�����Ƃ��L�q����B
//----------------------------------------------------------------------------------------------------

#include"MyWindowBase.h"
#include<tchar.h>

using namespace std;

namespace //�O���錾
{
	// (1) WndBase�N���X��public�p������B���̍ۂ̔h���N���X�̖��O�͔C�ӁB
	class AnyClassName : public WndBase
	{
		// (2) LocalWndProc()�֐����I�[�o�[���C�h���A�֐���`����B
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	//��(1)(2)
	class MainWnd : public WndBase
	{
		LRESULT LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

//��(a)(b)(c)(d)
int main()
{
	// (a) �\���������E�B���h�E�̐������I�u�W�F�N�g�𐶐����AInit()��Show()���Ăяo���B
	AnyClassName aw;
	MainWnd mw;
	if (!aw.Init(_T("AnyWindowName"), 0, 0, 1000, 500)) return -1;
	if (!mw.Init(_T("Main"), 0, 0, 300, 300))  return -1;

	aw.Show(); aw.Update();
	mw.Show(); mw.Update();

	// (b) while()�̏������A�E�B���h�E�̐���0�ɂȂ�܂Ń��[�v����悤��<WndBase::GetCount() != 0>�ɂ���B
	while (WndBase::GetCount() != 0)
	{
		// (c) �쐬�����E�B���h�E�̐��������b�Z�[�W���󂯎��R�[�h���L�q����B
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

		//���̍\���͏�L�̍\���Ɠ������Ƃ��s���Ă��܂�
		if (WndBase::HelperForMsgProcess(mw)) continue;

		// (d) ��������肽�����Ƃ��L�q����B
	}
}

namespace
{
	// (2) LocalWndProc()�֐����I�[�o�[���C�h���A�֐���`����B
	LRESULT AnyClassName::LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// (3) �C�ӂ̃R�[�h���L�q���A�K��WndBase::LocalWndProc()��return����悤���ӂ���B
		//����: DestroyWindow()��PostQuitMessage()���g��Ȃ��ł��������IWndBase::LocalWndProc()���ł��łɎ�������Ă��܂��B

		return WndBase::LocalWndProc(hWnd, msg, wParam, lParam); //return���͂��̂悤�ɋL�q���Ă�������
	}

	//��(2)(3)
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