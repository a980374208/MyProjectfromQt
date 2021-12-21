#ifndef THREAD_H
#define THREAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Thread; }
QT_END_NAMESPACE

class Thread : public QMainWindow
{
    Q_OBJECT

public:
    Thread(QWidget *parent = nullptr);
    ~Thread();
signals:
    void starting(int n);
private:
    Ui::Thread *ui;
};
#endif // THREAD_H
