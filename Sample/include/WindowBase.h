#pragma once

#include<Windows.h>
#include<tchar.h>

namespace WindowBaseLibrary
{
	//--------------------------------------------------------------------------------------------------------------
	// 
	// �E�B���h�E�̓o�^�A�쐬�݂̂��s���N���X
	// 
	//--------------------------------------------------------------------------------------------------------------
	class WindowFactory
	{
	//�����o�ϐ�
	protected:

		WNDCLASSEX		_wndClass;	//�E�B���h�E�̊�{�ݒ��ێ�����\����
		CREATESTRUCT	_cs;		//�E�B���h�E�쐬�ɕK�v�ȃp�����[�^��ێ�����\����
		HWND			_hwnd;		//�E�B���h�E�n���h��(���E�B���h�E�I�u�W�F�N�g�̃|�C���^)

	//�R���X�g���N�^
	protected:

		WindowFactory();
		WindowFactory(const WindowFactory&) = delete;
		WindowFactory& operator=(const WindowFactory&) = delete;

	//�������֘A
	protected:

		//�E�B���h�E�̐ݒ肩��쐬�܂ł��s���A���\�����Ă����v�ȏ�Ԃɂ���B
		bool			Init(
			LPCTSTR className,
			int		posX   = CW_USEDEFAULT,
			int		posY   = CW_USEDEFAULT,
			int		width  = CW_USEDEFAULT,
			int		height = CW_USEDEFAULT
		);

		//�ݒ肵���E�B���h�E�̌����ڂ�v���V�[�W����o�^����B
		bool			RegisterWindowClass(LPCTSTR className);

		//�o�^�����E�B���h�E�̐ݒ�ŃE�B���h�E���쐬�B
		bool			CreateMainWindow(HINSTANCE hInstance, LPCTSTR className);

	//�E�B���h�E�v���V�[�W��
	protected:
		virtual LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	private:
		static	LRESULT GlobalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//��Еt��
	protected:

		//�������
		bool			Release();

	//�A�N�Z�b�T
	public:

		WNDCLASSEX		GetWndClass() const;
		CREATESTRUCT	GetCreateStruct() const;
		void			SetWindowClass(const WNDCLASSEX& wndClass);
		void			SetCreateStruct(const CREATESTRUCT& cs);
	};

	//--------------------------------------------------------------------------------------------------------------
	// 
	// �쐬���ꂽ�E�B���h�E���A���[�U�[�������₷���e�R���ꂳ�ꂽ�N���X
	// 
	//--------------------------------------------------------------------------------------------------------------
	class WindowBase : public WindowFactory
	{
	//�Ǝ��������\�ȃ����o�֐�
	public:

		//�e���I�[�o�[���C�h���ēƎ��̎������ł��܂��B
		virtual LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual void	MainLoop();

	//�����ς݃����o�֐�
	public:

		bool			Begin(
			LPCTSTR className,
			int		posX   = CW_USEDEFAULT,
			int		posY   = CW_USEDEFAULT,
			int		width  = CW_USEDEFAULT,
			int		height = CW_USEDEFAULT
		);
		void			ShowWindow() const;
		bool			UpdateWindow() const;
		bool			End();

	//�E�B���h�E�ɑ΂��鑀����s���N���X
	private:

		class WindowCommander;
	};

	//--------------------------------------------------------------------------------------------------------------
	// 
	// �E�B���h�E�ɑ΂��鑀��݂̂��s���N���X(WindowBase�N���X�̂݃A�N�Z�X�\�ȃN���X)
	// 
	//--------------------------------------------------------------------------------------------------------------
	class WindowBase::WindowCommander
	{
	public:

		//�E�B���h�E�̕\��
		static void		ShowWindow(HWND hwnd);
		//WM_PAINT���b�Z�[�W�̑��M
		static bool		UpdateWindow(HWND hwnd);

		//���[�v�����̃T���v��
		static void		SampleMainLoop(HWND hwnd);
		//�Q�[���̃��C�����[�v������
		static void		SampleGameLoop(HWND hwnd);
	};
}
namespace wbl = WindowBaseLibrary;

#include"impl\WindowBase_Impl.h"

#pragma comment(lib, "WindowBase.lib")
