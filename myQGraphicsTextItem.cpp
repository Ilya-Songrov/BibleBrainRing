#include "myQGraphicsTextItem.h"
#include "QTextCursor"

myQGraphicsTextItem::myQGraphicsTextItem(myQGraphicsTextItem::GroupMembers members, QGraphicsTextItem *parent)
                : QGraphicsTextItem(parent)
{
    member = members;

    boolFocusInOut = false;

    setTextInteractionFlags(Qt::TextEditorInteraction);
    setCursor(Qt::IBeamCursor);

}


QRectF myQGraphicsTextItem::boundingRect() const
{
    switch (member)
    {
    case myQGraphicsTextItem::LineFirstTeam:
    case myQGraphicsTextItem::LineSecondTeam:
    case myQGraphicsTextItem::LineFirstPoints:
    case myQGraphicsTextItem::LineSecondPoints:
        return QRectF(0,0,textWidth(),QGraphicsTextItem::boundingRect().height());
        break;
    case myQGraphicsTextItem::LineTitleText:
    case myQGraphicsTextItem::LineQuestion:
    case myQGraphicsTextItem::LineTimer:
        return QRectF(0,0,textWidth(),QGraphicsTextItem::boundingRect().height());
        break;
    default:
        return QGraphicsTextItem::boundingRect();
        break;
    }
}

QPainterPath myQGraphicsTextItem::shape() const
{
    QPainterPath path; // метод скорее не нужен. Пусть пока будет
    path.addRect(boundingRect());
    return path;
}

void myQGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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


void myQGraphicsTextItem::focusInEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusInEvent(event);
    boolFocusInOut = true;
}

void myQGraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusOutEvent(event);
    boolFocusInOut = false;
    boolMousePress = true;// ставит true чтобы при следующем нажатии сработало выделение.
    // вызов как-бы не пердназначался для этого и не связан с названием, но он хорошо подходит
    emit cursorPositionChangeD(); // когда итем теряет фокус, обнуляются QToolButton в slotRefresh_Tool()
}

void myQGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void myQGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseReleaseEvent(event);
    emit cursorPositionChangeD(); // в ворде тоже реагирует на снятие а не на нажатие.
}

void myQGraphicsTextItem::keyPressEvent(QKeyEvent *event)
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
