#include "levelsmenu.h"
#include "ui_levelsmenu.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>


 ///@brief constructor of Levels Menu of the educational app
LevelsMenu::LevelsMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelsMenu)
{
    ui->setupUi(this);

    // set up kitchen utilities and locks
    QSize toolSize(500, 500);
    QGraphicsScene *scenePot = createScene("pot.png", toolSize);
    QGraphicsScene *sceneOven = createScene("oven closed.png", toolSize);
    QGraphicsScene *sceneFryer = createScene("air fryer.png", toolSize);
    QGraphicsScene *sceneGrill = createScene("grill.png", toolSize);
    QGraphicsScene *sceneChicken = createScene("raw pixel chicken.png", QSize(100, 100));
    QGraphicsScene *sceneLock1 = createScene("lock.png", toolSize);
    QGraphicsScene *sceneLock2 = createScene("lock.png", toolSize);
    QGraphicsScene *sceneLock3 = createScene("lock.png", toolSize);
    QGraphicsScene *sceneLock4 = createScene("lock.png", toolSize);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    ui->levelLabel->setFont(font);
    ui->levelLabel->setStyleSheet("color: white;");

    // set up background image
    ui->background->setScene(createScene("levels menu background.png", QSize(800, 600)));
    ui->background->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->background->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->pot->setScene(scenePot);
    ui->pot->scale(0.3, 0.25);
    ui->pot->setStyleSheet("background: transparent");
    ui->grill->setScene(sceneGrill);
    ui->grill->scale(0.25, 0.25);
    ui->grill->setStyleSheet("background: transparent");
    ui->oven->setScene(sceneOven);
    ui->oven->scale(0.4, 0.25);
    ui->oven->setStyleSheet("background: transparent");
    ui->fryer->setScene(sceneFryer);
    ui->fryer->scale(0.3, 0.25);
    ui->fryer->setStyleSheet("background: transparent");
    ui->chicken->setScene(sceneChicken);
    ui->chicken->setSceneRect(25, -100, 10, 10);
    ui->chicken->setStyleSheet("background: transparent");
    ui->lock->hide();
    ui->lock->setScene(sceneLock1);
    ui->lock->scale(0.1, 0.1);
    ui->lock->setStyleSheet("background: transparent");
    ui->lock_2->setScene(sceneLock2);
    ui->lock_2->scale(0.1, 0.1);
    ui->lock_2->setStyleSheet("background: transparent");
    ui->lock_3->setScene(sceneLock3);
    ui->lock_3->scale(0.1, 0.1);
    ui->lock_3->setStyleSheet("background: transparent");
    ui->lock_4->setScene(sceneLock4);
    ui->lock_4->scale(0.1, 0.1);
    ui->lock_4->setStyleSheet("background: transparent");
    ui->levelLabel->setText("Drag the chicken to: " + listOfKitchenAppliances[levelNum]);

    connect(ui->chicken, &DragItem::dragPosition, this, [this](int x, int y){ui->chicken->setSceneRect(-x + 420, -y + 335, 10, 10);});
    connect(ui->chicken, &DragItem::releasePosition, this, &LevelsMenu::levelSelected);
}

 ///@brief destructor of Levels Menu of the educational app
LevelsMenu::~LevelsMenu()
{
    delete ui;
}

///@brief slot that receives and handles the signal when level is picked
void LevelsMenu::levelSelected(int x, int y){
    // level 1
    if(x >= 22 && x <= 207 && y >= 101 && y <= 230){
        if(!potLocked){
            ui->chicken->setSceneRect(0, 0, 10, 10);
            levelNum++;
            airFryerLocked = false;
            potLocked = true;
            ui->lock_2->hide();
            ui->levelLabel->setText("Drag the chicken to: " + listOfKitchenAppliances[levelNum]);
            emit openLevelOne();
        }
    }
    // level 2
    else if(x >= 212 && x <= 397 && y >= 101 && y <= 230){
        if(!airFryerLocked){
            ui->chicken->setSceneRect(0, 0, 10, 10);
            levelNum++;
            ovenLocked = false;
            ui->lock_3->hide();
            ui->levelLabel->setText("Drag the chicken to: " + listOfKitchenAppliances[levelNum]);
            emit openLevelTwo();
        }
    }
    // level 3
    else if(x >= 403 && x <= 588 && y >= 101 && y <= 230){
        if(!ovenLocked){
            levelNum++;
            grillLocked = false;
            ui->lock_4->hide();
            ui->levelLabel->setText("Drag the chicken to: " + listOfKitchenAppliances[levelNum]);
            emit openLevelThree();
        }
    }
    // level 4
    else if(x >= 594 && x <= 779 && y >= 101 && y <= 230){
        if(!grillLocked){
            levelNum++;
            emit openLevelFour();
        }
    }
}

///@brief create image object
///@param filename: image to be used
///@param size of image
QGraphicsScene* LevelsMenu::createScene(QString fileName, QSize sceneSize){
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(fileName);
    QPixmap scaledPixmap= pixmap.scaled(sceneSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(scaledPixmap);
    item->setShapeMode(QGraphicsPixmapItem::MaskShape);
    scene->addItem(item);
    return scene;
}
