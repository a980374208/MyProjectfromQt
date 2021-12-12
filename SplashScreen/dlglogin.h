#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLogin(QWidget *parent = nullptr);
    ~DlgLogin();

private slots:
    void on_btnOK_clicked();
private:
    void WriteSetting();
    void ReadSettings();
    QString Encrypt(const QString& str);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    Ui::DlgLogin *ui;
    QString m_User;
    QString m_Password;
    int m_TryCount=0;
    QPoint m_LastPos;
    bool m_MouseMoving;

};

#endif // DLGLOGIN_H
