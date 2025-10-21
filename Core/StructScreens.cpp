#include "StructScreens.h"

void StructScreens::initializationDesktop()
{

    desktopWidget = QApplication::desktop();

    int intAllXmove = 0;

    for (int var = 0; var < desktopWidget->numScreens(); ++var)
    { // for для обходу всіх екранів в системі. Щоб для кожного окремо підготувати QGraphicsView
        int intDesWidth = 0;
        int intDesHeight = 0;
        int intDesYmove = 0;
        if (var != desktopWidget->primaryScreen())
        { // якщо не основний екран в системі.
            intDesWidth = desktopWidget->screenGeometry(var).width();
            intDesHeight = desktopWidget->screenGeometry(var).height();
            intDesYmove = 0;
        }
        else
        {
            intDesWidth = desktopWidget->screenGeometry(var).width();
            intDesHeight = desktopWidget->screenGeometry(var).height();
            intDesYmove = 0;
    //            intDesWidth = 400; // після видалити
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
            graphicsViewD->move(intAllXmove-3,intDesYmove-3); // щоб сховати краї

            VecGraphicsViewDesktop.push_back(graphicsViewD);

    //            intDesWidth += 6,intDesHeight += 6; // щоб сховати краї
            // Вирахується у скільки збільшений екран відносно головної сцени, діленням на її розмір.
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
