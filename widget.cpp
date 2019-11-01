#include "widget.h"
#include "helper.h"
#include "ball.h"

#include <QPainter>
#include <QTimer>

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(600, 600);
}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event);
    painter.end();
}
