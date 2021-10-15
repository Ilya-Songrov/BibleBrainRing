/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#pragma once

#include <QObject>

#include "biblebrainringserverlib/enums/global_enums.h"

class Questions
{
public:
    explicit Questions();

    void loadQuestions(const QStringList &questions);
    void changeQuestionStatus(const QString &question, const QuestionStatus questionStatus);


private:
    struct QuestionNode{
        QString question        ;
        QuestionStatus status   = UnusedQuestion;
    };

    QList<QuestionNode> listQuestions;
};

