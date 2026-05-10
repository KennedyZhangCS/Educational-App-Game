/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief The main cpp file that implements the methods of drag item for images (QGraphicView) that need to be dragged

#include "dragitem.h"

#include <QGraphicsView>
#include <QPoint>
#include <QRectF>
#include <QMouseEvent>
#include <QTimer>

///@brief constructor of picture to be dragged
DragItem::DragItem(QWidget *parent)
    : QGraphicsView{parent}, latestDragYPos(0), latestDragXPos(0), dragIsGoingDown(false), dragIsGoingLeft(false), functionsEnabled(true), infoText("")
{}

///@brief override mouseEvent to handle clicking and dragging this object
void DragItem:: mouseMoveEvent(QMouseEvent *event){
    //emit signals that updates the x and y coordinate position of mouse
    QPointF localPos = event->pos();
    if(sceneIsClicked){
        int currentXPos = localPos.x();
        int currentYPos = localPos.y();
        if(functionsEnabled){
            if(currentYPos < latestDragYPos && dragIsGoingDown){
                emit sendLastDragDownPosition(currentXPos, currentYPos);
                dragIsGoingDown = false;
            }
            else if(currentYPos > latestDragYPos && !dragIsGoingDown){
                emit sendLastDragUpPosition(currentXPos, currentYPos);
                dragIsGoingDown = true;
            }

            if(currentXPos < latestDragXPos && dragIsGoingLeft){
                emit sendLastDragLeftPosition(currentXPos, currentYPos);
                dragIsGoingLeft = false;
            }
            else if(currentYPos > latestDragXPos && !dragIsGoingLeft){
                emit sendLastDragRightPosition(currentXPos, currentYPos);
                dragIsGoingLeft = true;
            }
            emit dragPosition(localPos.x(), currentYPos);
            latestDragYPos = currentYPos;
            latestDragXPos = currentXPos;
        }
    }
}

///@brief override mouseEvent to handle releasing this object
void DragItem::mouseReleaseEvent(QMouseEvent *event){
    //emit signals that provides the x and y coordinate of starting position when mouse is pressed
    QPointF localPos = event->pos();
    if(sceneIsClicked && functionsEnabled){
        emit releasePosition(localPos.x(), localPos.y());
        sceneIsClicked = false;
    }
}

///@brief override mouseEvent to handle pressing this object
void DragItem::mousePressEvent(QMouseEvent *event){
    QPointF localPos = this->mapToScene(event->pos());
    int xPos = localPos.x();
    int yPos = localPos.y();
    QRectF sceneRect = this->scene()->sceneRect();
    int lowerXBound = sceneRect.x();
    int lowerYBound = sceneRect.y();
    int higherXBound = lowerXBound + sceneRect.width();
    int higherYBound = lowerYBound + sceneRect.height();
    emit displayNewInfo(infoText);

    if(xPos >= lowerXBound && xPos <= higherXBound && yPos >= lowerYBound && yPos <= higherYBound){
        sceneIsClicked = true;
    }
}

///@brief enable this object to be dragged
void DragItem::setEnabled(bool isEnabled){
    functionsEnabled = isEnabled;
}

///@brief educational info for this object
void DragItem::setInfoText(const QString &text){
    infoText = text;
}

