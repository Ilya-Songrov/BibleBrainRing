#ifndef STRUCTSCREENS_H
#define STRUCTSCREENS_H

#include "QVector"
#include "QGraphicsView"
#include "QDesktopWidget"
#include "QApplication"

struct StructScreens
{
public:
    QDesktopWidget *desktopWidget; // ссылка на QDesktopWidget
    QVector <QGraphicsView *> VecGraphicsViewDesktop; // созданные экраны
    QVector <QSizeF> VecGraphicsViewScaleSize; // созданные экраны
    QVector <QVector <int> > VecGraphicsViewReset; // экраны для VecGraphicsViewResetса)
    QWidget *parentWidget;

    bool showORhideScreen = false;

    void setParentWidget(QWidget *parentWid){ parentWidget = parentWid; }
    void initializationDesktop();
};


#endif // STRUCTSCREENS_H
