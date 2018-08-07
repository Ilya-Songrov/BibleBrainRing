#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>


    void loadModules(QSplashScreen* psplash)
    {
        QTime time;
        time.start();

        float opacity = 0.01;
        for (int i = 0; i < 100; )
        {
            if (time.elapsed() > 40)
            {
            time.start();
            ++i;
            opacity = (float)opacity + 0.01;
            psplash->setWindowOpacity(opacity);
            }
        }
    }
// Доделать:
// -2. Во время как работает таймер, обнуление очков происходит при касании на название команды.
// -1. И хотелось бы, чтобы было после 10 секунд какой-то сигнал, мол время закончилось.
// 0. Желтый поиск. Тоесть в комбобоксе вопроса, выделять запрос желтым цветом. Наполовину готово.
// 1. Автоматическое обновление приложения.
// 2. Дроп картинок на сцену, которые устанавливаются на итем картинки (Item_LineTitlePixmap).
// 4. Можно сделать Cntrl+Z для всей сцены, или для всего приложения.
// 6. Доделать горячие клавиши с (&). И посмотреть чтоб они появлялись при запуске. Потому что сейчас, после
// запуска, горячие клавиши не подчеркиваются. Только после нажатия Alt появляются подчеркивания.
// 7. Баг - если увеличить шрифт заглавия очень много, так что скроется вопрос, тогда автоматический подбор шрифта
// будет работать не корректно, вернее будет рекурсия. В будущем можно исправить, подобная ситуация маловероятна.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen splash(QPixmap(":/new/Other/FilesAndLogo/Logo_temporarily.png"));
    splash.setWindowOpacity(0.01);
    MainWindow win;

    splash.show();
    loadModules(&splash);
    splash.finish(&win);

    win.setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,win.size(),
                                        qApp->desktop()->availableGeometry()));
//        win.move(560,105);  // после удалить

    // без ffShowPopupComboBox вначале, если выделить текст или highlighted() по комбо боксу, ничего не будет.
    // Однако если это закомментировать, то еще до появления приложения будет появляеться комбобокс.
    win.ffShowPopupComboBox();
    win.show();
    win.ffHidePopupComboBox();

    return a.exec();
}

