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
    {                          //  я сам доробив, як міг)
        // зберігаємо шлях до файла при успішному завантаженні
        lastUsedQuestionFilePath = fileName;
        
        QStringList list;
        list = questionPreviewForm->decodedString().split(QLatin1Char('\n'),QString :: SkipEmptyParts);
        for (int var = 0; var < list.size(); ++var)
        {
            QString str = list[var];
            vecText_questions.push_back(str.remove("\r"));
        }
        
        // Сповіщаємо про успішне завантаження питань
        emit questionsLoaded(vecText_questions.size() > 0);
    }
}


void QuestionSearch::questionFastLoad(bool boolQuestionsonEsther)
{
    QString str;
    QString strFilter;
    if(!boolQuestionsonEsther)// Якщо звичайна ситуація, тобто в адміністративних налаштуваннях нічого не встановлено.
        str = QFileDialog::getOpenFileName(0,"Open questions", QDir::currentPath(),"*.txt", &strFilter);

//-------------------------------------------------------------------------------------------------------------
// Питання по Есфірі збережені в ресурсах. Завантажити можна через адміністративні налаштування.
    if(boolQuestionsonEsther)// Якщо в адміністративних налаштуваннях встановлено, ми входимо. Викличеться ця функція.
        str = ":/new/Other/FilesAndLogo/Questions-about-Esther-ANSI-Windows-1251.txt";
//-------------------------------------------------------------------------------------------------------------

    if (!str.isEmpty())
    {
        // зберігаємо шлях до файла тільки якщо це не ресурсний файл
        if (!boolQuestionsonEsther)
            lastUsedQuestionFilePath = str;

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
        
        // Сповіщаємо про успішне завантаження питань
        emit questionsLoaded(vecText_questions.size() > 0);

    }
}

QStringList QuestionSearch::search(QString strRequest)
{
   QStringList lstHTML_questions;//Список питань які відповідають пошуку.

   for (int var = 0; var < vecText_questions.size(); ++var)// Пошук.
   {
       // toLower() - переводимо все в нижній регістр, щоб пошук був незалежно від регістру.
       int purpose = vecText_questions[var].toLower().indexOf(strRequest.toLower(),0);
       if(purpose >= 0)
       {
           // Вставка в текст HTML тегів. Все для виділення жовтим кольором.
           QString strHTML = vecText_questions[var];
           // Спочатку вставляється закриваючий тег. Позиція + кількість букв в пошуковому слові, це куди вставляти.
           strHTML.insert(purpose + strRequest.size(),"</span>");
           strHTML.insert(purpose, "<span style=\"background: yellow\">");// Вставляється відкриваючий тег.
           lstHTML_questions.push_back(strHTML);
       }
   }

   return lstHTML_questions;
}

void QuestionSearch::slotTextChanged(const QString &)
{
    if(vecText_questions.size() == 0){
        QMessageBox::information(parentMain, "Title", "Завантажте питання.");
    }
}

void QuestionSearch::slotOnPushButton_Search_clicked()
{
    QStringList lstHTML_questions = search(ui->lineEdit_question->text());

    ui->comboBox_question->clear();
    if(lstHTML_questions.size() > 1 || lstHTML_questions.isEmpty())
    {//Якщо за запитом пошуку кілька варіантів або взагалі ніяких, тоді:
        ui->comboBox_question->addItem("");// Виводимо порожній рядок, і
        ui->comboBox_question->addItems(lstHTML_questions);
        ui->comboBox_question->showPopup();
    }
    if(lstHTML_questions.size() == 1)// Якщо варіант один
    {
        ui->comboBox_question->addItems(lstHTML_questions);// Він один поміщається в комбобокс і
        emit signalShowQuestion(lstHTML_questions[0]);// одразу виводимо це на екран.
    }
}

void QuestionSearch::autoLoadQuestions()
{
    // автоматичне завантаження питань з раніше збереженого файла
    if (!lastUsedQuestionFilePath.isEmpty() && QFile::exists(lastUsedQuestionFilePath))
    {
        vecText_questions.clear(); // очищуємо попередні питання
        
        QFile read_file(lastUsedQuestionFilePath);
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

            read_file.close();
            
            // Сповіщаємо про успішне завантаження питань
            emit questionsLoaded(vecText_questions.size() > 0);
            
            // Повідомляємо користувача про успішне завантаження
            QTimer::singleShot(0, this, [this]() {
                QMessageBox::information(parentMain, "Автозавантаження питань", 
                                        QString("Автоматично завантажено %1 питань з файла:\n%2")
                                        .arg(vecText_questions.size())
                                        .arg(QFileInfo(lastUsedQuestionFilePath).fileName()));
            });
        }
    }
    else
    {
        // Сповіщаємо що питання не завантажені
        emit questionsLoaded(false);
    }
}
