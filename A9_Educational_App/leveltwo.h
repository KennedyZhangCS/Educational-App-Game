/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for Level 2 of game

#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "dragitem.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QFont>

namespace Ui {
class LevelTwo;
}

class LevelTwo : public QWidget
{
    Q_OBJECT

public:
    ///@brief the constructor for level 2
    explicit LevelTwo(QWidget *parent = nullptr);
    ///@brief deconstructor for level 2
    ~LevelTwo();

signals:
    ///@brief send signal to go back to level selection menu
    void goBackToMenu();

private:

    ///@brief This method is used to format the text of each label in the level
    /// @param label: The label that will be displayed
    /// @param font: The formatting of the text
    void formatText(QLabel* label, QFont font);

    ///@brief This method is used to create all background images in the level
    /// @param backgroundView: The Graphic View that will hold the background
    /// @param backgroundFileName: The name of the file that holds the background image
    void createBackground(QGraphicsView* backgroundView, QString backgroundFileName);

    ///@brief create image object
    ///@param filename: image to be used
    ///@param size of image
    QGraphicsScene* createScene(QString fileName, QSize sceneSize);

    ///@brief checking if coords of mouse dragging QGraphicsView is in inside of target (QGraphicsView)
    ///@param *target: image (QGraphicsView) to be checked
    ///@param x: x coord of image being dragged (QGraphicsView)
    ///@param y: y coord of image being dragged (QGraphicsView)
    bool isInside(QWidget *target, int x, int y) const;

    ///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
    void settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent);

    ///@brief redraw image to have it follow the mouse as it drags
    ///@param *item: image (QGraphicsView) to be dragged
    ///@param offsetX: offset for x so the image follows right below mouse
    ///@param offsetY: offset for y so the image follows right below mouse
    void connectFollowDrag(DragItem *item, int offsetX, int offsetY, int rectW, int rectH);

    //these are helper methods for adding educational text for your drag item, but when you call it you only need to call:
    //makeEducationalLabelFormat(ui->Name of your Qlabel in stack widget);
    //makeEducationalText(ui->Drag Item Name, name of your qlabel in stack widget, "your educational text");
    ///@brief create text for educational background for an ingredient
    void makeEducationalText(DragItem *item, QLabel *label, const QString &info);

    ///@brief format the label that has educational background
    void makeEducationalLabelFormat(QLabel* labelName);

    // all private varibles used for level three
    QTimer timer;
    QTimer timer2;
    Ui::LevelTwo *ui;
    int saltHitCount = 0;
    int pepperHitCount = 0;
    int chickenHitCount = 0;
    int eggHitCount = 0;
    bool chickenIsFlipped = false;
    int time;
    int time2;
    bool timeHitZero = false;
};

#endif // LEVELTWO_H
