#ifndef GENERATE
#define GENERATE

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QVector>

class Generate : public QObject, public QRunnable
{
     Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void recvNum(int num);
    void run() override;
signals:
    void sendArray(QVector<int> num);

private:
    int m_num;
};


class BubbleSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
   explicit BubbleSort(QObject *parent = nullptr);
   void recvArray(QVector<int> list);
    void run() override;
signals:
   void finish(QVector<int> num);

private:
   QVector<int> m_list;

};

class QuickSort : public QObject, public QRunnable
{
    Q_OBJECT
public:
   explicit QuickSort(QObject *parent = nullptr);
   void recvArray(QVector<int> list);
   void run() override;
private:
   void qucikSort(QVector<int> &list, int l,int r);
signals:
   void finish(QVector<int> list);

private:
   QVector<int> m_list;
};





#endif // GENERATE
