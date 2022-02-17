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

enum GameState
{
    NotStarted              = 0,
    QuestionAsked           ,
    AnswerReceived          ,
    Finished                ,
};

enum ServerMode
{
    Unknown                 = 0,
    Initialization          ,
    Idle                    ,
    AcceptsRegistrations    ,
    SelectingSparringTeams  ,
    RunningSparring         ,
    ShowingSparringResult   ,
    ShowingGameResult       ,
};

enum TeamStatus
{
    None                    = 0,
    NotValid                ,
    Registered              ,
    WaitingForTheNextRound  ,
    InBattle                ,
    Lost                    ,
    Banned                  ,
};

enum QuestionStatus
{
    UnusedQuestion          = 0,
    AnsweredQuestion        ,
    WithdrawnQuestion       ,
    IncorrectQuestion       ,
};

