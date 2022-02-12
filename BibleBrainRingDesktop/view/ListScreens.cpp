#include "ListScreens.hpp"

ListScreens::ListScreens(QObject *parent)
    : QObject{parent}
{
}

void ListScreens::initScreens()
{
    setScreenPrototype(generateScreenPrototype());
    rectForApp = generateRectForApp();
    sizeForBoundingItemScreenWidget = generateSizeForBoundingItemScreenWidget();
    sizeForScreenWidget = getSizeForScreenWidget();
    appendScreens(QGuiApplication::screens());
}

void ListScreens::appendScreen(const AdditionalScreen& screen)
{
    emit preSetItems(1);
    list.append(screen);
    emit postSetItems();
}

void ListScreens::appendScreens(const QList<QScreen*>& listScreens)
{
    const auto* primaryScreen = QGuiApplication::primaryScreen();
    const QSize boundingSize(screenPrototype.widthReal, screenPrototype.heightReal);
    for (QScreen* screen: listScreens) {
        if (screen == primaryScreen) {
            continue;
        }
        const QRect rect = screen->geometry();
        AdditionalScreen additionalScreen;
        additionalScreen.xPos                 = rect.x();
        additionalScreen.yPos                 = rect.y();
        additionalScreen.widthReal            = rect.width();
        additionalScreen.heightReal           = rect.height();
        QSize size (additionalScreen.widthReal, additionalScreen.heightReal);
        size.scale(boundingSize, Qt::KeepAspectRatio);
        additionalScreen.widthVisual          = size.width();
        additionalScreen.heightVisual         = size.height();
        // TODO: finish me. if sizeForScreenWidget.width() > additionalScreen.widthVisual
        additionalScreen.scalePixelSize       = double(additionalScreen.widthVisual) / double(sizeForScreenWidget.width());
        appendScreen(additionalScreen);
    }
}

void ListScreens::removeTeam(const int index)
{
    if (index > -1 && list.size() > index) {
        emit preRemoveItems(index, index);
        list.removeAt(index);
        emit postRemoveItems();
    }
}

void ListScreens::clear()
{
    emit preResetModel();
    list.clear();
    emit postResetModel();
}

AdditionalScreen ListScreens::getScreen(const int index)
{
    if (index > -1 && list.size() > index) {
        return list.at(index);
    }
    return {};
}

AdditionalScreen ListScreens::getScreenPrototype()
{
    return screenPrototype;
}

QRect ListScreens::getRectForApp() const
{
    return rectForApp;
}

QSize ListScreens::getSizeForBoundingItemScreenWidget() const
{
    return sizeForBoundingItemScreenWidget;
}

QSize ListScreens::getSizeForScreenWidget() const
{
    QSize sizeScreenPrototype(screenPrototype.widthReal, screenPrototype.heightReal);
    sizeScreenPrototype.scale(sizeForBoundingItemScreenWidget, Qt::KeepAspectRatio);
    return sizeScreenPrototype;
}

QList<AdditionalScreen>& ListScreens::getList()
{
    return list;
}

int ListScreens::getListSize() const
{
    return list.size();
}

void ListScreens::setScreenPrototype(const AdditionalScreen& screen)
{
    screenPrototype = screen;
}

AdditionalScreen ListScreens::generateScreenPrototype()
{
    const QScreen* primaryScreen = QGuiApplication::primaryScreen();
    const QScreen* additionaScreen = nullptr;
    const auto lScreens = QGuiApplication::screens();
    for (QScreen* screen: lScreens) {
        if (screen == primaryScreen) {
            continue;
        }
        additionaScreen = screen;
        break;
    }
    const QRect rectScreen = additionaScreen ? additionaScreen->geometry() : primaryScreen->geometry();
    AdditionalScreen screenPrototype;
    screenPrototype.xPos                 = rectScreen.x();
    screenPrototype.yPos                 = rectScreen.y();
    screenPrototype.widthReal            = rectScreen.width();
    screenPrototype.heightReal           = rectScreen.height();
    screenPrototype.widthVisual          = rectScreen.width();
    screenPrototype.heightVisual         = rectScreen.height();
    screenPrototype.scalePixelSize       = 1.0;
    return screenPrototype;
}

QRect ListScreens::generateRectForApp()
{
    const QRect rectPrimaryScreen = QGuiApplication::primaryScreen()->geometry();
    QRect rectForAppNew = QRect(QPoint(), QSize(rectPrimaryScreen.width() / 1.6, rectPrimaryScreen.height() / 1.3));
    rectForAppNew.moveCenter(rectPrimaryScreen.center());
    return rectForAppNew;
}

QSize ListScreens::generateSizeForBoundingItemScreenWidget()
{
    const QRect rectForApp = getRectForApp();
    return QSize(rectForApp.width() / 2.3, rectForApp.height() / 2.3);
}
