#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmygraphicsview.h"
#include <QTime>
#include <QGraphicsRectItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
    label_itemInfor = new QLabel("ItemInfor:");
    label_itemInfor->setMinimumWidth(150);
    ui->statusbar->addWidget(label_itemInfor);

    m_scene = new QGraphicsScene(-300,-100,600,200);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);//设置可区域选择（鼠标拉动选择）

    connect(ui->graphicsView,&QMyGraphicsView::mouseDoubleClick,this,&MainWindow::on_mouseDoubleClick);
    connect(ui->graphicsView,&QMyGraphicsView::mousePress,this,&MainWindow::on_mousePress);
    connect(ui->graphicsView,&QMyGraphicsView::keyPress,this,&MainWindow::on_keyPress);

    srand(QTime::currentTime().second());
}

void MainWindow::on_mousePress(QPoint *point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(*point);
    QGraphicsItem *item = nullptr;
    item = m_scene->itemAt(pointScene,ui->graphicsView->transform());
    if(item == nullptr) return;
    label_itemInfor->setText("ItemInfor:"+
                             item->data(ItemId).toString()+","+
                             item->data(ItemDescription).toString());


}

#include <QColorDialog>
void MainWindow::on_mouseDoubleClick(QPoint *point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(*point);
    QGraphicsItem *item = nullptr;
    item = m_scene->itemAt(pointScene,ui->graphicsView->transform());
    if(item == nullptr) return;
    switch(item->type()){
    case QGraphicsRectItem::Type:{
        QGraphicsRectItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        QColor color = theItem->brush().color();
        color = QColorDialog::getColor(color,nullptr,"选择颜色");
        if(color == nullptr) return;
        theItem->setBrush(QBrush(color));
        break;
    }
    case QGraphicsEllipseItem::Type:{
        QGraphicsEllipseItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        QColor color = theItem->brush().color();
        color = QColorDialog::getColor(color,nullptr,"选择颜色");
        if(color == nullptr) return;
        theItem->setBrush(QBrush(color));
        break;
    }
    case QGraphicsLineItem::Type:{
        QGraphicsLineItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
        QColor color = theItem->pen().color();
        color = QColorDialog::getColor(color,nullptr,"选择颜色");
        if(color == nullptr) return;
        QPen pen(theItem->pen());
        pen.setColor(color);
        theItem->setPen(pen);
        break;
    }
    case QGraphicsPolygonItem::Type:{
        QGraphicsPolygonItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
        QColor color = theItem->brush().color();
        color = QColorDialog::getColor(color,nullptr,"选择颜色");
        if(color == nullptr) return;
        theItem->setBrush(QBrush(color));
        break;
    }
    case QGraphicsTextItem::Type:{
        QGraphicsTextItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
        QColor color = theItem->defaultTextColor();
        color = QColorDialog::getColor(color,nullptr,"选择颜色");
        if(color == nullptr) return;
        theItem->setDefaultTextColor(color);
        break;
    }
    default:
        break;
    }

}

#include <QKeyEvent>
void MainWindow::on_keyPress(QKeyEvent *enent)
{
    int count = m_scene->selectedItems().count();
    if(count == 0) return;
    switch(enent->key()){
    case Qt::Key_Delete:{
        for(int i = 0;i<count;++i){
            QGraphicsItem *item = m_scene->selectedItems().at(0);
            m_scene->removeItem(item);
        }
        break;
    }
    case Qt::Key_Left:{
        for(int i = 0;i<count;++i){
            QGraphicsItem *item = m_scene->selectedItems().at(i);
            item->setX(item->x()-2);
        }
        break;
    }
    case Qt::Key_Right:{
        for(int i = 0;i<count;++i){
            QGraphicsItem *item = m_scene->selectedItems().at(i);
            item->setX(item->x()+2);
        }
        break;
    }
    case Qt::Key_Up:{
        for(int i = 0;i<count;++i){
            QGraphicsItem *item = m_scene->selectedItems().at(i);
            item->setY(item->y()-2);
        }
        break;
    }
    case Qt::Key_Down:{
        for(int i = 0;i<count;++i){
            QGraphicsItem *item = m_scene->selectedItems().at(i);
            item->setY(item->y()+2);
        }
        break;
    }
    default:
        break;
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actItem_Rect_triggered()
{
    QGraphicsRectItem *item = new QGraphicsRectItem(-50,-70,100,120);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setBrush(QBrush(Qt::green));
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"矩形");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);

}


void MainWindow::on_actItem_Ellipse_triggered()
{
    auto *item = new QGraphicsEllipseItem(-50,-50,60,80);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setBrush(QBrush(Qt::yellow));
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"椭圆");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Circle_triggered()
{
    auto *item = new QGraphicsEllipseItem(-50,-50,60,60);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setBrush(QBrush(Qt::gray));
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"圆");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Triangle_triggered()
{
    auto *item = new QGraphicsPolygonItem;
    QPolygon polygon;
    polygon.append(QPoint(-50,0));
    polygon.append(QPoint(50,0));
    polygon.append(QPoint(0,50));
    item->setPolygon(polygon);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setBrush(QBrush(Qt::red));
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"三角形");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);

}


void MainWindow::on_actItem_Line_triggered()
{
    auto *item = new QGraphicsLineItem(-100,-50,60,0);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(20);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setPen(pen);
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"线");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Polygon_triggered()
{
    auto *item = new QGraphicsPolygonItem;
    QPolygon polygon;
    polygon.append(QPoint(-50,0));
    polygon.append(QPoint(50,0));
    polygon.append(QPoint(70,40));
    polygon.append(QPoint(-70,40));
    item->setPolygon(polygon);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setBrush(QBrush(Qt::blue));
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setData(ItemDescription,"梯形");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);
}


#include <QInputDialog>
void MainWindow::on_actItem_Text_triggered()
{
    QString str = QInputDialog::getText(this,"输入对话框","请输入：");
    auto *item = new QGraphicsTextItem(str);
    QFont font;
    //font.setWidth(4);
    font.setPointSize(20);;
    item->setFont(font);
    item->setDefaultTextColor(Qt::green);
    item->setPos(-300+rand()%600,-100+rand()%200);
    item->setData(ItemId,++ItemNum);
    item->setFlags(QGraphicsItem::ItemIsFocusable|
                   QGraphicsItem::ItemIsSelectable|
                   QGraphicsItem::ItemIsMovable);
    item->setData(ItemDescription,"文本");
    m_scene->addItem(item);
    m_scene->clearSelection();
    item->setSelected(true);



}


void MainWindow::on_actZoomIn_triggered()
{
   int cnt = m_scene->selectedItems().count();
   if(cnt == 0) {
       ui->graphicsView->scale(1.1,1.1);
       return;
   }
   for(int i= 0;i<cnt;++i){
       QGraphicsItem *item = m_scene->selectedItems().at(i);
       item->setScale(0.1+item->scale());
   }
}


void MainWindow::on_actZoomOut_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0) {
        ui->graphicsView->scale(1.1,1.1);
    }
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setScale(0.1+item->scale());
    }
}


void MainWindow::on_actRestore_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0) {
        ui->graphicsView->resetTransform();
        return;
    }
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setScale(1);
    }
}


void MainWindow::on_actRotateLeft_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0)
        return;
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setRotation(item->rotation()-10);
    }
}


void MainWindow::on_actRotateRight_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0)
        return;
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setRotation(item->rotation()+10);
    }
}


void MainWindow::on_actEdit_Front_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0)
        return;
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setZValue(item->zValue()+1);
    }

}


void MainWindow::on_actEdit_Back_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0)
        return;
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(i);
        item->setZValue(item->zValue()-1);
    }
}


void MainWindow::on_actGroup_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt <= 1)
        return;
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    m_scene->addItem(group);
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(0);
        item->setSelected(false);
        group->addToGroup(item);

    }
    m_scene->clearSelection();
    group->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsMovable|
                    QGraphicsItem::ItemIsSelectable);

    group->setSelected(true);
}


void MainWindow::on_actGroupBreak_triggered()
{
    int cnt = m_scene->selectedItems().count();
    if(cnt == 0)
        return;
    QGraphicsItemGroup *group;
    int m = 0;
    for(int i= 0;i<cnt;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(m);
        if(item->type() == QGraphicsItemGroup::Type){
            group = qgraphicsitem_cast<QGraphicsItemGroup*>(item);
            m_scene->destroyItemGroup(group);
            item->setSelected(true);
        }else{
            m++;
        }
    }
//    m_scene->clearSelection();
//    group->setSelected(true);
}


void MainWindow::on_actEdit_Delete_triggered()
{
    int count = m_scene->selectedItems().count();
    if(count == 0) return;

    for(int i = 0;i<count;++i){
        QGraphicsItem *item = m_scene->selectedItems().at(0);
        m_scene->removeItem(item);
    }

}

