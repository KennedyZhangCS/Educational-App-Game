/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for Level 1 of game

#include "levelone.h"
#include "ui_levelone.h"

#include <QPixmap>
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QFont>

///@brief the constructor for level 1
LevelOne::LevelOne(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelOne), pestleHitCount(0), knifeSliceCount(0)
{
    ui->setupUi(this);

    QSize newSize(200, 200);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    // creating the background for all scenes in level four
    createBackground(ui->scene1Background, "l1s1.png");
    createBackground(ui->scene2Background, "l1s2.png");
    createBackground(ui->scene3Background, "l1s3.png");
    createBackground(ui->scene4Background, "l1s4.png");
    createBackground(ui->scene5Background, "l1s4.png");
    createBackground(ui->scene6Background, "levelDone.png");

    // scene 1

    ui->levelOneSteps->setCurrentIndex(0);

    ui->sceneOneContinue->hide();

    ui->stepLabel->setText(QString("First, drag the ginger to the pot"));

    formatText(ui->stepLabel, font);
    formatText(ui->infoBox, font);

    // Ginger item information
    makeEducationalText(
        ui->ginger,ui->infoBox,
        "<p>Ginger helps to neutralize the 'poultry smell' of chicken and add aroma and flavor.</p>"
        "Most Sichuan dishes use old ginger; old ginger has a strong aroma and better ability to remove odors."
        "China is one of the earliest regions where ginger was cultivated and widely used, and it later spread along early trade routes."
        "<p>Later in the app, you can see how Chicken Choila uses Boshe, which is low in fiber and higher yielding.</p>"
        );

    //green onion item information
    makeEducationalText(
        ui->onion, ui->infoBox,
        "<p>Kou Shui Ji tastes better with green onions in there because it provides a light and fresh herbal aroma that balances out the heavy or oily texture of the cuisine."
        "<p>Si Chuan province uses thin scallions/green onion instead of large scallions because of geographic reasons.</p>"
        "North provinces’ climate is better for growing large scallions, which has a thicker texture and more flavor compared to thin scallions.</p>"
        );

    //cooking wine item information
    makeEducationalText(
        ui->wine, ui->infoBox,
        "<p>Most Chinese cooking wine is a type of yellow wine, a fermented grain wine. </p>"
        "<p>They are usually made from glutinous rice, regular rice, water and fermentation starter containing yeast. Cooking wine is extremely versatile. It is used for de-smelling, seasoning, and enhancing aroma.</p>"
        );

    ui->pot->setScene(createScene("pot.png", QSize(400,300)));
    ui->ginger->setScene(createScene("ginger.png", newSize));
    ui->onion->setScene(createScene("green onion.png", QSize(150, 150)));
    ui->wine->setScene(createScene("cooking wine full.png", newSize));
    ui->chicken->setScene(createScene("raw pixel chicken.png", QSize(100, 100)));

    ui->pot->setStyleSheet("background: transparent");
    ui->pot->setFrameShape(QFrame::NoFrame);

    settingPositionAndTransparentOfitem(ui->ginger,400,-30,true);
    settingPositionAndTransparentOfitem(ui->wine,200,-30,true);
    settingPositionAndTransparentOfitem(ui->chicken,50,-80,true);
    settingPositionAndTransparentOfitem(ui->onion, 260 ,-30,true);

    connectFollowDrag(ui->ginger, 420, 335, 10, 10);
    connectFollowDrag(ui->wine, 420, 335, 10, 10);
    connectFollowDrag(ui->chicken, 420, 335, 10, 10);
    connectFollowDrag(ui->onion, 420, 335, 10, 10);

    connect(ui->ginger, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->ginger->hide();
            this->ui->stepLabel->setText(QString("Second, drag onions to the pot"));
        }
    });

    connect(ui->wine, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->wine->hide();
            ui->stepLabel->setText("Finally, drag the chicken to the pot");
        }
    });

    connect(ui->onion, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->onion->hide();
            ui->stepLabel->setText("Third, drag wine to the pot");
        }
    });

    connect(ui->chicken, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->chicken->hide();
            this->ui->sceneOneContinue->show();
            ui->stepLabel->setText("Nice job, now press the continue button!");
        }
    });

    connect(ui->sceneOneContinue, &QPushButton::clicked, this, [this](){
        ui->levelOneSteps->setCurrentIndex(1);
    });

    // scene 2

    ui->sceneTwoContinue->hide();

    formatText(ui->ovenInstruction, font);

    ui->pot_2->setScene(createScene("pot.png", QSize(200,200)));
    ui->oven->setScene(createScene("stove.png", QSize(200,200)));

    ui->pot_2->setStyleSheet("background: transparent");
    ui->oven->setStyleSheet("background: grey");

    ui->ovenSettingSlider->setValue(50);
    time = 10;
    timer.setInterval(100);
    ui->ovenMinCount->display(time);

    connect(&timer, &QTimer::timeout, this, [this](){
        time--;
        ui->ovenMinCount->display(time);
        if(time == 0){
            timer.stop();
            ui->ovenInstruction->setText(QString("Nice job, now press the continue button!"));
            ui->oven->setScene(createScene("stove.png", QSize(200,200)));
            ui->pot_2->setScene(createScene("pot.png", QSize(200, 200)));
            ui->sceneTwoContinue->show();
        }
    });

    // bool for timer to start once user has put the progress bar to zero
    connect(ui->ovenSettingSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == 0){
            timer.start();
            ui->ovenInstruction->setText(QString("Now keep pot on low heat for 10 minutes."));
            ui->ovenSettingSlider->setEnabled(false);
            ui->oven->setScene(createScene("stove on.png", QSize(200,200)));
            ui->pot_2->setScene(createScene("pot with water.png", QSize(200, 200)));
        }
    });

    connect(ui->sceneTwoContinue, &QPushButton::clicked, this, [this](){
        ui->levelOneSteps->setCurrentIndex(2);
    });

    // scene 3

    ui->sceneThreeContinue->hide();
    ui->stepLabel4->setText("Drag chicken to ice water bowl");

    formatText(ui->stepLabel4, font);

    ui->iceWaterBowl->setScene(createScene("ice water bowl.png", QSize(250,250)));
    ui->iceWaterBowl->setStyleSheet("background: transparent");
    ui->iceWaterBowl->setFrameShape(QFrame::NoFrame);
    ui->chicken_2->setScene(createScene("cooked chicken.png", QSize(200,200)));

    settingPositionAndTransparentOfitem(ui->chicken_2,352,-10,true);

    connectFollowDrag(ui->chicken_2, 420, 335, 10, 10);

    connect(ui->chicken_2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->iceWaterBowl, x, y)) {
            this->ui->chicken_2->hide();
            ui->iceWaterBowl->setScene(createScene("ice chicken.png", QSize(250,250)));
            ui->stepLabel4->setText("Press continue button");
            ui->sceneThreeContinue->show();}
    });

    connect(ui->sceneThreeContinue, &QPushButton::clicked, this, [this](){
        ui->levelOneSteps->setCurrentIndex(3);
    });

    // scene 4

    ui->sceneFourContinue->hide();

    formatText(ui->stepLabel2, font);
    formatText(ui->infoBox_2, font);

    // Garlic item information
    makeEducationalText(
        ui->garlic,ui->infoBox_2,
        "<p>Garlic was added to Kou Shui Ji for similar reasons; it adds aromatic base and boosts umami and savory depth. "
        "Si Chuan style dishes has Sichuan chili oil + garlic as a classic combination.</p>"
        );

    ui->mashedIngredients->hide();

    ui->ginger_2->setScene(createScene("ginger.png", newSize));
    ui->garlic->setScene(createScene("garlic.png", newSize));
    ui->chicken_3->setScene(createScene("cooked chicken.png", QSize(100,150)));
    ui->chicken_3->setFrameShape(QFrame::NoFrame);
    ui->knife->setScene(createScene("knife.png", QSize(200,200)));
    ui->mortar->setScene(createScene("mortar.png", QSize(150, 150)));
    ui->mortar->setFrameShape(QFrame::NoFrame);
    ui->pestle->setScene(createScene("pestle.png", newSize));
    ui->cuttingBoard->setScene(createScene("cutting board.png", QSize(200, 200)));
    ui->cuttingBoard->setFrameShape(QFrame::NoFrame);
    ui->mashedIngredients->setScene(createScene("ginger and garlic paste.png", QSize(150, 150)));
    ui->mashedIngredients->setFrameShape(QFrame::NoFrame);

    ui->chicken_3->setStyleSheet("background: transparent");
    ui->mortar->setStyleSheet("background: transparent");
    ui->cuttingBoard->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->ginger_2,325,200,true);
    settingPositionAndTransparentOfitem(ui->garlic,325,25,true);
    settingPositionAndTransparentOfitem(ui->pestle,-113,-102,true);
    settingPositionAndTransparentOfitem(ui->knife,-175,75,true);

    connectFollowDrag(ui->ginger_2, 420, 335, 10, 10);
    connectFollowDrag(ui->garlic, 420, 335, 10, 10);
    connectFollowDrag(ui->pestle, 420, 335, 10, 10);
    connectFollowDrag(ui->knife, 420, 335, 10, 10);

    connect(ui->garlic, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->garlic->hide();
            ui->stepLabel2->setText("Third, drag the pestle to the mortar back and forth 5 times");
        }
    });

    connect(ui->ginger_2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->ginger_2->hide();
            ui->stepLabel2->setText("Second, drag the garlic to the mortar");
        }
    });

    connect(ui->pestle, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            pestleHitCount++;
        }
        if(pestleHitCount == 5){
            this->ui->pestle->hide();
            this->ui->mortar->hide();
            this->ui->mashedIngredients->show();
            this->ui->mashedIngredients->setStyleSheet("background: transparent");
            ui->stepLabel2->setText("Finally, drag the knife to the chicken back and forth 5 times");
        }
    });

    connect(ui->knife, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->chicken, x, y)) {
            knifeSliceCount++;
        }
        if(knifeSliceCount == 5){
            this->ui->knife->hide();
            ui->chicken_3->setScene(createScene("sliced chicken.png", QSize(100,150)));
            ui->stepLabel2->setText("Nice job, press the continue button to move on to the next phase");
            this->ui->sceneFourContinue->show();
        }
    });

    connect(ui->sceneFourContinue, &QPushButton::clicked, this, [this](){
        ui->levelOneSteps->setCurrentIndex(4);
    });

    // scene 5

    ui->sceneFiveContinue->hide();

    ui->stepLabel3->setText("First, put chili oil in bowl");

    formatText(ui->stepLabel3, font);
    formatText(ui->infoBox_3, font);

    // Chili oil item
    makeEducationalText(
        ui->chiliOil,ui->infoBox_3,
        "<p>Chili oil is the MOST common used seasoning base in Sichuan.Without chili oil, the dish loses its signature Sichuan fragrance.</p>"
        "<p>Chili oil helps distribute heat evenly through the sauce without overwhelming the palate, which is why Sichuan dishes taste spicy but still enjoyable.</p>"
        );

    makeEducationalText(
        ui->sesame, ui->infoBox_3,
        "<p>Usually toasted sesame or sesame oil is added to the dish because sesame creates the perfect combination of seasoning with chili oil in Sichuan style dishes."
        "It also gives a visual and finish touch by adding contrast (golden on red chili oil) and signal nuttiness before you taste the dish. </p>"
        );

    ui->chiliOil->setScene(createScene("chili oil.png", newSize));
    ui->sesame->setScene(createScene("bowl of seasame.png", newSize));
    ui->mashedIng->setScene(createScene("ginger and garlic paste.png", newSize));
    ui->greenOnion->setScene(createScene("green onion.png", QSize(150, 150)));
    ui->cookedChicken->setScene(createScene("sliced chicken.png", newSize));
    ui->bowl->setScene(createScene("bowl.png", QSize(250,250)));
    ui->bowl->setFrameShape(QFrame::NoFrame);

    ui->bowl->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->chiliOil,305,250,true);
    settingPositionAndTransparentOfitem(ui->sesame,305,0,true);
    settingPositionAndTransparentOfitem(ui->mashedIng,350,125,true);
    settingPositionAndTransparentOfitem(ui->greenOnion,150,100,true);
    settingPositionAndTransparentOfitem(ui->cookedChicken,150,-10,true);

    connectFollowDrag(ui->chiliOil, 420, 335, 10, 10);
    connectFollowDrag(ui->sesame, 420, 335, 10, 10);
    connectFollowDrag(ui->mashedIng, 420, 335, 10, 10);
    connectFollowDrag(ui->greenOnion, 420, 335, 10, 10);
    connectFollowDrag(ui->cookedChicken, 420, 335, 10, 10);

    connect(ui->chiliOil, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->chiliOil->hide();
            ui->stepLabel3->setText("Second, put sesame in bowl");
        }
    });

    connect(ui->sesame, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->sesame->hide();
            ui->stepLabel3->setText("Third, put mashed garlic and ginger in bowl");
        }
    });

    connect(ui->mashedIng, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->mashedIng->hide();
            ui->stepLabel3->setText("Fourth, put green onion in bowl");
        }
    });

    connect(ui->greenOnion, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->greenOnion->hide();
            ui->bowl->setScene(createScene("bowl of combined chili oil.png", QSize(300,300)));
            ui->stepLabel3->setText("Finally, put chopped chicken in bowl");
        }
    });

    connect(ui->cookedChicken, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->cookedChicken->hide();
            ui->bowl->setScene(createScene("chicken and chili oil.png", QSize(300,300)));
            this->ui->sceneFiveContinue->show();
            ui->stepLabel3->setText("Press continue button to see results");
        }
    });

    connect(ui->sceneFiveContinue, &QPushButton::clicked, this, [this](){
        ui->levelOneSteps->setCurrentIndex(5);
    });

    // scene 6

    ui->kouShui->setScene(createScene("Kou Shui Ji.jpg", QSize(200, 200)));

    formatText(ui->winLabel, font);

    connect(ui->levelsMenuButton, &QPushButton::clicked, this, [this](){emit goBackToMenu();});
}

///@brief the destructor for level 1
LevelOne::~LevelOne()
{
    delete ui;
}

///@brief create image object
///@param filename: image to be used
///@param size of image
QGraphicsScene* LevelOne::createScene(QString fileName, QSize sceneSize){
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(fileName);
    QPixmap scaledPixmap = pixmap.scaled(sceneSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(scaledPixmap);
    item->setShapeMode(QGraphicsPixmapItem::MaskShape);
    scene->addItem(item);
    return scene;
}

///@brief checking if coords of mouse dragging QGraphicsView is in inside of target (QGraphicsView)
///@param *target: image (QGraphicsView) to be checked
///@param x: x coord of image being dragged (QGraphicsView)
///@param y: y coord of image being dragged (QGraphicsView)
bool LevelOne::isInside(QWidget *target, int x, int y) const
{
    // widget rect in parent coordinates
    QRect targetRect(target->pos(), target->size());
    return targetRect.contains(QPoint(x, y));
}

///@brief redraw image to have it follow the mouse as it drags
///@param *item: image (QGraphicsView) to be dragged
///@param offsetX: offset for x so the image follows right below mouse
///@param offsetY: offset for y so the image follows right below mouse
void LevelOne::connectFollowDrag(DragItem *item,int offsetX,int offsetY,int rectW,int rectH)
{
    connect(item, &DragItem::dragPosition, this,
            [item, offsetX, offsetY, rectW, rectH](int x, int y)
            {
                item->setSceneRect(-x + offsetX, -y + offsetY, rectW, rectH);
            });
}

///@brief This method is used to create all background images in the level
/// @param backgroundView: The Graphic View that will hold the background
/// @param backgroundFileName: The name of the file that holds the background image
void LevelOne::createBackground(QGraphicsView* backgroundView, QString backgroundFileName){
    backgroundView->setScene(createScene(backgroundFileName, QSize(800, 600)));
    backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

///@brief This method is used to format the text of each label in the level
/// @param label: The label that will be displayed
/// @param font: The formatting of the text
void LevelOne::formatText(QLabel* label, QFont font){
    label->setFont(font);
    label->setWordWrap(true);
    label->setStyleSheet("color: white;");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

///@brief create text for educational background for an ingredient
void LevelOne::makeEducationalText(DragItem *item, QLabel *label, const QString &info)
{
    item->setInfoText(info);
    connect(item, &DragItem::displayNewInfo,
            this, [label](const QString &text) {
                label->setText(text);
            });
}

///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
void LevelOne::settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent) {
    if(isTransparent) {
        item->setStyleSheet("background: transparent");
    }
    item->setSceneRect(x, y, 10, 10);
}
