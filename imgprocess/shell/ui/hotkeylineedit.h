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

private:
    int         m_iHotKey;          //�ȼ�ֵ
    QString     m_strHotKey;         //�ȼ���ʾ�ַ����

};
#endif  //HOTKEYLINEEDIT_H