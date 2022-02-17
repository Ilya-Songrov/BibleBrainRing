#pragma once

#include "dtoabstract.h"

struct DtoButtonPressedRq : public DtoAbstract
{
    QString guid        ;
    qint64  time        = 0;
};

