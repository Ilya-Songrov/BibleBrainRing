#pragma once

#include "dtoabstract.h"

struct DtoTeamActivationForBattleServerRq : public DtoAbstract
{
    QString guid        ;
    bool isActive       = false;
};

