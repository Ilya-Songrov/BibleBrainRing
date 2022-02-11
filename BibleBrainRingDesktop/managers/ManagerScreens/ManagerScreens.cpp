#include "ManagerScreens.hpp"

ManagerScreens::ManagerScreens(QObject *parent)
    : QObject{parent}
{

}

QRect ManagerScreens::getRectPrimaryScreen()
{
    const QRect rectPrimaryScreen = QGuiApplication::primaryScreen()->geometry();
#ifdef QT_DEBUG
    QRect rect = QRect(QPoint(), QSize(4, 3) * 220);
    rect.moveCenter(rectPrimaryScreen.center());
#endif
    return rect;
}

QVariantList ManagerScreens::getInfoAdditionalScreens()
{
    const auto* primaryScreen = QGuiApplication::primaryScreen();
    const auto listScreens = QGuiApplication::screens();
    QVariantList variantListScreens;
    for (QScreen* screen: listScreens) {
        if (screen == primaryScreen) {
            continue;
        }
        variantListScreens.append(screen->geometry());
    }
    return variantListScreens;
}

QSizeF ManagerScreens::getSizeForScreenWidget(const QSizeF boundingSize)
{
    const QScreen* primaryScreen = QGuiApplication::primaryScreen();
    const QScreen* additionaScreen = nullptr;
    const auto listScreens = QGuiApplication::screens();
    for (QScreen* screen: listScreens) {
        if (screen == primaryScreen) {
            continue;
        }
        additionaScreen = screen;
        break;
    }
    const QRect rectScreen = additionaScreen ? additionaScreen->geometry() : primaryScreen->geometry();
    QSize sizeScreen = rectScreen.size();
    sizeScreen.scale(boundingSize.toSize(), Qt::KeepAspectRatio);
    return sizeScreen;
}
