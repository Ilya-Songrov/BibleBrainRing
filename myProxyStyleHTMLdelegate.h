#ifndef HTMLDELEGATE_MYPROXYSTYLE_H
#define HTMLDELEGATE_MYPROXYSTYLE_H

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QProxyStyle>
#include <QComboBox>
#include <QDebug>
#include <QWidget>
#include <QAbstractItemView>
#include <QStyledItemDelegate>

class myProxyStyle : public QProxyStyle
{
  public:
    void drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal, bool enabled,
                      const QString &text, QPalette::ColorRole textRole = QPalette::NoRole) const
    {// Это работает только когда комбобокс не редактируемый.
        if(text.isEmpty() || text == "") return;

        QPen saved_pen;
        if(textRole != QPalette::NoRole)
            saved_pen = painter->pen();

            painter->setPen(QPen(pal.brush(textRole), saved_pen.widthF()));
            int margin = 3;
            painter->save();
            QTextDocument docSelf;
            painter->translate(rect.left() - margin, 0);
            docSelf.setHtml(text);
            docSelf.drawContents(painter, QRectF(rect.adjusted(-rect.left(), 0, -margin, 0)));
            painter->restore();

        if(textRole != QPalette::NoRole)
            painter->setPen(saved_pen);

        QProxyStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    }
};

class myStyledItemDelegate : public QStyledItemDelegate {
public:
    myStyledItemDelegate(QObject* pobj = 0) : QStyledItemDelegate(pobj)
    {
    }

    void paint(QPainter *pPainter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItemV4 optionS = option;
           initStyleOption(&optionS, index);

           pPainter->save();

           QTextDocument doc;
           doc.setHtml(optionS.text);

           optionS.text = "";
           optionS.widget->style()->drawControl(QStyle::CE_ItemViewItem, &optionS, pPainter);

           pPainter->translate(optionS.rect.left() - 3, optionS.rect.top() - 3);
           QRect clip(0, 0, optionS.rect.width(), optionS.rect.height() + 5);// + 5 чтоб снизу не обрезались буквы.
           doc.drawContents(pPainter, clip);

           pPainter->restore();

//        QStyledItemDelegate::paint(pPainter, option, index);
    }
};


#endif // HTMLDELEGATE_MYPROXYSTYLE_H
