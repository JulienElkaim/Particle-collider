#include "glwidget.h"
#include "widget.h"
#include "window.h"

#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("Projet C/C++"));

    Widget *native = new Widget(&helper, this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, native, &Widget::animate);
    timer->start(60);
}
