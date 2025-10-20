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


class myQListWidget : public QListWidget
{// Нужен для дропа.
    Q_OBJECT
public:
    explicit myQListWidget(QWidget *parent = 0) : QListWidget(parent)
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

            if(strSuffix == "png" || strSuffix == "jpg")// Если картинки, сохраняем адреса.
                strPathDropPix += url.toString().remove("file:///") + "\n";
            if(strSuffix == "mp3" || strSuffix == "wav")// Если музыка, сохраняем адреса.
                strPathDropMp3 += url.toString().remove("file:///") + "\n";
            qDebug() << "function: " << __FUNCTION__ << " strPathDropPix: " << strPathDropPix << Qt::endl;
            qDebug() << "function: " << __FUNCTION__ << " strPathDropMp3: " << strPathDropMp3 << Qt::endl;
        }
        if(!strPathDropPix.isEmpty()){
            // Если картинка - отправляем сигнал.
            emit signalDropListWidgetPix(strPathDropPix, this->objectName());
        }
        if(!strPathDropMp3.isEmpty()){
            // Если музыка - отправляем сигнал.
            emit signalDropListWidgetMp3(strPathDropMp3, this->objectName());
        }
    }
signals:
    // Первый параметр адреса, второй - или картинки или музыка.
    void signalDropListWidgetPix(QString strPathDrop, QString objectNameN);
    void signalDropListWidgetMp3(QString strPathDrop, QString objectNameN);
};

#endif // MYQLISTWIDGET_H
