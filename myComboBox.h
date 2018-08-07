#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QObject>
#include <QWheelEvent>
#include <QPixmap>
#include <QDebug>
#include <QApplication>
#include <QFontDatabase>
#include <QLineEdit>


class myComboBox : public QComboBox
{
    Q_OBJECT
public:
     explicit myComboBox(QWidget *parent = 0) : QComboBox(parent)
     {
         const QList<int> standardSizes = QFontDatabase::standardSizes();
         foreach (int size, standardSizes)
             addItem(QString::number(size));
         setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
                 //color(qrand() % 256, qrand() % 256, qrand() % 256)
         setEditable(true);
         setAutoCompletion(false); // без автодополнения
         setMaxCount(count());
     }

     bool boolPress = false;

     virtual void hidePopup()
     {
         QComboBox::hidePopup();
         // обработка сигнала прописана в QtCreator. После сигнала фокус пололучает ui->graphicsView
         emit signalComboBoxHidePopup();
     }
protected:
     void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE
     {
          boolPress = true;
          QComboBox::mousePressEvent(e);
     }
     void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE
     {
         boolPress = false;
         QComboBox::mouseReleaseEvent(e);
     }

signals:
    void signalComboBoxHidePopup();
};

#endif // MYCOMBOBOX_H
