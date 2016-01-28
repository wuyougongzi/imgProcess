#include "hotkeylineedit.h"
#include <QKeyEvent>

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
    }
    else
    {

        //if(keyModefy) 
    }
    
   // qDebug(strHotKey.ascii());
    //else
}