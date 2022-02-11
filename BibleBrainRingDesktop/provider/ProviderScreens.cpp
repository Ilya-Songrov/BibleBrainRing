#include "ProviderScreens.hpp"

ProviderScreens::ProviderScreens(QObject *parent)
    : QObject{parent}
{

}

QVariantList ProviderScreens::getInfoAdditionalScreens()
{
    auto sdf = ManagerScreens::getInfoAdditionalScreens();
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " sdf: " << sdf << Qt::endl;
    return sdf;

}

QSizeF ProviderScreens::getSizeForScreenWidget(const QSizeF boundingSize)
{
    return ManagerScreens::getSizeForScreenWidget(boundingSize);;
}
