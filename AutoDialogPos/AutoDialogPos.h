//==============================================================================
//							 AutoDialogPos.h
//							   
//begin	  : 2016/11/29
//describe: �Զ������Ի����λ��
//==============================================================================

#ifndef AUTODIALOGPOS_H
#define AUTODIALOGPOS_H

class QWidget;

//==============================================================================
//
//							  CAutoDialogPos
//							�Զ�Qt�����Ի����λ��
//
//==============================================================================

class CAutoDialogPos
{
public:
	// �Զ����ؼ���ʾ���ƶ������������Ļ������, bResize��ʾ�öԻ�������ʾʱ�����Զ���С����
	static void AdjustPos(QWidget* pWidget, bool bResize=true);
	// �Զ����ؼ���ʾ���ƶ������ʵ�λ��, nOffset��ʾ�ø��豸ͼԪ�Ĺ����С, bResize��ʾ�öԻ�������ʾʱ�����Զ���С����
	static void AdjustPos(QWidget* pWidget, int nOffset, bool bResize=true);

private:
	// �����Ժ����ӿڣ�����Ҫʵ����
	CAutoDialogPos();
public:
	~CAutoDialogPos();
};

#endif	// AUTODIALOGPOS_H

