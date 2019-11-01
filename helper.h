#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

#include "ball.h"

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event);
    Ball** particule;

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    int ballsTabSize;
};

#endif
