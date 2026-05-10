/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for Level 4 of game

#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "dragitem.h"

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>

namespace Ui {
class LevelFour;
}

class LevelFour : public QWidget
{
    Q_OBJECT

public:
    ///@brief constructor for level 4
    explicit LevelFour(QWidget *parent = nullptr);
    ///@brief deconstructor for level 4
    ~LevelFour();

signals:
    ///@brief send signal to go back to level selection menu
    void goBackToMenu();

private:
    Ui::LevelFour *ui;

    /// @brief This method is used to create all background images in the level
    /// @param backgroundView: The Graphic View that will hold the background
    /// @param backgroundFileName: The name of the file that holds the background image
    void createBackground(QGraphicsView* backgroundView, QString backgroundFileName);

    ///@brief checking if coords of mouse dragging QGraphicsView is in inside of target (QGraphicsView)
    ///@param *target: image (QGraphicsView) to be checked
    ///@param x: x coord of image being dragged (QGraphicsView)
    ///@param y: y coord of image being dragged (QGraphicsView)
    bool isInside(QWidget *target, int x, int y) const;

    ///@brief redraw image to have it follow the mouse as it drags
    ///@param *item: image (QGraphicsView) to be dragged
    ///@param offsetX: offset for x so the image follows right below mouse
    ///@param offsetY: offset for y so the image follows right below mouse
    void connectFollowDrag(DragItem *item,int offsetX,int offsetY,int rectW,int rectH);

    ///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
    void settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent);

    ///@brief create image object
    ///@param filename: image to be used
    ///@param size of image
    QGraphicsScene* createScene(QString fileName, QSize sceneSize);

    //these are helper methods for adding educational text for your drag item, but when you call it you only need to call:
    //makeEducationalLabelFormat(ui->Name of your Qlabel in stack widget);
    //makeEducationalText(ui->Drag Item Name, name of your qlabel in stack widget, "your educational text");
    ///@brief create text for educational background for an ingredient
    void makeEducationalText(DragItem *item, QLabel *label, const QString &info);

    ///@brief This method is used to format the text of each label in the level
    /// @param label: The label that will be displayed
    /// @param font: The formatting of the text
    void formatText(QLabel* label, QFont font);

    // all private variables used in level four
    int pestleHitCount;
    int knifeSliceCount;
    int currentIngIndex;
    int time;
    int chickenCounter;
    bool chickenFlipIsFalling;
    bool chickenFlipReachedTop;
    QTimer timer;
    int peelCounter;
};

#endif // LEVELFOUR_H
