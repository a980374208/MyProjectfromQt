#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QAudioProbe>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void ON_stateChange(QMediaRecorder::State state);
    void ON_durationChanged(qint64 duration);
    void ON_audioBufferProbed(QAudioBuffer buffer);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGetFile_clicked();

    void on_actRecord_triggered();

    void on_actPause_triggered();

    void on_actStop_triggered();

    void on_actQuit_triggered();

private:
    Ui::MainWindow *ui;
    QAudioRecorder *m_pRecorder;
    QAudioProbe *m_pProbe;
};
#endif // MAINWINDOW_H
