#include "hotkeylineedit.h"
#include <QKeyEvent>
#include <Windows.h>

HotKeyLineEdit::HotKeyLineEdit(QObject* parent)
{

}

HotKeyLineEdit::~HotKeyLineEdit()
{

}

int HotKeyLineEdit::getIHotKey()
{
    return m_iHotKey;
}

void HotKeyLineEdit::setIHotKey(int hotkey)
{
    m_iHotKey = hotkey;
}

QString HotKeyLineEdit::getStrHotKey()
{
    return m_strHotKey;
}

void HotKeyLineEdit::setStrHotKey(QString strHotKey)
{
    m_strHotKey = strHotKey;
}

void HotKeyLineEdit::keyPressEvent(QKeyEvent *pKeyEvent)
{
    int keyModefy = pKeyEvent->modifiers();

    QString strHotKey;
    bool hasModifier = false;
    if(keyModefy & Qt::ShiftModifier)
    {
        //按下了shift键
        strHotKey.append("Shift");
        hasModifier = true;
    }

    if(keyModefy & Qt::ControlModifier)
    {
        //按下了ctrl
        strHotKey.append("Ctrl");

    }

    if(keyModefy & Qt::AltModifier)
    {
        //按下了
        strHotKey.append("Alt");
    }

    int hotkey = pKeyEvent->key();
    
    //过滤一些不需要的快捷方式
    if(hotkey != Qt::Key_Escape || hotkey != Qt::Key_Enter)
    {
        m_iHotKey = hotkey;
        strHotKey.append(m_iHotKey - '0');
    }
    else
    {
        int test = 0;
        //if(keyModefy) 
    }
    
    //拿到key了之后作一个表映射到window的值
    qDebug(strHotKey.toAscii());
    //else
}

bool HotKeyLineEdit::winEvent(MSG *message, long *result)
{
    switch(message->message)
    {
    case WM_KEYDOWN:
        {
            //test
            int a = 0;
            //todo:
        }
        
        return true;
    case WM_CHAR:
        {
            //todo:
        }
        return true;
    default:
        break;
    }
    return QLineEdit::winEvent(message, result);
}

