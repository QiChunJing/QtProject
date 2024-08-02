#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QWidget>

class DrawWidget : public QWidget   // 绘图区
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *) override;  // 鼠标按下事件
    void mouseMoveEvent(QMouseEvent *) override;   // 鼠标移动事件
    void paintEvent(QPaintEvent *) override;       // 重绘事件
    void resizeEvent(QResizeEvent *) override;  // 重写尺寸变化事件

signals:

public slots:
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void clear();

private:
    QPixmap * pix;
    QPoint startPos;
    QPoint endPos;
    int style = Qt::PenStyle::SolidLine;
    int weight = 3;
    QColor color;

};

#endif // DRAWWIDGET_H
