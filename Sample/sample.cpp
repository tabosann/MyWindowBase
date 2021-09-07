
#include<WindowBase.h>

using namespace wbl;

//WindowBase�N���X���p�����邱�ƂŁA�Ǝ��̓���������ł���B
class GameWindow : public WindowBase
{
public:

	//���L�Q�̊֐��̂݁A�I�[�o�[���C�h�ɂ��Ǝ��̎������ł��܂��B
	LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void	MainLoop();
};

static int gGameCounter	 = 0;	//�Q�[���������ʂ�����
static int gMsgCounter	 = 0;	//���b�Z�[�W������������
static int gPaintCounter = 0;	//WM_PAINT���b�Z�[�W������������

int main()
{
	GameWindow hwnd;

	WNDCLASSEX wndClass = hwnd.GetWndClass();					//(�K�{)���̃E�B���h�E�ݒ���擾
	wndClass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);	//�V�����E�B���h�E�̐ݒ���s��
	hwnd.SetWindowClass(wndClass);								//���̐V�����ݒ��K�p����

	if (hwnd.Begin(_T("GameWindow")))
	{
		//Begin�֐���End�֐��̊ԂŃE�B���h�E�̑�����s��
		hwnd.ShowWindow();
		hwnd.UpdateWindow();
		hwnd.MainLoop();

		hwnd.End();
	}
}

// �ϒ������������镶����̍쐬
static int CreateStr(TCHAR* dst, const TCHAR* format, ...);

LRESULT GameWindow::LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	++gMsgCounter;

	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(hwnd, _T("�悤�����I�T���v���v���O�����ցI"), _T("�T���v���v���O����"), 0);
		break;
	}
	case WM_PAINT:
	{
		++gPaintCounter;

		//�N���C�A���g�̈�ւ̕`��J�n
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// NOTE : BeginPaint�֐���EndPaint�֐��̊Ԃɕ`�揈�����L�q

		//��������߂�g�̑傫�����擾�ł���
		TEXTMETRIC metric;
		GetTextMetrics(hdc, &metric);

		//�������\��������W��ݒ�(��_�͍���)
		POINT drawPos = { 0, 0 };

		//�N���C�A���g�̈�̒��S��WM_PAINT���Ă΂ꂽ�񐔂�`��
		int	   length;
		TCHAR* str = nullptr;
		length = CreateStr(str, _T("gGameCounter : %d"), gGameCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		drawPos.y += metric.tmHeight; //���s

		length = CreateStr(str, _T("gMsgCounter : %d"), gMsgCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		drawPos.y += metric.tmHeight; //���s

		length = CreateStr(str, _T("gPaintCounter : %d"), gPaintCounter);
		TextOut(hdc, drawPos.x, drawPos.y, str, length);

		//�`��I��(����ȍ~�͕`��֎~)
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_KEYDOWN:
	{
		//Space�L�[����������ƃE�B���h�E�����(�j��)
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
		//�E�B���h�E���j������Ă����烋�[�v�𔲂���B
		if (IsWindow(_hwnd) == 0) break;

		//���b�Z�[�W����
		if (PeekMessage(&msg, _hwnd, NULL, NULL, PM_REMOVE))
		{
			//���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		//�Q�[������
		++gGameCounter;
	}
}

int CreateStr(TCHAR* dst, const TCHAR* format, ...)
{
	int length = -1;
	va_list args;
	va_start(args, format);

	// ������̃o�b�t�@�T�C�Y���Z�o
	size_t size = _vsctprintf(format, args) + 1;

	// ������̍쐬
	if (dst = new TCHAR[size])
		length = _vstprintf_s(dst, size, format, args);

	va_end(args);
	return length;
}
