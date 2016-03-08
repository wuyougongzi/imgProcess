#ifndef HOTKEYLINEEDIT_H
#define HOTKEYLINEEDIT_H

#include <QLineEdit>

class HotKeyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    HotKeyLineEdit(QObject* parent);
    ~HotKeyLineEdit();

public:
    int getIHotKey();
    void setIHotKey(int hotkey);
    QString getStrHotKey();
    void setStrHotKey(QString strHotKey);
protected:
    virtual void keyPressEvent(QKeyEvent *pKeyEvent)    override;
    virtual bool winEvent(MSG *message, long *result)   override;
private:
    int         m_iHotKey;          //热键值
    QString     m_strHotKey;         //热键表示字符组合

};
#endif  //HOTKEYLINEEDIT_H