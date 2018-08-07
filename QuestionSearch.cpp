#include "QuestionSearch.h"

QuestionSearch::QuestionSearch(Ui::MainWindow *uiMain, QWidget *parent) :
    ui(uiMain),
    parentMain(parent)
{
    questionPreviewForm = new QuestionPreviewForm;

    connect(ui->lineEdit_question, &QLineEdit::textChanged, this, &QuestionSearch::slotTextChanged);
    connect(ui->pushButton_Search, &QPushButton::clicked, this, &QuestionSearch::slotOnPushButton_Search_clicked);
}

QuestionSearch::~QuestionSearch()
{
    delete questionPreviewForm;
}


void QuestionSearch::showPreviewFormDecoder(QString currentPath)
{
    const QString fileName = QFileDialog::getOpenFileName(parentMain, QObject::tr("Open questions"),
                                                          currentPath,"*.txt ");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(parentMain, QObject::tr("Codecs"), QString("Cannot read file %1:\n%2")
                             .arg(QDir::toNativeSeparators(fileName),file.errorString()));
        return;
    }

    const QByteArray data = file.readAll();

    questionPreviewForm->setWindowTitle(QObject::tr("Choose Encoding for %1").arg(QFileInfo(fileName).fileName()));
    questionPreviewForm->setEncodedData(data);
    if (questionPreviewForm->exec())
    {                          //  я сам доделал, как мог)
        QStringList list;
        list = questionPreviewForm->decodedString().split(QLatin1Char('\n'),QString :: SkipEmptyParts);
        for (int var = 0; var < list.size(); ++var)
        {
            QString str = list[var];
            vecText_questions.push_back(str.remove("\r"));
        }
    }
}


void QuestionSearch::questionFastLoad(bool boolQuestionsonEsther)
{
    QString str;
    QString strFilter;
    if(!boolQuestionsonEsther)// Если обычная ситуация, тоесть в административных настройках ничего не установленно.
        str = QFileDialog::getOpenFileName(0,"Open questions", QDir::currentPath(),"*.txt", &strFilter);

//-------------------------------------------------------------------------------------------------------------
// Вопросы по Есфири сохранены в ресурсах. Загрузить можно через административные настройки.
    if(boolQuestionsonEsther)// Если в административных настройках установленно, мы входим. Вызовется эта функция.
        str = ":/new/Other/FilesAndLogo/Вопросы по Есфири  ANSI Windows1251.txt";
//-------------------------------------------------------------------------------------------------------------

    if (!str.isEmpty())
    {

        QFile read_file(str);
        QString text;

        if(read_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&read_file);

            do
            {
                text = stream.readLine();
                if(!text.isNull())
                    vecText_questions.push_back(text);
            } while (!text.isNull());

        }

        read_file.close();

    }
}

QStringList QuestionSearch::search(QString strRequest)
{
   QStringList lstHTML_questions;//Список вопросов которые соотвецтвуют поиску.

   for (int var = 0; var < vecText_questions.size(); ++var)// Поиск.
   {
       // toLower() - переводим все в нижний регистр, чтобы поиск был независимо от регистра.
       int purpose = vecText_questions[var].toLower().indexOf(strRequest.toLower(),0);
       if(purpose >= 0)
       {
           // Вставка в текс HTML тегов. Все для выделения желтым цветом.
           QString strHTML = vecText_questions[var];
           // Сначала вставляется закрывающий тег. Позиция + количество букв в поисковом слове, это куда вставлять.
           strHTML.insert(purpose + strRequest.size(),"</span>");
           strHTML.insert(purpose, "<span style=\"background: yellow\">");// Вставляется открывающий тег.
           lstHTML_questions.push_back(strHTML);
       }
   }

   return lstHTML_questions;
}

void QuestionSearch::slotTextChanged(const QString &)
{
    if(vecText_questions.size() == 0){
        QMessageBox::information(parentMain, "Title","Загрузите вопросы.");
    }
}

void QuestionSearch::slotOnPushButton_Search_clicked()
{
    QStringList lstHTML_questions = search(ui->lineEdit_question->text());

    ui->comboBox_question->clear();
    if(lstHTML_questions.size() > 1 || lstHTML_questions.isEmpty())
    {//Если по запросу поиска несколько вариантов или вовсе никаких, тогда:
        ui->comboBox_question->addItem("");// Выводим пустую строку, и
        ui->comboBox_question->addItems(lstHTML_questions);
        ui->comboBox_question->showPopup();
    }
    if(lstHTML_questions.size() == 1)// Если вариант один
    {
        ui->comboBox_question->addItems(lstHTML_questions);// Он один помещается в комбобокс и
        emit signalShowQuestion(lstHTML_questions[0]);// сразу выводим это на экран.
    }
}
