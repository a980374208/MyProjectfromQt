#ifndef GENERATE
#define GENERATE

#include <QObject>
#include <QThread>
#include <QVector>

class Generate : public QObject
{
     Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void working(int m);
    //void recvNum(int num);
signals:
    void sendArray(QVector<int> num);
//protected:
//    void run() override;
private:
    //int m_num;
};


class BubbleSort : public QObject{
    Q_OBJECT
public:
   explicit BubbleSort(QObject *parent = nullptr);
    void working(QVector<int> m_list);
   //void recvArray(QVector<int> list);
signals:
   void finish(QVector<int> num);
//protected:
//   void run() override;
private:
   //QVector<int> m_list;

};

class QuickSort : public QObject{
    Q_OBJECT
public:
   explicit QuickSort(QObject *parent = nullptr);
   void working(QVector<int> m_list);
   //void recvArray(QVector<int> list);
private:
   void qucikSort(QVector<int> &list, int l,int r);
signals:
   void finish(QVector<int> list);
//protected:
   //void run() override;
private:
   //QVector<int> m_list;
};





#endif // GENERATE
