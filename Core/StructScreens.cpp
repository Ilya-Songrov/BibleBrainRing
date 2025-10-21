#include "StructScreens.h"

void StructScreens::initializationDesktop()
{

    desktopWidget = QApplication::desktop();

    int intAllXmove = 0;

    for (int var = 0; var < desktopWidget->numScreens(); ++var)
    { // for для обхода всех экранов в системе. Чтоб для каждого отдельно подготовить QGraphicsView
        int intDesWidth = 0;
        int intDesHeight = 0;
        int intDesYmove = 0;
        if (var != desktopWidget->primaryScreen())
        { // если не основной экран в системе.
            intDesWidth = desktopWidget->screenGeometry(var).width();
            intDesHeight = desktopWidget->screenGeometry(var).height();
            intDesYmove = 0;
        }
        else
        {
            intDesWidth = desktopWidget->screenGeometry(var).width();
            intDesHeight = desktopWidget->screenGeometry(var).height();
            intDesYmove = 0;
    //            intDesWidth = 400; // после удалить
    //            intDesHeight = 300;
    //            intDesYmove = 0;
    //            intAllXmove = 359;
        }

            QGraphicsView *graphicsViewD = new QGraphicsView(parentWidget);
            graphicsViewD->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            graphicsViewD->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
            graphicsViewD->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            graphicsViewD->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            graphicsViewD->setMinimumSize(intDesWidth+6,intDesHeight+6);
            graphicsViewD->move(intAllXmove-3,intDesYmove-3); // чтобы скрыть края

            VecGraphicsViewDesktop.push_back(graphicsViewD);

    //            intDesWidth += 6,intDesHeight += 6; // чтобы скрыть края
            // Выщитывается во сколько увеличен экран относительно главной сцены, делением на ее размер.
            VecGraphicsViewScaleSize.push_back(QSizeF((qreal)intDesWidth / 400,
                                                      (qreal)intDesHeight / 300));

    //            intDesWidth -= 6,intDesHeight -= 6;
            QVector <int> vec;
            vec.push_back(intDesWidth+6);
            vec.push_back(intDesHeight+6);
            vec.push_back(intAllXmove-3);
            vec.push_back(intDesYmove-3);
            VecGraphicsViewReset.push_back(vec);

            intAllXmove += desktopWidget->screenGeometry(var).width();
        }
}
