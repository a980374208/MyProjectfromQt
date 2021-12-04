#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void ON_stateChanged(QMediaPlayer::State state);
    void ON_posiontionChanged(qint64 position);
    void ON_durationChanged(qint64 duration);
    void ON_PLayListIndexChanged(int index);
    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnClear_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_sliderPosition_valueChanged(int value);

    void on_sliderVolumn_valueChanged(int value);

    void on_btnSound_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_pPlayer;
    QMediaPlaylist *m_pPlaylist;
    QString m_strDurationTime;  //总时长
    QString m_strPositionTime;   //当前进度
};
#endif // MAINWINDOW_H
