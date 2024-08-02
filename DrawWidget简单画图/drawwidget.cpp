#include "drawwidget.h"
#include <QtGui>
#include <QPen>

#include <QDebug>

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);  // 对窗体背景色的设置
    setPalette(QPalette(Qt::red));
    pix = new QPixmap(size());  // 此QPixmap对象用于准备随时接收绘制的内容
    qDebug() << this->size();
    pix->fill(Qt::white);  // 填充背景颜色为白色
    setMinimumSize(600, 400);  // 设置绘制区窗体的最小尺寸
}

// 重定义鼠标按下事件
void DrawWidget::mousePressEvent(QMouseEvent * e)
{
    // 在按下鼠标键时，记录当前的鼠标位置值
    startPos = e->pos();
    qDebug() << startPos;
}

// 重定义鼠标移动事件  完成向QPixmap对象中绘图的工作
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    // this->setMouseTracking(true);  // 指示窗体是否追踪鼠标，默认为false（不追踪）
    // QPainter * painter = new QPainter; // 新建一个用于绘图的对象
    QPainter * painter = new QPainter; // 新建一个用于绘图的对象
    QPen pen;  // 新建一个画笔对象
    pen.setStyle((Qt::PenStyle) style); // 设置画笔的风格
    pen.setWidth(weight);  // 设置画笔的线宽值
    pen.setColor(color);  // 设置画笔的颜色
    painter->begin(pix);  // begin() 函数用于指定绘图的目标
    painter->setPen(pen); // 将之前设置好属性的画笔应用到绘图操作中。
    // 绘制从startPos 到鼠标当前位置的直线
    painter->drawLine(startPos, e->pos());
    // qDebug() << e->pos();
    painter->end();
    startPos = e->pos(); // 更新鼠标的当前位置，为下次绘制做准备
    update(); // 调用 update 函数，触发界面的更新，以显示新绘制的内容
    delete painter;
    qDebug() << "释放成功";
}

// 重绘函数paintEvent()完成绘制区窗体的更新工作
void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    qDebug() << "paintEvent() called!";
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if (height() > pix->height() || width() > pix->width())
    {
        QPixmap * newPix = new QPixmap(size());
        qDebug() << size();
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);
        delete pix;
        pix = newPix;
    }
    QWidget::resizeEvent(event); // 完成其余的工作
    qDebug() << "resizeEvent() called!";
}

// setStyle()函数接收主窗口传来的线型风格参数
void DrawWidget::setStyle(int s)
{
    style = s;
}

// setWidth()函数接收主窗口传来的线宽参数
void DrawWidget::setWidth(int w)
{
    weight = w;

}

// setColor()函数接收主窗口传来的画笔颜色值
void DrawWidget::setColor(QColor c)
{
    color = c;
}

// clear()函数完成绘制区的清除工作
void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    delete pix;
    pix = clearPix;
    update();
}
