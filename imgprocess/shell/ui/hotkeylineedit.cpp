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
