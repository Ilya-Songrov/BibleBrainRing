#ifndef STRUCTSCREENS_H
#define STRUCTSCREENS_H

#include "QVector"
#include "QGraphicsView"
#include "QDesktopWidget"
#include "QApplication"

struct StructScreens
{
public:
    QDesktopWidget *desktopWidget; // посилання на QDesktopWidget
    QVector <QGraphicsView *> VecGraphicsViewDesktop; // створені екрани
    QVector <QSizeF> VecGraphicsViewScaleSize; // створені екрани
    QVector <QVector <int> > VecGraphicsViewReset; // екрани для скидання
    QWidget *parentWidget;

    bool showORhideScreen = false;

    void setParentWidget(QWidget *parentWid){ parentWidget = parentWid; }
    void initializationDesktop();
};


#endif // STRUCTSCREENS_H
