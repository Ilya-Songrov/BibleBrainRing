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

#include "data/questions.h"

Questions::Questions()
{

}

void Questions::loadQuestions(const QStringList &questions)
{
    listQuestions.clear();
    for (const QString &strQuestion: questions) {
        QuestionNode q;
        q.question = strQuestion;
        listQuestions.append(q);
    }
}

void Questions::changeQuestionStatus(const QString &question, const QuestionStatus questionStatus)
{
    for (QuestionNode &q: listQuestions) {
        if (q.question == question) {
            q.status = questionStatus;
            return;
        }
    }
}
