#ifndef MY_QGRAPHICSTEXTITEM_H
#define MY_QGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QCursor>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>
#include <QStyle>
#include <QStyleOptionGraphicsItem>


class MyQGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum GroupMembers {LineTitleText = 0, LineFirstTeam, LineSecondTeam, LineFirstPoints,
                                            LineSecondPoints, LineQuestion, LineTimer};
     explicit MyQGraphicsTextItem(GroupMembers members, QGraphicsTextItem *parent = 0);

    GroupMembers member;
    bool boolFocusInOut;
    bool boolMousePress = true;// для того щоб натискаючи на айтем, текст в ньому виділявся.
    bool showHideRect = false;

    void setShow_HideRect(bool showHide = false){showHideRect = showHide; update();}
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

signals:
    void cursorPositionChangeD();

};

#endif // MY_QGRAPHICSTEXTITEM_H

