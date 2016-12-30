//==============================================================================
//                  AutoDialogPos.h
// 
// begin    : 2016-11-29
// describe : auto move dialog to proper position.
//==============================================================================

#ifndef AUTODIALOGPOS_H
#define AUTODIALOGPOS_H

class QWidget;

//==============================================================================
//
//                            CAutoDialogPos
//                          �Զ�Qt�����Ի����λ��
//
//==============================================================================

class CAutoDialogPos
{
public:
    // �Զ����ؼ���ʾ���ƶ������������Ļ������, bResize��ʾ�öԻ�������ʾʱ�����Զ���С����
    static void AdjustPos(QWidget* pWidget, bool bResize=false);
    // �Զ����ؼ���ʾ���ƶ������ʵ�λ��, nOffset��ʾ�ø��豸ͼԪ�Ĺ����С, bResize��ʾ�öԻ�������ʾʱ�����Զ���С����
    static void AdjustPos(QWidget* pWidget, int nOffset, bool bResize=false);
    
private:
    // �����Ժ����ӿڣ�����Ҫʵ����
    CAutoDialogPos();
public:
    ~CAutoDialogPos();
};

#endif  // AUTODIALOGPOS_H

