/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for Level 3 of game

#include "levelthree.h"
#include "ui_levelthree.h"
#include "dragitem.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDial>
#include <QTimer>

///@brief the constructor for level 3
LevelThree::LevelThree(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::LevelThree), time(10), seasonChickenCount(0), rubSeasoningCount(0), washLeafCount(0),
    luLeafCount(0),
    dryingLeaf(false), timerStarted(false)
{
    ui->setupUi(this);

    QSize defaultSize(200, 200);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    // creating the background for all scenes in level three
    createBackground(ui->scene1Background, "l3s1.png");
    createBackground(ui->scene2Background, "l2s1.png");
    createBackground(ui->scene3Background, "l2s1.png");
    createBackground(ui->scene4Background, "l3s4.png");
    createBackground(ui->scene5Background, "l3s5.png");
    createBackground(ui->scene6Background, "l3s6.png");
    createBackground(ui->scene7Background, "l3s7.png");
    createBackground(ui->scene8Background, "l1s4.png");
    createBackground(ui->scene9Background, "l3s9.png");
    createBackground(ui->scene10Background, "l3s10.png");
    createBackground(ui->scene11Background, "levelDone.png");

    // connection with timer

    connect(&timer, &QTimer::timeout, this, [this](){
        // scene 1
        time--;
        if(ui->levelThreeSteps->currentIndex() == 0){
            QString numStr = QString::number(time);
            ui->sceneOneLabel->setText(QString("Set the oven temp to 375 degree farenheight in: " + numStr + " second(s)"));
            if(ui->ovenTemp->value() == 375){
                timer.stop();
                ui->ovenDial->setEnabled(false);
                ui->sceneOneContinue->show();
                ui->sceneOneLabel->setText(QString("Congrats! You can now move on to the next step."));
            }
            else if(numStr.toInt() == 0){
                timer.stop();
                timerStarted = false;
                ui->failMessage->show();
                ui->ovenDial->hide();
                ui->ovenTemp->hide();
                ui->ovenTop->hide();
                ui->sceneOneLabel->hide();
            }
        }
        else{
        // scene 5

        QSize taroLeafSize(200, 200);
        if(washLeafCount == 5){
            timer.stop();
            dryingLeaf = true;
            ui->sink->setScene(createScene("sink.png", QSize(150, 150)));
            ui->faucetView->show();
            ui->faucet->hide();
            ui->taroLeaf->setScene(createScene("wet taro leaf.png", QSize(150, 150)));
            ui->taroLeaf->setSceneRect(60, -69, 10, 10);
            ui->taroLeaf->show();
            ui->leafInstruction->setText("Now, put it on the counter to dry.");
            luLeafCount++;
        }
        else if(washLeafCount % 2 == 0){
            ui->sink->setScene(createScene("leaf with splash.png", QSize(150, 150)));
            washLeafCount++;
        }
        else if(washLeafCount % 2 == 1){
            ui->sink->setScene(createScene("wet leaf in sink.png", QSize(150, 150)));
            washLeafCount++;
        }
        }
    });

    // scene 1

    ui->levelThreeSteps->setCurrentIndex(0);

    ui->sceneOneContinue->hide();

    ui->failMessage->hide();

    formatText(ui->sceneOneLabel, font);

    ui->ovenTop->setScene(createScene("oven closed.png", QSize(400, 400)));

    ui->ovenTop->setStyleSheet("background: transparent");

    ui->ovenTemp->display(170);
    ui->ovenDial->setRange(170, 550);
    ui->ovenDial->setNotchesVisible(true);
    ui->ovenDial->setSingleStep(5);
    ui->ovenDial->setWrapping(false);
    timer.setInterval(1000);

    connect(ui->ovenDial, &QDial::valueChanged, this, [this](int newTemp){
        ui->ovenTemp->display(newTemp);
        if(!timerStarted){
            timerStarted = true;
            ui->sceneOneLabel->setText("Set the oven temp to 375 degree farenheight in: 10 second(s)");
            timer.start();
        }
    });

    connect(ui->failMessage, &QPushButton::clicked, this, [this](){
        ui->failMessage->hide();
        ui->ovenDial->show();
        ui->ovenTemp->show();
        ui->ovenTop->show();
        ui->sceneOneLabel->show();
        time = 10;
        ui->sceneOneLabel->setText(QString("First step: set the oven. Move the dial to start!"));
    });

    connect(ui->sceneOneContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(1);
    });

    // scene 2

    ui->sceneTwoContinue->hide();

    formatText(ui->sceneTwoLabel, font);
    formatText(ui->infoBox, font);

    makeEducationalText(
        ui->pepper,ui->infoBox,
        "<p>Although lu is both a popular and traditional tongan dish, it does not mean that all of its ingredients have stayed the same. "
        "Spices and oils such as pepper, salt, olive oil curry powder, and garlic have all been added over the years to better compliment the dish based on the cook’s preference.</p>"

        );
    makeEducationalText(
        ui->salt,ui->infoBox,
        "<p>Although lu is both a popular and traditional tongan dish, it does not mean that all of its ingredients have stayed the same. "
        "Spices and oils such as pepper, salt, olive oil curry powder, and garlic have all been added over the years to better compliment the dish based on the cook’s preference.</p>"

        );

    ui->pepper->setScene(createScene("ground pepper.png", QSize(100, 100)));
    ui->salt->setScene(createScene("salt.png", QSize(100, 100)));
    ui->chicken->setScene(createScene("raw pixel chicken.png", QSize(150, 200)));

    ui->chicken->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->pepper, 327, 81, true);
    settingPositionAndTransparentOfitem(ui->salt, 225, 81, true);

    connectFollowDrag(ui->pepper, 420, 335, 10, 10);
    connectFollowDrag(ui->salt, 420, 335, 10, 10);

    // track if pepper is being moved on top of chicken (seasoning)
    connect(ui->pepper, &DragItem::sendLastDragDownPosition, this, [this](int x, int y){
        if(isAbove(ui->chicken, x, y)){
            seasonChickenCount++;
            if(seasonChickenCount == 3){
                seasonChickenCount = 0;
                ui->pepper->hide();
                ui->sceneTwoLabel->setText(QString("Now, season the chicken with salt."));
            }
        }
    });

    // track if salt is being moved on top of chicken (seasoning)
    connect(ui->salt, &DragItem::sendLastDragDownPosition, this, [this](int x, int y){
        if(isAbove(ui->chicken, x, y)){
            seasonChickenCount++;
            if(seasonChickenCount == 3){
                seasonChickenCount = 0;
                ui->salt->hide();
                ui->sceneTwoContinue->show();
                ui->sceneTwoLabel->setText(QString("Perfectly seasoned! Continue to the next level."));
            }
        }
    });

    connect(ui->sceneTwoContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(2);
    });

    // scene 3

    ui->sceneThreeContinue->hide();

    formatText(ui->sceneThreeLabel, font);
    formatText(ui->infoBox_3, font);

    //taro leaf item
    makeEducationalText(
        ui->oliveOil,ui->infoBox_3,
        "<p>Although lu is both a popular and traditional tongan dish, it does not mean that all of its ingredients have stayed the same. "
        "Spices and oils such as pepper, salt, olive oil curry powder, and garlic have all been added over the years to better compliment the dish based on the cook’s preference.</p>"
        );

    ui->oliveOil->setScene(createScene("oil full.png", defaultSize));
    ui->chicken_2->setScene(createScene("raw pixel chicken.png", QSize(150, 200)));

    ui->chicken_2->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->oliveOil, 277, 158, true);

    connectFollowDrag(ui->oliveOil, 420, 335, 10, 10);

    connect(ui->oliveOil, &DragItem::sendLastDragDownPosition, this, [this](int x, int y){
        if(isInside(ui->chicken_2, x, y)){
            rubSeasoningCount++;
            if(rubSeasoningCount == 10){
                ui->oliveOil->hide();
                ui->sceneThreeLabel->setText(QString("The chicken is ready! Let's move on to the oven."));
                ui->sceneThreeContinue->show();
            }
        }
    });

    connect(ui->oliveOil, &DragItem::sendLastDragUpPosition, this, [this](int x, int y){
        if(isInside(ui->chicken_2, x, y)){
            rubSeasoningCount++;
            if(rubSeasoningCount == 10){
                ui->oliveOil->hide();
                ui->sceneThreeLabel->setText(QString("The chicken is ready! Let's move on to the oven."));
                ui->sceneThreeContinue->show();
            }
        }
    });

    connect(ui->sceneThreeContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(3);
    });

    // scene 4

    ui->sceneFourContinue->hide();

    formatText(ui->sceneFourLabel, font);

    ui->chicken_3->setScene(createScene("raw pixel chicken.png", QSize(150, 150)));
    ui->oven->setScene(createScene("oven open.png", QSize(300, 400)));
    ui->bakingDish->setScene(createScene("baking dish.png", QSize(150, 150)));
    ui->bakingDish->setFrameShape(QFrame::NoFrame);

    ui->oven->setStyleSheet("background: transparent");
    ui->bakingDish->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->chicken_3, 85, 52, true);

    connectFollowDrag(ui->chicken_3, 420, 335, 10, 10);

    connect(ui->chicken_3, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bakingDish, x, y)) {
            ui->bakingDish->hide();
            ui->chicken_3->setScene(createScene("chicken in a baking dish.png", QSize(150, 150)));
            ui->sceneFourLabel->setText("Now, put the baking dish in the oven.");
        }
    });

    connect(ui->chicken_3, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->oven, x, y)) {
            ui->sceneFourContinue->show();
            ui->chicken_3->hide();
            ui->oven->setScene(createScene("oven closed.png", QSize(300, 400)));
            ui->sceneFourLabel->setText("While that is cooking, let's go to the next step.");
        }
    });

    connect(ui->sceneFourContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(4);
    });

    // scene 5

    ui->sceneFiveContinue->hide();

    formatText(ui->sceneFiveLabel, font);
    formatText(ui->leafLabel, font);
    formatText(ui->leafInstruction, font);
    formatText(ui->infoBox_5, font);

    //taro leaf item
    makeEducationalText(
        ui->taroLeaf,ui->infoBox_5,
        "<p> Taro as a crop, grows extremely well in Tonga’s tropical climate. "
        "Before aluminum foil or banana leaves were widely used, taro leaves were broad and flexible, heat resistant, and perfect for wrapping food tightly by themselves.</p>"
        "<p>They keep the chicken and coconut cream mixture sealed inside so the steam and flavors don’t escape while cooking in the oven or in other heat-trapping appliances.</p>"
        );

    ui->faucetView->hide();

    ui->taroLeaf->setScene(createScene("taro leaf with stem.png", QSize(150, 150)));
    ui->faucet->setScene(createScene("faucet.png", QSize(150, 150)));
    ui->sink->setScene(createScene("sink.png", QSize(150, 150)));
    ui->faucetView->setScene(createScene("faucet.png", defaultSize));

    ui->faucet->setStyleSheet("background: transparent");
    ui->faucetView->setStyleSheet("background: transparent");
    ui->sink->setStyleSheet("background: transparent");
    ui->sink->setFrameShape(QFrame::NoFrame);

    connectFollowDrag(ui->taroLeaf, 420, 335, 10, 10);

    settingPositionAndTransparentOfitem(ui->taroLeaf, 308, 75, true);

    // check how many leaves are on the counter and update the counter
    connect(ui->taroLeaf, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->sink, x, y) && !dryingLeaf){
            ui->taroLeaf->hide();
            ui->faucet->show();
            ui->faucetView->hide();
            ui->sink->setScene(createScene("leaf in sink.png", QSize(150, 150)));
            ui->leafInstruction->setText("Click the faucet to clean the leaf.");
        }
        else if(isInside(ui->counter, x, y) && luLeafCount == 1 && dryingLeaf){
            dryingLeaf = false;

            ui->firstCleanLeaf->setScene(createScene("wet taro leaf.png", QSize(100, 100)));
            ui->taroLeaf->setSceneRect(308, 4, 10, 10);
            ui->taroLeaf->setScene(createScene("taro leaf with stem.png", QSize(100, 100)));
            ui->leafInstruction->setText("Break the stem from the taro leaf by clicking on it.");
        }
        else if(isInside(ui->counter, x, y) && luLeafCount == 2 && dryingLeaf){
            dryingLeaf = false;

            ui->secondCleanLeaf->setScene(createScene("wet taro leaf.png", QSize(100, 100)));
            ui->taroLeaf->setSceneRect(308, 4, 10, 10);
            ui->taroLeaf->setScene(createScene("taro leaf with stem.png", QSize(100, 100)));
            ui->leafInstruction->setText("Break the stem from the taro leaf by clicking on it.");
        }
        else if(isInside(ui->counter, x, y) && luLeafCount == 3 && dryingLeaf){
            dryingLeaf = false;

            ui->thirdCleanLeaf->setScene(createScene("wet taro leaf.png", QSize(100, 100)));
            ui->taroLeaf->hide();
            ui->leafInstruction->hide();
            ui->leafLabel->hide();
            ui->sceneFiveContinue->show();
            ui->sceneFiveLabel->setText("Perfect! Now, let's go prepare the foil.");

            luLeafCount = 0;
        }
        else if(!dryingLeaf){
            ui->taroLeaf->setScene(createScene("taro leaf.png", QSize(100, 100)));
            ui->leafInstruction->setText("Take leaf to the sink.");
        }
    });

    connect(ui->faucet, &DragItem::releasePosition, this, [this](){
        washLeafCount = 0;
        ui->faucet->hide();
        ui->faucetView->show();
        timer.start();
    });

    connect(ui->sceneFiveContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(5);
    });

    // scene 6

    ui->sceneSixContinue->hide();

    ui->sceneSixLabel->setText("Cut the foil by clicking the scissors!");

    formatText(ui->sceneSixLabel, font);

    ui->firstCut->setScene(createScene("cutting line.png", QSize(200, 200)));
    ui->foil->setScene(createScene("whole foil.png", QSize(400, 400)));

    ui->firstCut->setStyleSheet("background: transparent");
    ui->secondCut->setStyleSheet("background: transparent");
    ui->foil->setStyleSheet("background: transparent");

    connect(ui->firstCut, &DragItem::releasePosition, this, [this](){
        ui->firstCut->hide();
        ui->secondCut->setScene(createScene("cutting line.png", QSize(200, 200)));
        ui->foil->setScene(createScene("first cut foil.png", QSize(400, 400)));
    });

    connect(ui->secondCut, &DragItem::releasePosition, this, [this](){
        ui->secondCut->hide();
        ui->faucet->hide();
        ui->foil->setScene(createScene("second cut foil.png", QSize(400, 400)));
        ui->sceneSixLabel->setText("Perfect! Now, let's shred some chicken.");
        ui->sceneSixContinue->show();
    });

    connect(ui->sceneSixContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(6);
    });

    // scene 7

    ui->sceneSevenContinue->hide();

    ui->sceneSevenLabel->setText("Shred the chicken with a knife by dragging the knife over the chicken 4 times");

    formatText(ui->sceneSevenLabel, font);

    ui->bakedChicken->setScene(createScene("cooked chicken.png", QSize(100, 100)));
    ui->knife->setScene(createScene("knife.png", QSize(100, 100)));
    ui->bakedChicken->setFrameShape(QFrame::NoFrame);

    ui->bakedChicken->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->knife, 371, 140, true);

    connectFollowDrag(ui->knife, 420, 335, 10, 10);

    // check how many times knife has shredded chicken
    connect(ui->knife, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bakedChicken, x, y)) {
            knifeCount++;
            this->ui->knife->setSceneRect( 371, 129, 10, 10);
        }
        if(knifeCount == 4){
            this->ui->knife->hide();
            this->ui->sceneSevenContinue->show();
            this->ui->bakedChicken->setScene(createScene("shredded chicken.png", QSize(100, 100)));
            this->ui->sceneSevenLabel->setText("Nice job! Now press continue");
        }
    });

    connect(ui->sceneSevenContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(7);
    });

    // scene 8

    ui->sceneEightContinue->hide();

    ui->sceneEightLabel->setText("First, add the shredded chicken to the bowl");

    formatText(ui->sceneEightLabel, font);
    formatText(ui->infoBox_8, font);

    //coconut milk item
    makeEducationalText(
        ui->coconutMilk,ui->infoBox_8,
        "<p> coconut milk is also essential in every lu dish across Tonga. It’s not just for taste. Coconut milk keeps the taro leaves moist, tender and silky. After adding coconut milk, lu moa contains a thick, rich, flavorful gravy and this is the iconic taste of lu dishes.</p>"
        "<p>Besides the taste, coconuts were one of the main fat sources available on islands like Tonga. It provides enough calories, satiety and richness for lu dishes for Tongans.</p>"
        );

    //curry item
    makeEducationalText(
        ui->curry,ui->infoBox_8,
        "<p>Although lu is both a popular and traditional tongan dish, it does not mean that all of its ingredients have stayed the same. "
        "Spices and oils such as pepper, salt, olive oil curry powder, and garlic have all been added over the years to better compliment the dish based on the cook’s preference.</p>"
        );

    //onion item
    makeEducationalText(
        ui->dicedOnions,ui->infoBox_8,
        "<p>Even though onions originated in Central Asia/ Middle East, they spread globally through early trade, and European sailors and missionaries introduced onions to Tonga in the 1700s-1800s. "
        "After their introduction, Tongans adopted onions into many dishes because they complement coconut-based cooking extremely well. </p>"
        );

    //onion item
    makeEducationalText(
        ui->mayo,ui->infoBox_8,
        "<p>Coconut milk is one of the main ingredients in the dish. "
        "However, as people move to different areas of the world with different agriculture, mayo and cow milk is often used as a first substitute. "
        "Or, as in this case, as an additional ingredient to change the texture.</p>"
        );

    //garlic item
    makeEducationalText(
        ui->mincedGarlic,ui->infoBox_8,
        "<p>Although lu is both a popular and traditional tongan dish, it does not mean that all of its ingredients have stayed the same. "
        "Spices and oils such as pepper, salt, olive oil curry powder, and garlic have all been added over the years to better compliment the dish based on the cook’s preference.</p>"
        );

    ui->shreddedChicken->setScene(createScene("shredded chicken.png", QSize(100, 100)));
    ui->dicedOnions->setScene(createScene("diced onions.png", QSize(100, 100)));
    ui->mincedGarlic->setScene(createScene("minced garlic.png", QSize(100, 100)));
    ui->curry->setScene(createScene("curry.png", QSize(100, 100)));
    ui->salt_2->setScene(createScene("salt.png", QSize(100, 100)));
    ui->pepper_2->setScene(createScene("ground pepper.png", QSize(100, 100)));
    ui->coconutMilk->setScene(createScene("coconut milk.png", QSize(100, 100)));
    ui->mayo->setScene(createScene("mayo.png", QSize(100, 100)));
    ui->bowl->setScene(createScene("bowl.png", QSize(200, 200)));
    ui->bowl->setFrameShape(QFrame::NoFrame);

    ui->bowl->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->shreddedChicken, -239, 88, true);
    settingPositionAndTransparentOfitem(ui->dicedOnions, -125, 92, true);
    settingPositionAndTransparentOfitem(ui->mincedGarlic, -1, 94, true);
    settingPositionAndTransparentOfitem(ui->curry, 111, 92, true);
    settingPositionAndTransparentOfitem(ui->salt_2, 235, -35, true);
    settingPositionAndTransparentOfitem(ui->pepper_2, 302, 0, true);
    settingPositionAndTransparentOfitem(ui->coconutMilk, 178, -82, true);
    settingPositionAndTransparentOfitem(ui->mayo, 29, -72, true);

    connectFollowDrag(ui->shreddedChicken, 420, 335, 10, 10);
    connectFollowDrag(ui->dicedOnions, 420, 335, 10, 10);
    connectFollowDrag(ui->mincedGarlic, 420, 335, 10, 10);
    connectFollowDrag(ui->curry, 420, 335, 10, 10);
    connectFollowDrag(ui->salt_2, 420, 335, 10, 10);
    connectFollowDrag(ui->pepper_2, 420, 335, 10, 10);
    connectFollowDrag(ui->coconutMilk, 420, 335, 10, 10);
    connectFollowDrag(ui->mayo, 420, 335, 10, 10);

    connect(ui->shreddedChicken, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->shreddedChicken->hide();
            this->ui->bowl->setScene(createScene("bowl making lu 1.png", QSize(200, 200)));
            this->ui->sceneEightLabel->setText(QString("Second, drag diced onions to the bowl"));
        }
    });

    connect(ui->dicedOnions, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->dicedOnions->hide();
            this->ui->sceneEightLabel->setText(QString("Third, drag minced garlic to the bowl"));
        }
    });

    connect(ui->mincedGarlic, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->mincedGarlic->hide();
            this->ui->sceneEightLabel->setText(QString("Next, drag curry to the bowl"));
        }
    });

    connect(ui->curry, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->curry->hide();
            this->ui->sceneEightLabel->setText(QString("Next, drag salt to the bowl"));
        }
    });

    connect(ui->salt_2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->salt_2->hide();
            this->ui->sceneEightLabel->setText(QString("Next, drag pepper to the bowl"));
        }
    });

    connect(ui->pepper_2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->pepper_2->hide();
            this->ui->bowl->setScene(createScene("bowl making lu 2.png", QSize(200, 200)));
            this->ui->sceneEightLabel->setText(QString("Next, drag coconut milk to the bowl"));
        }
    });

    connect(ui->coconutMilk, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->coconutMilk->hide();
            this->ui->sceneEightLabel->setText(QString("Finally, drag mayo to the bowl"));
        }
    });

    connect(ui->mayo, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl, x, y)) {
            this->ui->mayo->hide();
            this->ui->sceneEightContinue->show();
            ui->bowl->setScene(createScene("bowl with lu.png", QSize(200, 200)));
            this->ui->sceneEightLabel->setText(QString("Nice job! Press continue"));
        }
    });

    connect(ui->sceneEightContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(8);
    });

    // scene 9

    ui->sceneNineContinue->hide();

    formatText(ui->sceneNineLabel, font);

    ui->firstFold->hide();
    ui->secondFold->hide();
    ui->thirdFold->hide();
    ui->fourthFold->hide();
    ui->luWrapOne->hide();
    ui->luWrapTwo->hide();
    ui->luWrapThree->hide();

    ui->foil_2->setScene(createScene("foil.png", QSize(300, 300)));
    ui->bowl_2->setScene(createScene("bowl with lu.png", QSize(400, 280)));
    ui->bowl_2->setFrameShape(QFrame::NoFrame);
    ui->scoop->setScene(createScene("ladle.png", QSize(221, 221)));
    ui->lu->setScene(createScene("dry leaf.png", QSize(260, 260)));
    ui->firstFold->setScene(createScene("left leaf.png", QSize(125, 255)));
    ui->secondFold->setScene(createScene("right leaf.png", QSize(125, 255)));
    ui->thirdFold->setScene(createScene("top leaf.png", QSize(260, 130)));
    ui->fourthFold->setScene(createScene("bottom leaf.png", QSize(260, 130)));
    ui->luWrapOne->setScene(createScene("ball of lu.png", QSize(151, 131)));
    ui->luWrapTwo->setScene(createScene("ball of lu.png", QSize(151, 131)));
    ui->luWrapThree->setScene(createScene("ball of lu.png", QSize(151, 131)));

    ui->foil_2->setStyleSheet("background: transparent");
    ui->bowl_2->setStyleSheet("background: transparent");
    ui->firstFold->setStyleSheet("border: 0px; background: transparent");
    ui->secondFold->setStyleSheet("border: 0px; background: transparent");
    ui->thirdFold->setStyleSheet("border: 0px; background: transparent");
    ui->fourthFold->setStyleSheet("border: 0px; background: transparent");
    ui->luWrapOne->setStyleSheet("background: transparent");
    ui->luWrapTwo->setStyleSheet("background: transparent");
    ui->luWrapThree->setStyleSheet("background: transparent");

    ui->lu->setEnabled(false);

    settingPositionAndTransparentOfitem(ui->scoop, -240, 15, true);
    settingPositionAndTransparentOfitem(ui->lu, 355, -5, true);

    connectFollowDrag(ui->scoop, 420, 335, 10, 10);
    connectFollowDrag(ui->lu, 420, 335, 10, 10);

    connect(ui->scoop, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_2, x, y)){
            ui->scoop->setScene(createScene("ladle with lu.png", QSize(221, 221)));
            ui->sceneNineLabel->setText("Now, drag the ladle to the taro leaf.");
        }
        else if(isInside(ui->foil_2, x, y)){
            ui->scoop->hide();
            ui->scoop->setScene(createScene("ladle.png", QSize(221, 221)));
            ui->scoop->setSceneRect(-660 + 420,-320 + 335, 10, 10);
            ui->lu->setScene(createScene("leaf with lu.png", QSize(260, 260)));
            ui->firstFold->show();
            ui->sceneNineLabel->setText("Now, fold the left leaf in.");
        }
    });

    // track and update folds as user is folding over the lu
    connect(ui->firstFold, &DragItem::sendLastDragRightPosition, this, [this](){
        ui->firstFold->hide();
        ui->secondFold->show();
        ui->lu->setScene(createScene("first fold leaf.png", QSize(260, 260)));
        ui->sceneNineLabel->setText("Now, fold the right leaf in.");
    });
    connect(ui->secondFold, &DragItem::sendLastDragLeftPosition, this, [this](){
        ui->secondFold->hide();
        ui->thirdFold->show();
        ui->lu->setScene(createScene("second fold leaf.png", QSize(260, 260)));
        ui->sceneNineLabel->setText("Now, fold the top leaf in.");
    });
    connect(ui->thirdFold, &DragItem::sendLastDragDownPosition, this, [this](){
        ui->thirdFold->hide();
        ui->fourthFold->show();
        ui->lu->setScene(createScene("third fold leaf.png", QSize(260, 260)));
        ui->sceneNineLabel->setText("Now, fold the bottom leaf in.");
    });
    connect(ui->fourthFold, &DragItem::sendLastDragUpPosition, this, [this](){
        ui->fourthFold->hide();
        ui->lu->setEnabled(true);
        ui->lu->setScene(createScene("fourth fold leaf.png", QSize(260, 260)));
        ui->sceneNineLabel->setText("Perfect! Click to wrap and then drag to plate.");

        luLeafCount++;
    });

    connect(ui->lu, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->counter_2, x, y)){
            ui->foil_2->show();
            ui->foil_2->setScene(createScene("foil.png", QSize(300, 300)));
            ui->lu->setScene(createScene("dry leaf.png", QSize(260, 260)));
            ui->lu->setSceneRect(-65 + 420,-340 + 335, 10, 10);
            ui->lu->setEnabled(false);

            ui->scoop->show();

            if(luLeafCount == 1){
                ui->luWrapOne->show();
                ui->sceneNineLabel->setText("Drag the scooper to bowl to get the filling for the lu.");
            }else if(luLeafCount == 2){
                ui->luWrapTwo->show();
                ui->sceneNineLabel->setText("Drag the scooper to bowl to get the filling for the lu.");
            }else{
                ui->luWrapThree->show();
                ui->lu->hide();
                ui->foil_2->hide();
                ui->sceneNineLabel->setText("Perfect! Let's finally steam them.");

                ui->scoop->hide();
                ui->sceneNineContinue->show();

                luLeafCount = 0;
            }

        }else if(isInside(ui->foil, x, y)){
            ui->foil_2->hide();
            ui->lu->setScene(createScene("ball of lu.png", QSize(260, 260)));
        }
    });

    connect(ui->sceneNineContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(9);
    });

    // scene 10

    ui->sceneTenContinue->hide();

    formatText(ui->sceneTenLabel, font);
    formatText(ui->infoBox_10, font);

    //steamer item
    makeEducationalText(
        ui->selectedLu,ui->infoBox_10,
        "<p>Outside leaves, lu second, meat, flavors onions and tomatoes, coconut milk, lu leaf covers it, after wrap around, big leaves outside.</p>"
        "<p>Dig a hole, fire inside with rocks that hold heat, put lu on top, and after put mesh wire on top, put old rugs and old blankets, 5-10 layers. Leave it there for an hour or two.</p>"
        );

    ui->selectedLu->hide();

    ui->steamer->setScene(createScene("steamer.png", QSize(271, 261)));
    ui->steamer->setFrameShape(QFrame::NoFrame);
    ui->stoveTop->setScene(createScene("stove.png", QSize(300, 200)));
    ui->stoveTop->setFrameShape(QFrame::NoFrame);
    ui->selectedLu->setScene(createScene("ball of lu.png", QSize(131, 121)));
    ui->firstLuWrap->setScene(createScene("ball of lu.png", QSize(131, 121)));
    ui->firstLuWrap->setFrameShape(QFrame::NoFrame);
    ui->secondLuWrap->setScene(createScene("ball of lu.png", QSize(131, 121)));
    ui->secondLuWrap->setFrameShape(QFrame::NoFrame);
    ui->thirdLuWrap->setScene(createScene("ball of lu.png", QSize(131, 121)));
    ui->thirdLuWrap->setFrameShape(QFrame::NoFrame);

    ui->steamer->setStyleSheet("background: transparent");
    ui->stoveTop->setStyleSheet("background: transparent");
    ui->firstLuWrap->setStyleSheet("background: transparent");
    ui->secondLuWrap->setStyleSheet("background: transparent");
    ui->thirdLuWrap->setStyleSheet("background: transparent");

    ui->stoveTempSlider->setTickInterval(1);
    ui->stoveTempSlider->setRange(1, 5);

    settingPositionAndTransparentOfitem(ui->selectedLu, 295, -25, true);

    connectFollowDrag(ui->selectedLu, 420, 335, 10, 10);

    connect(ui->stoveTempSlider, &QSlider::valueChanged, this, [this](int stoveTemp){
        if(stoveTemp == 3){
            ui->stoveTempSlider->setEnabled(false);
            ui->sceneTenLabel->setText("Sweet! Now, put all of the lu inside the steamer.");

            ui->firstLuWrap->hide();
            ui->selectedLu->show();
        }
    });

    connect(ui->selectedLu, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->steamer, x, y)){

            if(luLeafCount == 0){
                ui->secondLuWrap->hide();
                ui->selectedLu->setSceneRect(-20 + 395,-380 + 295, 10, 10);
                luLeafCount++;
            } else if(luLeafCount == 1){
                ui->thirdLuWrap->hide();
                ui->selectedLu->setSceneRect(-180 + 395,-380 + 295, 10, 10);
                luLeafCount++;
            }else{
                ui->selectedLu->hide();
                ui->sceneTenContinue->show();
                ui->sceneTenLabel->setText("Now, leave that to cook for four hours.");
            }
        }
    });

    connect(ui->sceneTenContinue, &QPushButton::clicked, this, [this](){
        ui->levelThreeSteps->setCurrentIndex(10);
    });

    // scene 11

    formatText(ui->sceneElevenLabel, font);

    ui->luMoa->setScene(createScene("balls of lu.png", QSize(300, 300)));

    ui->luMoa->setStyleSheet("background: transparent");

    connect(ui->levelMenusButton, &QPushButton::clicked, this, [this](){emit goBackToMenu();});
}

///@brief deconstructor for level 3
LevelThree::~LevelThree()
{
    delete ui;
}

///@brief create image object
///@param filename: image to be used
///@param size of image
QGraphicsScene* LevelThree::createScene(QString fileName, QSize sceneSize){
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
bool LevelThree::isInside(QWidget *target, int x, int y) const
{
    // widget rect in parent coordinates
    QRect targetRect(target->pos(), target->size());
    return targetRect.contains(QPoint(x, y));
}

///@brief checking if coords of mouse dragging QGraphicsView is above the target (QGraphicsView)
///@param *target: image (QGraphicsView) to be checked
///@param x: x coord of image being dragged (QGraphicsView)
///@param y: y coord of image being dragged (QGraphicsView)
bool LevelThree::isAbove(QWidget *target, int x, int y)
{
    int targetLowerXBound = target->pos().x();
    int targetHigherXBound = targetLowerXBound + target->width();
    int targetLowerYBound = target->pos().y();
    int targetHigherYBound = targetLowerYBound + target->height();
    return x > targetLowerXBound && x < targetHigherXBound && y < targetHigherYBound;
}

///@brief redraw image to have it follow the mouse as it drags
///@param *item: image (QGraphicsView) to be dragged
///@param offsetX: offset for x so the image follows right below mouse
///@param offsetY: offset for y so the image follows right below mouse
void LevelThree::connectFollowDrag(DragItem *item,int offsetX,int offsetY,int rectW,int rectH)
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
void LevelThree::createBackground(QGraphicsView* backgroundView, QString backgroundFileName){
    backgroundView->setScene(createScene(backgroundFileName, QSize(800, 600)));
    backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

///@brief This method is used to format the text of each label in the level
/// @param label: The label that will be displayed
/// @param font: The formatting of the text
void LevelThree::formatText(QLabel* label, QFont font){
    label->setFont(font);
    label->setWordWrap(true);
    label->setStyleSheet("color: white;");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

///@brief create text for educational background for an ingredient
void LevelThree::makeEducationalText(DragItem *item, QLabel *label, const QString &info)
{
    item->setInfoText(info);
    connect(item, &DragItem::displayNewInfo,
            this, [label](const QString &text) {
                label->setText(text);
            });
}

///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
void LevelThree::settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent) {
    if(isTransparent) {
        item->setStyleSheet("background: transparent");
    }
    item->setSceneRect(x, y, 10, 10);
}

