//==============================================================================
//							 AutoDialogPos.cpp
//							   
//begin	  : 2016/11/29
//describe: �Զ������Ի����λ��
//==============================================================================
#include <cassert>
#include <QApplication>
#include <QDesktopWidget>
#include "AutoDialogPos.h"

#define SCREEN_OFFSET_H		25		// �Ի�������Ļ���ұߵ���С�߽�λ��
#define SCREEN_OFFSET_V		50		// �Ի�������Ļ���±ߵ���С�߽�λ��
#define WIDGET_TITLE_OFFSET 35		// �Ի���ı���������߶�

//==============================================================================
//
//							  CAutoDialogPos
//							�Զ�Qt�����Ի����λ��
//
//==============================================================================

void CAutoDialogPos::AdjustPos(QWidget* pWidget, bool bResize)
{
	if(NULL == pWidget)
	{
		return;
	}

	// ��ȡ���������Ļ������
	QPoint objCursorPoint = pWidget->cursor().pos();

	// ��ȡ���������Ļ�ĳߴ�
	QDesktopWidget* pDesktop = QApplication::desktop();
	if(NULL == pDesktop)
	{
		return;
	}
	QRect objScreenRect = pDesktop->screenGeometry(objCursorPoint);
	
	// ���������Զ��仯����ô��������ʾ��ʱ����ߴ������Ч��
	if(bResize)
	{
		pWidget->show();
	}
	// ��ȡ�ؼ��ĳߴ�
	QSize objWidgetSize = pWidget->size();

	// ����������Ҫ�ƶ�������Ļ����
	int nPosX = (objScreenRect.width()-objWidgetSize.width())/2 + objScreenRect.x();
	int nPosY = (objScreenRect.height()-WIDGET_TITLE_OFFSET-objWidgetSize.height())/2 + objScreenRect.y();

	pWidget->move(nPosX, nPosY);
}

void CAutoDialogPos::AdjustPos(QWidget* pWidget, int nOffset, bool bResize)
{
	if(NULL == pWidget)
	{
		return;
	}

	// ��ȡ���������Ļ������
	QPoint objCursorPoint = pWidget->cursor().pos();

	// ��ȡ���������Ļ�ĳߴ�
	QDesktopWidget* pDesktop = QApplication::desktop();
	if(NULL == pDesktop)
	{
		return;
	}
	QRect objScreenRect = pDesktop->screenGeometry(objCursorPoint);

	if(bResize)
	{
		// ���������Զ��仯����ô��������ʾ��ʱ����ߴ������Ч��
		pWidget->show();
	}
	// ��ȡ�ؼ��ĳߴ�
	QSize objWidgetSize = pWidget->size();

	// ����������Ҫ�ƶ�������Ļ����
	int nPosX=0;
	int nPosY=0;

	// ��ʼ��������λ�úͿؼ��Ĵ�С����ռ����ʾ����
	if(objCursorPoint.x()+nOffset+objWidgetSize.width()+SCREEN_OFFSET_H < objScreenRect.x()+objScreenRect.width())
	{
		// �öԻ��������ʾ���ұ�
		nPosX = objCursorPoint.x()+nOffset;
	}
	else if(objCursorPoint.x()-nOffset-objWidgetSize.width()-SCREEN_OFFSET_H > objScreenRect.x())
	{
		// �öԻ��������ʾ�����
		nPosX = objCursorPoint.x()-nOffset-objWidgetSize.width();
	}
	else
	{
		// �öԻ���̫���ˣ���ʾ���ұߣ����ǻ�����ڵ�
		nPosX = objScreenRect.x() + (objScreenRect.width()-objWidgetSize.width()-SCREEN_OFFSET_H);
	}

	// ����y������
	if(objWidgetSize.height() > objScreenRect.height())
	{
		// �ÿؼ��ĸ߶ȴ�����Ļ�ܹ���ʾ�����߶ȣ���ʱ�Ի������Ŷ�����ʾ
		nPosY = SCREEN_OFFSET_V;
	}
	else if(objCursorPoint.y()+objWidgetSize.height()/2 >= objScreenRect.height()-SCREEN_OFFSET_V)
	{
		// �ô��ڹ�����ʾ������Ļ�ױ߽�
		nPosY = objScreenRect.height() - SCREEN_OFFSET_V - objWidgetSize.height() - WIDGET_TITLE_OFFSET;
	}
	else if(objCursorPoint.y()-objWidgetSize.height()/2 <= SCREEN_OFFSET_V)
	{
		// �������λ�ù��ߣ���ʾ������Ļ���߽�
		nPosY = SCREEN_OFFSET_V;
	}
	else 
	{
		// һ������¸öԻ������Ļ����������λ��ͬ��
		nPosY = objCursorPoint.y()-objWidgetSize.height()/2;
	}

	pWidget->move(nPosX, nPosY);
}


CAutoDialogPos::CAutoDialogPos()
{

}

CAutoDialogPos::~CAutoDialogPos()
{

}
