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
    QPainterPath path; // метод швидше не потрібен. Нехай поки буде
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
            painter->setPen(Qt::white); // рисується 2 кольори, поки фон може бути чорним і білим і іншим
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
    boolMousePress = true;// ставить true щоб при наступному натисканні спрацювало виділення.
    // виклик як-би не передбачався для цього і не пов'язаний з назвою, але він добре підходить
    emit cursorPositionChangeD(); // коли айтем втрачає фокус, обнуляються QToolButton в slotRefresh_Tool()
}

void MyQGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mousePressEvent(event);
    Q_UNUSED(event);
    if(boolMousePress){// якщо перший раз натиснули значить виділити текст.
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::Document);
        this->setTextCursor(cursor);
        boolMousePress = false;
    }
}

void MyQGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseReleaseEvent(event);
    emit cursorPositionChangeD(); // в ворді теж реагує на зняття а не на натискання.
}

void MyQGraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace && (event->modifiers() == Qt::CTRL || event->modifiers() == Qt::ALT ||
                                             event->modifiers() == Qt::SHIFT))
        return; // довелося зробити щоб при порожньому документі все не йшло в дефолт.
    QGraphicsTextItem::keyPressEvent(event);
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right ||
       event->key() == Qt::Key_Up ||  event->key() == Qt::Key_Down)
    {
        emit cursorPositionChangeD();
    }
}
