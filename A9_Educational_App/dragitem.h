/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for images (QGraphicView) that need to be dragged

#ifndef DRAGITEM_H
#define DRAGITEM_H

#include <QWidget>
#include <QGraphicsView>

class DragItem : public QGraphicsView
{
    Q_OBJECT
public:
    ///@brief constructor of picture to be dragged
    explicit DragItem(QWidget *parent = nullptr);
    ///@brief override mouseEvent to handle clicking and dragging this object
    void mouseMoveEvent(QMouseEvent *event) override;
    ///@brief override mouseEvent to handle releasing this object
    void mouseReleaseEvent(QMouseEvent *event) override;
    ///@brief override mouseEvent to handle pressing this object
    void mousePressEvent(QMouseEvent *event) override;
    ///@brief enable this object to be dragged
    void setEnabled(bool isEnabled);
    ///@brief educational info for this object
    void setInfoText(const QString &text);

signals:
    ///@brief send position of mouse when this object is dragged
    void dragPosition(int x, int y);
    ///@brief send position of mouse when this object is released
    void releasePosition(int x, int y);
    ///@brief send position of mouse when this object is being dragged down
    void sendLastDragDownPosition(int x, int y);
    ///@brief send position of mouse when this object is being dragged up
    void sendLastDragUpPosition(int x, int y);
    ///@brief send position of mouse when this object is being dragged left
    void sendLastDragLeftPosition(int x, int y);
    ///@brief send position of mouse when this object is being dragged right
    void sendLastDragRightPosition(int x, int y);
    ///@brief send signal to show educational text
    void displayNewInfo(QString text);

private:
    // all private variables for a item that needs to be dragged
    int latestDragYPos;
    int latestDragXPos;
    bool dragIsGoingDown;
    bool dragIsGoingLeft;
    bool functionsEnabled;
    bool sceneIsClicked;
    bool infoDisplayed;
    QString infoText;
};

#endif // DRAGITEM_H
