//==============================================================================
//							 NativeHook.cpp
//							   
// begin	: 2016/12/8
// describe	: ���ع���
//==============================================================================

#include <QSettings>
#include <QDebug>
#include <Windows.h>
#include "NativeHook.h"

#define HOOK_PASS_ON		0	// �������ݹ���
#define HOOK_THROW_AWAY		1	// ��������

#define TASKMANAGER	"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
#define DISTASKMGR	"DisableTaskMgr"

HHOOK g_keyHook;	// ���̹���
HWND g_hTray;		// ϵͳ������

// ���̹��Ӵ�����
LRESULT CALLBACK keyHookProc(int nCode,WPARAM wParam,LPARAM lParam );

// ����������
void HideTray(bool bState);
void DisableTaskMgr(bool bState);

//==============================================================================
//
//							  CNativeHook
//							   ���ػ�����
//
//==============================================================================

CNativeHook::CNativeHook()
{
	g_hTray = FindWindow(L"Shell_TrayWnd",NULL);

	SetHook();
	HideTray(true);
	DisableTaskMgr(true);
}

CNativeHook::~CNativeHook()
{
	CancelHook();
	HideTray(false);
	DisableTaskMgr(false);
}

void CNativeHook::SetHook()
{
	//�ײ���̹���
	g_keyHook =SetWindowsHookEx( WH_KEYBOARD_LL, keyHookProc, GetModuleHandle(NULL), 0);
}

void CNativeHook::CancelHook()
{
	UnhookWindowsHookEx(g_keyHook);
}

//���̹��ӹ���
LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam )
{
	//��WH_KEYBOARD_LLģʽ��lParam ��ָ��KBDLLHOOKSTRUCT���͵�ַ
	KBDLLHOOKSTRUCT* pKeyboardHook = (KBDLLHOOKSTRUCT *) lParam;
	//���nCode����HC_ACTION�������Ϣ�����С��0�������ӳ̾ͱ��뽫����Ϣ���ݸ� CallNextHookEx
	if(nCode == HC_ACTION)
	{
		switch(pKeyboardHook->vkCode)
		{
		case VK_ESCAPE:
			if(GetAsyncKeyState(VK_CONTROL) & 0x8000)
			{
				qDebug() << "Ctrl+Esc";
				return HOOK_THROW_AWAY;
			}
			break;
		case VK_TAB:
			if(pKeyboardHook->flags & LLKHF_ALTDOWN)
			{
				qDebug() << "Alt+Tab";
				return HOOK_THROW_AWAY;
			}
			break;
		case VK_LWIN:
		case VK_RWIN:
			qDebug() << "LWIN/RWIN";
			return HOOK_THROW_AWAY;
		case VK_F8:
			UnhookWindowsHookEx(g_keyHook);
			DisableTaskMgr(false);
			HideTray(false);
			break;
		default:
			break;
		}
	}
	return CallNextHookEx(g_keyHook, nCode, wParam, lParam);
}

void DisableTaskMgr(bool bState)
{
	return;

	QSettings objSettings(TASKMANAGER, QSettings::NativeFormat);
	if(bState)
	{
		objSettings.setValue(DISTASKMGR, "1");
	}
	else
	{
		objSettings.remove(DISTASKMGR);
	}
}

// ����
void HideTray(bool bState)
{
	return;

	if(bState)
	{
		ShowWindow(g_hTray, SW_HIDE);
	}
	else
	{
		ShowWindow(g_hTray, SW_SHOW);
	}
}

