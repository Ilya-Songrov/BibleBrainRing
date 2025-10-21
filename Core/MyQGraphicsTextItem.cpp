#include "MyQGraphicsTextItem.h"
#include "QTextCursor"

MyQGraphicsTextItem::MyQGraphicsTextItem(MyQGraphicsTextItem::GroupMembers members, QGraphicsTextItem *parent)
                : QGraphicsTextItem(parent)
{
    member = members;

    boolFocusInOut = false;

    setTextInteractionFlags(Qt::TextEditorInteraction);
    setCursor(Qt::IBeamCursor);

}


QRectF MyQGraphicsTextItem::boundingRect() const
{
    switch (member)
    {
    case MyQGraphicsTextItem::LineFirstTeam:
    case MyQGraphicsTextItem::LineSecondTeam:
    case MyQGraphicsTextItem::LineFirstPoints:
    case MyQGraphicsTextItem::LineSecondPoints:
        return QRectF(0,0,textWidth(),QGraphicsTextItem::boundingRect().height());
        break;
    case MyQGraphicsTextItem::LineTitleText:
    case MyQGraphicsTextItem::LineQuestion:
    case MyQGraphicsTextItem::LineTimer:
        return QRectF(0,0,textWidth(),QGraphicsTextItem::boundingRect().height());
        break;
    default:
        return QGraphicsTextItem::boundingRect();
        break;
    }
}

QPainterPath MyQGraphicsTextItem::shape() const
{
    QPainterPath path; // метод скорее не нужен. Пусть пока будет
    path.addRect(boundingRect());
    return path;
}

void MyQGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->save();

    if(showHideRect)
    {
        if(boolFocusInOut == false)
        {
            painter->setPen(Qt::white); // рисуется 2 цвета, покуда фон может быть черным и белым и другим
            painter->drawRect(boundingRect());
            painter->setPen(Qt::black);
            painter->drawRect(boundingRect());
        }
    }
    painter->restore();

    QGraphicsTextItem::paint(painter, option, widget);
    painter->setPen(Qt::red);

}


void MyQGraphicsTextItem::focusInEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusInEvent(event);
    boolFocusInOut = true;
}

void MyQGraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusOutEvent(event);
    boolFocusInOut = false;
    boolMousePress = true;// ставит true чтобы при следующем нажатии сработало выделение.
    // вызов как-бы не пердназначался для этого и не связан с названием, но он хорошо подходит
    emit cursorPositionChangeD(); // когда итем теряет фокус, обнуляются QToolButton в slotRefresh_Tool()
}

void MyQGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mousePressEvent(event);
    Q_UNUSED(event);
    if(boolMousePress){// если первый раз нажали значит выделить текст.
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::Document);
        this->setTextCursor(cursor);
        boolMousePress = false;
    }
}

void MyQGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseReleaseEvent(event);
    emit cursorPositionChangeD(); // в ворде тоже реагирует на снятие а не на нажатие.
}

void MyQGraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace && (event->modifiers() == Qt::CTRL || event->modifiers() == Qt::ALT ||
                                             event->modifiers() == Qt::SHIFT))
        return; // пришлось сделать чтобы при пустом документе все не уходило в дефолт.
    QGraphicsTextItem::keyPressEvent(event);
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right ||
       event->key() == Qt::Key_Up ||  event->key() == Qt::Key_Down)
    {
        emit cursorPositionChangeD();
    }
}
