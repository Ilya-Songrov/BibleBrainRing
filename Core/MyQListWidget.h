#ifndef MYQLISTWIDGET_H
#define MYQLISTWIDGET_H


#include <QListWidget>
#include <QUrl>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QPixmap>
#include <QDebug>


class MyQListWidget : public QListWidget
{// Потрібен для дропу.
    Q_OBJECT
public:
    explicit MyQListWidget(QWidget *parent = 0) : QListWidget(parent)
    {
        setAcceptDrops(true);
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE
    {
        if (event->mimeData()->hasUrls())
            event->acceptProposedAction();
    }
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE
    {
        if(event->isAccepted())
            event->acceptProposedAction();
    }

    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE
    {
        QString strPathDropPix = "";
        QString strPathDropMp3 = "";
        foreach (QUrl url, event->mimeData()->urls())
        {
            QString strSuffix = QFileInfo(url.toString().remove("file:///")).suffix();
            qDebug() << "function: " << __FUNCTION__ << " strSuffix: " << strSuffix << Qt::endl;

            if(strSuffix == "png" || strSuffix == "jpg")// Якщо картинки, зберігаємо адреси.
                strPathDropPix += url.toString().remove("file:///") + "\n";
            if(strSuffix == "mp3" || strSuffix == "wav")// Якщо музика, зберігаємо адреси.
                strPathDropMp3 += url.toString().remove("file:///") + "\n";
            qDebug() << "function: " << __FUNCTION__ << " strPathDropPix: " << strPathDropPix << Qt::endl;
            qDebug() << "function: " << __FUNCTION__ << " strPathDropMp3: " << strPathDropMp3 << Qt::endl;
        }
        if(!strPathDropPix.isEmpty()){
            // Якщо картинка - відправляємо сигнал.
            emit signalDropListWidgetPix(strPathDropPix, this->objectName());
        }
        if(!strPathDropMp3.isEmpty()){
            // Якщо музика - відправляємо сигнал.
            emit signalDropListWidgetMp3(strPathDropMp3, this->objectName());
        }
    }
signals:
    // Перший параметр адреси, другий - або картинки або музика.
    void signalDropListWidgetPix(QString strPathDrop, QString objectNameN);
    void signalDropListWidgetMp3(QString strPathDrop, QString objectNameN);
};

#endif // MYQLISTWIDGET_H
