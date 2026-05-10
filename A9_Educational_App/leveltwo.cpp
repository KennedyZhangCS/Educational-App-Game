/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for Level 2 of game

#include "leveltwo.h"
#include "ui_leveltwo.h"

#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QFont>

///@brief the constructor for level 2
LevelTwo::LevelTwo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelTwo)
{
    ui->setupUi(this);

    QSize newSize(100, 100);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    // creating the background for all scenes in level two
    createBackground(ui->scene1Background, "l2s1.png");
    createBackground(ui->scene2Background, "l2s2.png");
    createBackground(ui->scene3Background, "l2s3.png");
    createBackground(ui->scene4Background, "l2s4.png");
    createBackground(ui->scene5Background, "l2s4.png");
    createBackground(ui->scene6Background, "levelDone.png");

    // scene 1

    ui->levelTwoSteps->setCurrentIndex(0);

    ui->sceneOneContinue->hide();

    ui->stepLabel->setText("First, drag the pepper to the chicken back and forth 3 times");

    formatText(ui->stepLabel, font);
    formatText(ui->infoBox, font);

    // Salt and pepper item information
    makeEducationalText(
        ui->pepper,ui->infoBox,
        "<p>Fried food in Japan such as chicken katsu doesn’t have as much seasoning or spices in comparison to many of the other dishes. Which is due to Japan’s belief in relying on natural flavors and flavors coming from their sauces such as katsu sauce.</p>"
        );

    ui->chicken->setScene(createScene("raw pixel chicken.png", newSize));
    ui->salt->setScene(createScene("salt.png", newSize));
    ui->pepper->setScene(createScene("ground pepper.png", newSize));

    ui->chicken->setFrameShape(QFrame::NoFrame);
    ui->chicken->setStyleSheet("background: transparent");
    ui->chicken->setSceneRect(100, 0, 10, 10);

    settingPositionAndTransparentOfitem(ui->salt, 225, 81, true);
    settingPositionAndTransparentOfitem(ui->pepper, 327, 81, true);

    connectFollowDrag(ui->salt, 420, 335, 10, 10);
    connectFollowDrag(ui->pepper, 420, 335, 10, 10);

    // connections for items being released on chicken
    connect(ui->pepper, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->chicken, x, y)) {
            pepperHitCount++;
            ui->pepper->setStyleSheet("background: transparent");
            ui->pepper->setSceneRect(327, 81, 10, 10);
        }
        if(pepperHitCount == 3){
            this->ui->pepper->hide();
            this->ui->stepLabel->setText("Second, drag the salt to the chicken back and forth 3 times");
        }
    });

    connect(ui->salt, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->chicken, x, y)) {
            saltHitCount++;
            ui->salt->setStyleSheet("background: transparent");
            ui->salt->setSceneRect(225, 81, 10, 10);
        }
        if(saltHitCount == 3){
            this->ui->salt->hide();
            this->ui->sceneOneContinue->show();
            this->ui->stepLabel->setText("Nice job! Now press continue button.");
        }
    });

    // connection for moving to next phase when button is pushed
    connect(ui->sceneOneContinue, &QPushButton::clicked, this, [this](){
        ui->levelTwoSteps->setCurrentIndex(1);
    });

    // scene 2

    ui->sceneTwoContinue->hide();

    ui->stepLabel_2->setText("Drag the seasoned chicken to the bowl of flour");

    formatText(ui->stepLabel_2, font);
    formatText(ui->infoBox_2, font);

    // Adding flour item information
    makeEducationalText(
        ui->chicken_2,ui->infoBox_2,
        "<p>This is the first step in a process called the “glue effect” where the breading (Panko) is \"glued\" to chicken. This process is majorly rooted in Europe, specifically Scotland. </p>"
        );

    ui->flipButton->hide();

    ui->chicken_2->setScene(createScene("raw pixel chicken.png", newSize));
    ui->flour->setScene(createScene("flour.png", QSize(150, 200)));

    ui->flour->setStyleSheet("background: transparent");
    ui->flour->setFrameShape(QFrame::NoFrame);

    settingPositionAndTransparentOfitem(ui->chicken_2, 240, -70, true);

    // dragging helper method
    connectFollowDrag(ui->chicken_2, 420, 335, 10, 10);

    // connection for chicken being released on flour
    connect(ui->chicken_2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->flour, x, y)) {
            chickenHitCount++;
            if(chickenHitCount == 1)
                this->ui->flipButton->show();
            this->ui->stepLabel->setText("Press the flip button to flip the chicken");
        }
        if(chickenHitCount >= 2 && chickenIsFlipped){
            this->ui->chicken_2->hide();
            this->ui->sceneTwoContinue->show();
            this->ui->stepLabel->setText("Nice job, press continue!");
        }
    });

    // connection for pressing button to flip chicken
    connect(ui->flipButton, &QPushButton::clicked, this, [this, newSize](){
        this->ui->chicken_2->setScene(createScene("raw pixel chicken - Copy.png", newSize));
        this->ui->chicken_2->setSceneRect(240, -70, 10, 10);
        this->ui->flipButton->hide();
        this->ui->stepLabel->setText("Drag the flipped chicken to the flour one more time");
        chickenIsFlipped = true;
    });

    // connection for moving to next phase when button is pushed
    connect(ui->sceneTwoContinue, &QPushButton::clicked, this, [this](){
        ui->levelTwoSteps->setCurrentIndex(2);
    });

    // scene 3

    ui->sceneThreeContinue->hide();

    ui->stepLabel_3->setText("First, drag the egg to the table back and fourth three times");

    formatText(ui->stepLabel_3, font);
    formatText(ui->infoBox_3, font);

    // Adding floured chicken to bowl of eggs information
    makeEducationalText(
        ui->flouredChicken,ui->infoBox_3,
        "<p>This is the second step in the processes using the \"glue effect\" where you put the floured chicken in eggs<p>"
        );

    ui->flipButton_2->hide();
    ui->whisk->hide();
    ui->flouredChicken->hide();

    ui->egg->setScene(createScene("egg.png", newSize));
    ui->whisk->setScene(createScene("whisk.png", newSize));
    ui->bowl->setScene(createScene("table top.png", QSize(200, 200)));
    ui->bowl->setFrameShape(QFrame::NoFrame);
    ui->flouredChicken->setScene(createScene("floured chicken.png", newSize));

    // reset number of times chicken flipped and dragged onto item
    chickenIsFlipped = false;
    chickenHitCount = 0;

    // timer
    time = 15;

    ui->bowl->setStyleSheet("background: transparent");
    ui->whisk->setStyleSheet("background: transparent");
    ui->whisk->setSceneRect(192, 132, 10, 10);
    ui->flouredChicken->setStyleSheet("background: transparent");
    ui->flouredChicken->setSceneRect(226, -78, 10, 10);

    settingPositionAndTransparentOfitem(ui->egg, -257, -78, true);

    // dragging helper method
    connectFollowDrag(ui->egg, 420, 335, 10, 10);
    connectFollowDrag(ui->whisk, 420, 335, 10, 10);
    connectFollowDrag(ui->flouredChicken, 420, 335, 10, 10);

    connect(&timer, &QTimer::timeout, this, [this](){
        time--;
        if(time == 0){
            timer.stop();
            timeHitZero = true;
            chickenHitCount = 0;
            chickenIsFlipped = false;
            ui->bowl->setScene(createScene("bowl with mixed eggs.png", QSize(150, 200)));
            ui->bowl->setStyleSheet("background: transparent");
            ui->whisk->hide();
            ui->flouredChicken->show();
            ui->stepLabel_3->setText("Fourth, drag the floured chicken into the egg bowl");
        }
    });

    // connection for egg being released on table
    connect(ui->egg, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            eggHitCount++;
            ui->egg->setStyleSheet("background: transparent");
            ui->egg->setSceneRect(-257, -78, 10, 10);
        }
        if(eggHitCount == 3){
            ui->bowl->setScene(createScene("bowl.png", QSize(150, 200)));
            ui->bowl->setStyleSheet("background: transparent");
            ui->stepLabel_3->setText("Second, drag the egg to the bowl");
        }

        if(eggHitCount == 4){
            ui->bowl->setScene(createScene("bowl with eggs.png", QSize(150, 200)));
            ui->egg->hide();
            ui->whisk->show();
            ui->stepLabel_3->setText("Third, drag the whisk back and fourth over the bowl until the image changes");
            ui->bowl->setStyleSheet("background: transparent");
        }
    });

    // connection for whisk mixing eggs
    connect(ui->whisk, &DragItem::dragPosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            if(!timer.isActive() && !timeHitZero)
                timer.start(100);
        } else {
            if(timer.isActive())
                timer.stop();
        }
    });

    // connection for floured chicken being released in egg bowl
    connect(ui->flouredChicken, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            chickenHitCount++;
            this->ui->flipButton_2->show();
            this->ui->stepLabel->setText("Press the flip button to flip the chicken");
        }
        if(chickenHitCount >= 2 && chickenIsFlipped){
            this->ui->flouredChicken->hide();
            this->ui->flipButton_2->hide();
            this->ui->sceneThreeContinue->show();
            this->ui->stepLabel_3->setText("Nice job, press continue!");
        }
    });

    // connection for pressing button to flip chicken
    connect(ui->flipButton_2, &QPushButton::clicked, this, [this, newSize](){
        this->ui->flouredChicken->setScene(createScene("floured chicken copy.png", newSize));
        this->ui->flouredChicken->setSceneRect(226, -78, 10, 10);
        this->ui->flipButton_2->hide();
        this->ui->stepLabel->setText("Drag the flipped chicken to the egg bowl one more time");
        chickenIsFlipped = true;
    });

    // connection for moving to next phase when button is pushed
    connect(ui->sceneThreeContinue, &QPushButton::clicked, this, [this](){
        this->ui->levelTwoSteps->setCurrentIndex(3);
    });

    // scene 4

    ui->sceneFourContinue->hide();

    ui->stepLabel_4->setText("Drag the chicken to the bowl of panko");

    formatText(ui->stepLabel_4, font);
    formatText(ui->infoBox_4, font);

    // Adding flour item information
    makeEducationalText(
        ui->chicken_3,ui->infoBox_4,
        "<p> Finally, in the \"glue effect\" process, we use the flour and eggs on the chicken to get the Panko to stick to the chicken<p>"
        );

    ui->chicken_3->setScene(createScene("chicken with egg.png", newSize));
    ui->bowlOfPanko->setScene(createScene("panko.png", QSize(150, 200)));

    ui->bowlOfPanko->setStyleSheet("background: transparent");
    ui->bowlOfPanko->setFrameShape(QFrame::NoFrame);

    settingPositionAndTransparentOfitem(ui->chicken_3, 259, -72, true);

    // dragging helper method
    connectFollowDrag(ui->chicken_3, 420, 335, 10, 10);

    // connections for chicken being released into bowl of panko
    connect(ui->chicken_3, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowlOfPanko, x, y)) {
            this->ui->chicken_3->hide();
            this->ui->sceneFourContinue->show();
            this->ui->stepLabel->setText("Nice job, press continue!");
        }
    });

    // connection for moving to next phase when button is pushed
    connect(ui->sceneFourContinue, &QPushButton::clicked, this, [this](){
        this->ui->levelTwoSteps->setCurrentIndex(4);
    });

    // scene 5

    ui->sceneFiveContinue->hide();

    ui->fryerInstruction->setText(QString("Set air fryer to 375 degrees Fahrenheit"));
    // Air fryer info
    ui->infoBox_5->setText("<p>Frying has origins from Portugal and was originally adopted by Japan through being adopted by Japanese monks in "
                           "the 16th century and was later enhanced during WWII. Japanese fried foods at that point were seen as luxurious foods "
                           "but are now internally enjoyed.<p>");

    formatText(ui->fryerInstruction, font);
    formatText(ui->infoBox_5, font);

    ui->fryer->setScene(createScene("air fryer.png", QSize(175,200)));
    ui->fryer->setStyleSheet("background: transparent");
    ui->fryer->setFrameShape(QFrame::NoFrame);

    ui->fryerSlider->setRange(0, 375);
    ui->fryerSlider->setValue(0);

    // timer
    time2 = 4;
    timer2.setInterval(100);
    ui->fryerTime->display(time2);

    connect(&timer2, &QTimer::timeout, this, [this](){
        time2--;
        ui->fryerTime->display(time2);
        if(time2 == 0){
            timer2.stop();
            ui->fryerInstruction->setText(QString("Nice job, now press continue to see the results!"));
            ui->sceneFiveContinue->show();
        }
    });

    // bool for timer to start once user drags slider to 375
    connect(ui->fryerSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == 375){
            timer2.start();
            ui->fryerInstruction->setText(QString("Now keep fryer at 375 degrees Fahrenheit for four minutes"));
            ui->fryerSlider->setEnabled(false);
        }
    });

    // connection for moving to next phase when button is pushed
    connect(ui->sceneFiveContinue, &QPushButton::clicked, this, [this](){
        ui->levelTwoSteps->setCurrentIndex(5);
    });

    // scene 6

    formatText(ui->label_2, font);

    // Adding flour item information
    formatText(ui->infoBox_6, font);

    ui->infoBox_6->setText("<p>As mentioned before, in Japan, much of the flavoring for their fried food actually depends on their sauce. "
                           "As expected, the sauce that is used for chicken katsu is katsu sauce. Which is made up of worcestershire sauce, "
                           "ketchup, and sugar. This sauce was heavily influenced by Indian curries that were introduced to Japan by the "
                           "British. Later, it was personalized to have have a tangy flavor. <p>");

    // show final product
    ui->chickenKatsu->setScene(createScene("chicken katsu.jpg", QSize(300, 300)));

    ui->chickenKatsu->setStyleSheet("background: transparent");
    ui->chickenKatsu->setSceneRect(150, 75, 10, 10);
    ui->chickenKatsu->setFrameShape(QFrame::NoFrame);

    // connection for moving back to levels menu when button is clicked
    connect(ui->levelsMenuButton, &QPushButton::clicked, this, [this](){emit goBackToMenu();});
}

 ///@brief deconstructor for level 2
LevelTwo::~LevelTwo()
{
    delete ui;
}

///@brief create image object
///@param filename: image to be used
///@param size of image
QGraphicsScene* LevelTwo::createScene(QString fileName, QSize sceneSize){
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
bool LevelTwo::isInside(QWidget *target, int x, int y) const
{
    // widget rect in parent coordinates
    QRect targetRect(target->pos(), target->size());
    return targetRect.contains(QPoint(x, y));
}

///@brief redraw image to have it follow the mouse as it drags
///@param *item: image (QGraphicsView) to be dragged
///@param offsetX: offset for x so the image follows right below mouse
///@param offsetY: offset for y so the image follows right below mouse
void LevelTwo::connectFollowDrag(DragItem *item,int offsetX,int offsetY,int rectW,int rectH)
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
void LevelTwo::createBackground(QGraphicsView* backgroundView, QString backgroundFileName){
    backgroundView->setScene(createScene(backgroundFileName, QSize(800, 600)));
    backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

///@brief This method is used to format the text of each label in the level
/// @param label: The label that will be displayed
/// @param font: The formatting of the text
void LevelTwo::formatText(QLabel* label, QFont font){
    label->setFont(font);
    label->setWordWrap(true);
    label->setStyleSheet("color: white;");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

///@brief create text for educational background for an ingredient
void LevelTwo::makeEducationalText(DragItem *item, QLabel *label, const QString &info)
{
    item->setInfoText(info);
    connect(item, &DragItem::displayNewInfo,
            this, [label](const QString &text) {
                label->setText(text);
            });
}

///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
void LevelTwo::settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent) {
    if(isTransparent) {
        item->setStyleSheet("background: transparent");
    }
    item->setSceneRect(x, y, 10, 10);
}
