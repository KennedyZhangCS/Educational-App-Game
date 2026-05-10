/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief The cpp file that implements all methods for Level 4 of game

#include "levelfour.h"
#include "ui_levelfour.h"

#include <QFont>

/**
 * @brief LevelFour::LevelFour
 * @param parent
 *
 *     ///@brief constructor for level 4
    explicit LevelFour(QWidget *parent = nullptr);
    ///@brief deconstructor for level 4
    ~LevelFour();
 */

///@brief constructor for level 4
LevelFour::LevelFour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelFour), pestleHitCount(0), knifeSliceCount(0), currentIngIndex(0), chickenCounter(0)
    , chickenFlipIsFalling(false), chickenFlipReachedTop(false)
{
    ui->setupUi(this);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    // creating the background for all scenes in level four
    createBackground(ui->scene1Background, "l2s4.png");
    createBackground(ui->scene2Background, "l1s1.png");
    createBackground(ui->scene3Background, "l1s4.png");
    createBackground(ui->scene4Background, "l2s2.png");
    createBackground(ui->scene5Background, "l4s5.png");
    createBackground(ui->scene6Background, "l4s6.png");
    createBackground(ui->scene7Background, "l3s4.png");
    createBackground(ui->scene8Background, "l4s6.png");
    createBackground(ui->scene9Background, "l1s4.png");
    createBackground(ui->scene10Background, "l3s4.png");
    createBackground(ui->scene11Background, "l1s1.png");
    createBackground(ui->scene12Background, "levelDone.png");

    // scene 1

    ui->levelFourScenes->setCurrentIndex(0);

    ui->sceneOneContinue->hide();

    ui->sceneOneInstructions->setText(QString("Drag the ginger to the mortar"));

    formatText(ui->sceneOneInstructions, font);
    formatText(ui->sceneOneInfoBox, font);

    makeEducationalText(
        ui->ginger,ui->sceneOneInfoBox,
        "<p> Grown in Nepal around the mid-hills regions and is the fourth largest producer of ginger. </p>"
        );

    makeEducationalText(
        ui->garlic,ui->sceneOneInfoBox,
        "<p> Grown in Nepal due to the ideal climate near the Himalayan foothill and is a staple of Newari cooking. </p>"
        );

    makeEducationalText(
        ui->pestle,ui->sceneOneInfoBox,
        "<p> The paste is used to neutralize the smell of chicken and aid in digestion. Choila was traditionally a way to prepare meat in order to preserve it for a longer time, due to this, ginger and garlic was used to help with this process.  </p>"
        );

    ui->mashedIng->hide();

    // setting up the images in the level
    ui->ginger->setScene(createScene("ginger.png", QSize(150,150)));
    ui->garlic->setScene(createScene("garlic.png", QSize(150,150)));
    ui->pestle->setScene(createScene("pestle.png", QSize(150,150)));
    ui->mortor->setScene(createScene("mortar.png", QSize(300,300)));
    ui->mashedIng->setScene(createScene("ginger and garlic paste.png",QSize(300,300)));

    ui->mashedIng->setStyleSheet("background: transparent");
    ui->mortor->setStyleSheet("background: transparent");
    ui->mortor->setFrameShape(QFrame::NoFrame);

    // setting the position and making the images transparent
    settingPositionAndTransparentOfitem(ui->ginger, 400,-65,true);
    settingPositionAndTransparentOfitem(ui->garlic, 300,-65,true);
    settingPositionAndTransparentOfitem(ui->pestle, 200,-65,true);

    // making images follow the mouse as they click
    connectFollowDrag(ui->ginger, 420, 335, 10, 10);
    connectFollowDrag(ui->garlic, 420, 335, 10, 10);
    connectFollowDrag(ui->pestle, 420, 335, 10, 10);

    // creating connections to make the image draggable
    connect(ui->ginger, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortor, x, y)) {
            ui->sceneOneInstructions->setText(QString("Now drag the garlic"));
            this->ui->ginger->hide();
        }
    });

    connect(ui->garlic, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortor, x, y)) {
            this->ui->garlic->hide();
            ui->sceneOneInstructions->setText(QString("Perfect! Now hit the mortar with the pestle 5 times."));
        }
    });

    connect(ui->pestle, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortor, x, y)) {
            pestleHitCount++;
        }
        if(pestleHitCount == 5){
            this->ui->pestle->hide();
            this->ui->mortor->hide();
            this->ui->sceneOneInfoBox->hide();
            this->ui->mashedIng->show();
            this->ui->mashedIng->setStyleSheet("background: transparent");
            this->ui->sceneOneContinue->show();
            ui->sceneOneInstructions->setText(QString("Great, continue to the next step by pressing the continue button!"));
        }
    });

    connect(ui->sceneOneContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(1);
    });

    // scene 2

    ui->sceneTwoContinue->hide();

    ui->sceneTwoInstructions->setText(QString("Start by dragging the salt into the mortar."));

    formatText(ui->sceneTwoInstructions, font);
    formatText(ui->sceneTwoInfoBox, font);

    makeEducationalText(
        ui->pepper,ui->sceneTwoInfoBox,
        "<p> Spices have been used in Nepal for thousands of years. The spices in Newari cuisine is similar to the spices used in India, although, combines these spices from ones imported from China like Szechuan peppers. </p>"
        );

    makeEducationalText(
        ui->cumin,ui->sceneTwoInfoBox,
        "<p> Provides earthy, warm, and nutty depth to the dish </p>"
        "<p> Aid in digestion and contains antioxidants that help reduce inflammation </p>"
        );

    makeEducationalText(
        ui->coriander,ui->sceneTwoInfoBox,
        "<p> Traditionally used in Newari dishes. In the past, India and Nepal shared a similar spice palette and both had access to produce .coriander seeds. The spice is used to add earthy notes into the dish </p>"
        );

    makeEducationalText(
        ui->curry,ui->sceneTwoInfoBox,
        "<p> Combination of cardamon, cloves, nutmeg, and other himalayan spices. </p>"
        );

    makeEducationalText(
        ui->turmeric,ui->sceneTwoInfoBox,
        "<p> Staple of Newari cooking, adds a yellow hue to the dish and is used to preserve the dishes </p>"
        );

    makeEducationalText(
        ui->redChili,ui->sceneTwoInfoBox,
        "<p> Another staple of Newari cooking, adds intense heat, flavor, and color. </p>"
        );

    makeEducationalText(
        ui->salt,ui->sceneTwoInfoBox,
        "<p> Import from Tibet, at the start was black salt but now is brought in from India. </p>"
        );

    makeEducationalText(
        ui->pestleS2,ui->sceneTwoInfoBox,
        "<p> Mashing the spices intensfies the flavors and aroma by breakingdown the walls of the spices. </p>"
        "<p> This method is traditional and has been passed down through generations. </p>"
        );

    ui->crushedIng->hide();

    // creating all images for scene two
    ui->pepper->setScene(createScene("szechuan pepper.png", QSize(100,100)));
    ui->cumin->setScene(createScene("bowl of cumin.png", QSize(100,100)));
    ui->coriander->setScene(createScene("coriander.png", QSize(100,100)));
    ui->curry->setScene(createScene("curry.png", QSize(100,100)));
    ui->turmeric->setScene(createScene("bowl of tumeric.png", QSize(100,100)));
    ui->redChili->setScene(createScene("bowl of red chilli powder.png", QSize(100,100)));
    ui->salt->setScene(createScene("salt.png", QSize(100,100)));
    ui->pestleS2->setScene(createScene("pestle.png", QSize(100,100)));
    ui->mortar->setScene(createScene("mortar.png", QSize(250,250)));
    ui->mortar->setFrameShape(QFrame::NoFrame);
    ui->crushedIng->setScene(createScene("spice mixture.png",QSize(250,250)));

    ui->mortar->setStyleSheet("background: transparent");
    ui->crushedIng->setStyleSheet("background: transparent");

    // setting the position of all the scenes
    settingPositionAndTransparentOfitem(ui->pepper,189,220,true);
    settingPositionAndTransparentOfitem(ui->cumin,275,230,true);
    settingPositionAndTransparentOfitem(ui->coriander, 358,230,true);
    settingPositionAndTransparentOfitem(ui->curry, 191,80,true);
    settingPositionAndTransparentOfitem(ui->turmeric, 191,80,true);
    settingPositionAndTransparentOfitem(ui->redChili,290,80,true);
    settingPositionAndTransparentOfitem(ui->salt, 368,80,true);
    settingPositionAndTransparentOfitem(ui->pestleS2,122,-75,true);

    // making images follow the mouse as they click
    connectFollowDrag(ui->pepper, 420, 335, 10, 10);
    connectFollowDrag(ui->cumin, 420, 335, 10, 10);
    connectFollowDrag(ui->coriander, 420, 335, 10, 10);
    connectFollowDrag(ui->turmeric, 420, 335, 10, 10);
    connectFollowDrag(ui->curry, 420, 335, 10, 10);
    connectFollowDrag(ui->redChili, 420, 335, 10, 10);
    connectFollowDrag(ui->salt, 420, 335, 10, 10);
    connectFollowDrag(ui->pestleS2, 420, 335, 10, 10);

    // creating connections for all items
    connect(ui->pepper, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->pepper->hide();
            ui->sceneTwoInstructions->setText(QString("Perfect! Now mash all seasoning."));
        }
    });

    connect(ui->cumin, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->cumin->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the sichuan peppers into the mortar."));
        }
    });

    connect(ui->coriander, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->coriander->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the cumin into the mortar."));
        }
    });

    connect(ui->curry, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->curry->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the coriander seeds into the mortar."));
        }
    });

    connect(ui->turmeric, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->turmeric->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the curry powder into the mortar."));
        }
    });

    connect(ui->redChili, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->redChili->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the turmeric into the mortar."));
        }
    });

    connect(ui->salt, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            this->ui->salt->hide();
            ui->sceneTwoInstructions->setText(QString("Drag the red chilis into the mortar."));
        }
    });

    connect(ui->pestleS2, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->mortar, x, y)) {
            pestleHitCount++;
        }
        if(pestleHitCount == 10){
            this->ui->pestleS2->hide();
            this->ui->mortar->hide();
            this->ui->crushedIng->show();
            this->ui->crushedIng->setStyleSheet("background: transparent");
            this->ui->sceneTwoContinue->show();
        }
    });

    connect(ui->sceneTwoContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(2);
    });

    // scene 3

    ui->sceneThreeContinue->hide();

    ui->sceneThreeInstructions->setText(QString("Drag the onion to the cutting board."));

    formatText(ui->sceneThreeInstructions, font);
    formatText(ui->sceneThreeInfoBox, font);

    ui->choppedIng->hide();

    // creating images for scene 3
    ui->currentIng->setScene(createScene("onion.png", QSize(100,100)));
    ui->knife->setScene(createScene("knife.png", QSize(100,100)));
    ui->cuttingBoard->setScene(createScene("cutting board.png", QSize(375,375)));
    ui->cuttingBoard->setFrameShape(QFrame::NoFrame);

    ui->cuttingBoard->setStyleSheet("background: transparent");

    // setting the position for all draggable items
    settingPositionAndTransparentOfitem(ui->currentIng, 241, -64, true);
    settingPositionAndTransparentOfitem(ui->knife, 285, 73, true);

    connectFollowDrag(ui->currentIng, 420, 335, 10, 10);
    connectFollowDrag(ui->knife, 420, 335, 10, 10);

    connect(ui->currentIng, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->cuttingBoard, x, y)) {
            this->ui->currentIng->hide();
            this->ui->choppedIng->setScene(createScene("onion.png", QSize(100,100)));
            ui->choppedIng->setStyleSheet("background: transparent");
            this->ui->choppedIng->show();
        }

        if (isInside(ui->cuttingBoard, x, y) && currentIngIndex == 1) {
            this->ui->currentIng->hide();
            this->ui->choppedIng->setScene(createScene("garlic.png", QSize(100,100)));
            ui->choppedIng->setStyleSheet("background: transparent");
            this->ui->choppedIng->show();
        }

        if (isInside(ui->cuttingBoard, x, y) && currentIngIndex == 2) {
            this->ui->currentIng->hide();
            this->ui->choppedIng->setScene(createScene("serrano pepper.png", QSize(100,100)));
            ui->choppedIng->setStyleSheet("background: transparent");
            this->ui->choppedIng->show();
        }
    });

    connect(ui->knife, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->choppedIng, x, y)) {
           knifeSliceCount++;
        }

        if(currentIngIndex == 0) {
            ui->sceneThreeInfoBox->setText("<p> Called 'pyaj'. It is a red onion grown in Nepal </p>"
                                           "<p> staple of Newari cooking. Used to add color and spice in the dish.</p>");
        }

        if(knifeSliceCount == 3 && currentIngIndex == 0){
            ui->choppedIng->hide();
            ui->currentIng->setScene(createScene("garlic.png", QSize(100,100)));
            settingPositionAndTransparentOfitem(ui->knife, 285, 73, true);
            settingPositionAndTransparentOfitem(ui->currentIng, 241, -64, true);
            ui->currentIng->show();
            ui->sceneThreeInstructions->setText(QString("Drag the garlic to the cutting board."));
            currentIngIndex++;
        }

        if(knifeSliceCount == 6 && currentIngIndex == 1){
            ui->choppedIng->hide();
            ui->currentIng->setScene(createScene("serrano pepper.png", QSize(100,100)));
            settingPositionAndTransparentOfitem(ui->knife, 285, 73, true);
            settingPositionAndTransparentOfitem(ui->currentIng, 241, -64, true);
            ui->currentIng->show();
            ui->sceneThreeInstructions->setText(QString("Drag the serrano peppers to the cutting board."));
            ui->sceneThreeInfoBox->setText(QString("<p> Grown in Nepal <p> "
                                                   "<p>Sspicier peppers like Dalle Khursani are popular in the country<p>"
                                                   "<p>Peppers in the past were used to kill parasites in stomachs. <p>"));
            currentIngIndex++;
        }

        if(knifeSliceCount == 9 && currentIngIndex == 2){
            ui->choppedIng->hide();
            ui->sceneThreeInstructions->setText(QString("Press the continue button!"));
            ui->knife->hide();
            this->ui->sceneThreeContinue->show();
        }
    });

    connect(ui->sceneThreeContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(3);
    });

    // scene 4 for level 4

    ui->sceneFourContinue->hide();

    ui->sceneFourInstructions->setText(QString("Drag the sliced garlic to the bowl."));

    formatText(ui->sceneFourInstructions, font);
    formatText(ui->sceneFourInfoBox, font);

    // creating images for scene 4
    ui->choppedGarlic->setScene(createScene("minced garlic.png", QSize(100,100)));
    ui->choppedOnion->setScene(createScene("diced onions", QSize(100,100)));
    ui->choppedSerrano->setScene(createScene("chopped serrano.png", QSize(100,100)));
    ui->allChoppedIng->setScene(createScene("three empty bowls.png", QSize(400,400)));
    ui->allChoppedIng->setFrameShape(QFrame::NoFrame);

    ui->allChoppedIng->setStyleSheet("background: transparent");

    // setting the position for all draggable items
    settingPositionAndTransparentOfitem(ui->choppedGarlic, 163, -90, true);
    settingPositionAndTransparentOfitem(ui->choppedOnion, 303, -79, true);
    settingPositionAndTransparentOfitem(ui->choppedSerrano, 382, -73, true);

    connectFollowDrag(ui->choppedGarlic, 420, 335, 10, 10);
    connectFollowDrag(ui->choppedOnion, 420, 335, 10, 10);
    connectFollowDrag(ui->choppedSerrano, 420, 335, 10, 10);

    // creating connections
    connect(ui->choppedGarlic, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->allChoppedIng, x, y)) {
            this->ui->choppedGarlic->hide();
            ui->allChoppedIng->setScene(createScene("chopped ing 1.png", QSize(400,400)));
            ui->sceneFourInstructions->setText(QString("Drag the sliced onion to the bowl."));
        }
    });

    connect(ui->choppedOnion, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->allChoppedIng, x, y)) {
            this->ui->choppedOnion->hide();
            ui->allChoppedIng->setScene(createScene("chopped ing 2.png", QSize(400,400)));
            ui->sceneFourInstructions->setText(QString("Drag the sliced serrano peppers to the bowl."));

        }
    });

    connect(ui->choppedSerrano, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->allChoppedIng, x, y)) {
            this->ui->choppedSerrano->hide();
            ui->allChoppedIng->setScene(createScene("chopped ing 3.png", QSize(400,400)));
            ui->sceneFourInstructions->setText(QString("Great! Press the continue button."));
            ui->sceneFourContinue->show();
        }
    });

    connect(ui->sceneFourContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(4);
    });

    // scene 5

    ui->sceneFiveContinue->hide();

    ui->sceneFiveInstructions->setText(QString("Drag the tomatos into the pot!"));

    formatText(ui->sceneFiveInstructions, font);
    formatText(ui->sceneFiveInfoBox, font);

    makeEducationalText(
        ui->tomato,ui->sceneFiveInfoBox,
        "<p> Not used in the traditional dish, however, in the modern version of the dish it is used to add a smoky and deeper flavor </p>"
        );

    ui->tomato->setScene(createScene("one tomato.png", QSize(100,100)));
    ui->tomatoTwo->setScene(createScene("one tomato.png", QSize(100,100)));
    ui->tomatoThree->setScene(createScene("one tomato.png", QSize(100,100)));
    ui->pot->setScene(createScene("pot.png", QSize(400,400)));

    ui->pot->setStyleSheet("background: transparent");

    ui->tempSlider->setValue(50);
    time = 10;
    timer.setInterval(100);
    ui->timer->display(time);

    settingPositionAndTransparentOfitem(ui->tomato, 123, 100, true);
    settingPositionAndTransparentOfitem(ui->tomatoTwo, 260, 100, true);
    settingPositionAndTransparentOfitem(ui->tomatoThree, 367, 100, true);

    connectFollowDrag(ui->tomato, 420, 335, 10, 10);
    connectFollowDrag(ui->tomatoTwo, 420, 335, 10, 10);
    connectFollowDrag(ui->tomatoThree, 420, 335, 10, 10);

    connect(&timer, &QTimer::timeout, this, [this](){
        time--;
        ui->timer->display(time);
        if(time == 0){
            timer.stop();
            ui->sceneFiveContinue->show();
        }
    });

    connect(ui->tomato, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->tomato->hide();
        }
    });

    connect(ui->tomatoTwo, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            this->ui->tomatoTwo->hide();
        }
    });

    connect(ui->tomatoThree, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->pot, x, y)) {
            ui->tomatoThree->hide();
            ui->sceneFiveInstructions->setText(QString("Lovely! Now turn the heat to high to start boiling."));
        }
    });

    connect(ui->tempSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == ui->firstTomatoSlider->maximum()){
            timer.start();
            ui->tempSlider->setEnabled(false);
            ui->pot->setScene(createScene("pot with water.png", QSize(400,400)));
        }
    });

    connect(ui->sceneFiveContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(5);
    });

    // scene 6

    ui->sceneSixContinue->hide();

    ui->sceneSixInstructions->setText(QString("Drag the slider to peel the first tomato."));

    formatText(ui->sceneSixInstructions, font);

    ui->secondTomato->hide();
    ui->thirdTomato->hide();
    ui->secondTomatoSlider->hide();
    ui->thirdTomatoSlider->hide();

    ui->firstTomato->setScene(createScene("boiled tomato.png", QSize(200,200)));
    ui->secondTomato->setScene(createScene("boiled tomato.png", QSize(200,200)));
    ui->thirdTomato->setScene(createScene("boiled tomato.png", QSize(200,200)));
    ui->bowl_2->setScene(createScene("bowl.png", QSize(400,400)));

    ui->bowl_2->setStyleSheet("background: transparent");

    currentIngIndex = 0;

    settingPositionAndTransparentOfitem(ui->firstTomato, 250,80,true);

    connectFollowDrag(ui->firstTomato, 420, 335, 10, 10);
    connectFollowDrag(ui->secondTomato, 420, 335, 10, 10);
    connectFollowDrag(ui->thirdTomato, 420, 335, 10, 10);

    connect(ui->firstTomato, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl_2, x, y)) {
            this->ui->firstTomato->hide();
            this->ui->secondTomato->show();
            this->ui->secondTomatoSlider->show();
            ui->sceneSixInstructions->setText(QString("Drag the slider to peel the second tomato."));
            settingPositionAndTransparentOfitem(ui->secondTomato, 250,80,true);
        }
    });

    connect(ui->secondTomato, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl_2, x, y)) {
            this->ui->secondTomato->hide();
            this->ui->secondTomatoSlider->hide();
            this->ui->thirdTomato->show();
            this->ui->thirdTomatoSlider->show();
            ui->sceneSixInstructions->setText(QString("Drag the slider to peel the third tomato."));
            settingPositionAndTransparentOfitem(ui->thirdTomato, 250,80,true);
        }
    });

    connect(ui->thirdTomato, &DragItem::releasePosition, this, [this](int x, int y){
        if (isInside(ui->bowl_2, x, y)) {
            this->ui->thirdTomato->hide();
            this->ui->thirdTomatoSlider->hide();
            ui->sceneSixInstructions->setText(QString("Perfect! Press the continue button!"));
            ui->bowl_2->setScene(createScene("tomato bowl.png", QSize(400,400)));
            ui->sceneSixContinue->show();
        }
    });

    connect(ui->firstTomatoSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == 50){
            ui->firstTomato->setScene(createScene("tomato with peel.png", QSize(200,200)));
        }

        if(value == ui->firstTomatoSlider->maximum()) {
            ui->firstTomato->setScene(createScene("peeled tomato.png", QSize(200,200)));
            ui->firstTomatoSlider->setEnabled(false);
            ui->firstTomatoSlider->hide();
            ui->sceneSixInstructions->setText(QString("Drag the peeled tomato into the bowl."));
        }
    });

    connect(ui->secondTomatoSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == 50){
            ui->secondTomato->setScene(createScene("tomato with peel.png", QSize(200,200)));
        }

        if(value == ui->secondTomatoSlider->maximum()) {
            ui->secondTomato->setScene(createScene("peeled tomato.png", QSize(200,200)));
            ui->secondTomatoSlider->setEnabled(false);
            ui->secondTomatoSlider->hide();
            ui->sceneSixInstructions->setText(QString("Drag the peeled tomato into the bowl."));
        }
    });

    connect(ui->thirdTomatoSlider, &QSlider::valueChanged, this, [this](int value) {
        if(value == 50){
            ui->thirdTomato->setScene(createScene("tomato with peel.png", QSize(200,200)));
        }

        if(value == ui->thirdTomatoSlider->maximum()) {
            ui->thirdTomato->setScene(createScene("peeled tomato.png", QSize(200,200)));
            ui->thirdTomatoSlider->setEnabled(false);
            ui->thirdTomatoSlider->hide();
        }
    });

    connect(ui->sceneSixContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(6);
    });

    // scene 7

    ui->sceneSevenContinue->hide();

    formatText(ui->sceneSevenLabel, font);
    formatText(ui->sceneSevenInfoBox, font);

    ui->grillChicken->setScene(createScene("flip raw chicken 1.png", QSize(135, 135)));
    ui->grill->setScene(createScene("grill.png", QSize(230, 230)));

    ui->grillChicken->setStyleSheet("background: transparent");
    ui->grill->setStyleSheet("background: transparent");

    ui->grillChicken->setSceneRect(0, 0, 135, 135);
    ui->flipChickenSlider->setRange(1, 7);

    connect(ui->flipChickenSlider, &QSlider::valueChanged, this, [this](int flipValue){
        QString flipGrillPicName;
        int yPos = 0;

        // check the postion for the flipped grilled chicken
        if(flipValue == 1){
            yPos = 0;
            if(chickenFlipReachedTop)
                chickenCounter++;
            chickenFlipReachedTop = false;
            chickenFlipIsFalling = false;
            flipGrillPicName += "1.png";
        }
        else if(flipValue == 7){
            yPos = 120;
            chickenFlipReachedTop = true;
            chickenFlipIsFalling = true;
            flipGrillPicName += "3.png";
        }
        else if(flipValue == 4){
            yPos = 60;
            if(chickenFlipIsFalling){
                flipGrillPicName += "4.png";
            }
            else{
                flipGrillPicName += "2.png";
            }
        }

        // check how cooked the grilled chicken is
        if(chickenCounter == 0){
            flipGrillPicName = "flip raw chicken " + flipGrillPicName;
        }
        else if(chickenCounter == 1){
            flipGrillPicName = "flip cooked chicken " + flipGrillPicName;
        }
        else{
            chickenCounter = 0;
            flipGrillPicName = "grilled chicken.png";
            ui->flipChickenSlider->setEnabled(false);
            ui->sceneSevenLabel->setText("Perfect! Now, press continue.");
            ui->sceneSevenContinue->show();
        }

        // change the picture to the correct grilled chicken
        if(flipValue == 1 || flipValue == 4 || flipValue == 7){
            ui->grillChicken->setScene(createScene(flipGrillPicName, QSize(135, 135)));
            ui->grillChicken->setSceneRect(0, yPos, 135, 135);
        }
    });

    connect(ui->sceneSevenContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(7);
    });

    // scene 8

    ui->sceneEightContinue->hide();

    ui->bowl_3->setScene(createScene("bowl.png", QSize(245, 245)));
    ui->chicken->setScene(createScene("grilled chicken.png", QSize(205, 205)));

    ui->bowl_3->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->chicken, 351, 21, true);

    connect(ui->chicken, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_3, x, y)){
            chickenCounter++;

            ui->bowl_3->setScene(createScene("bowl with chicken " + QString::number(chickenCounter) + ".png", QSize(245, 245)));
            if(chickenCounter == 3){
                chickenCounter = 0;
                ui->chicken->hide();
                ui->sceneEightContinue->show();
                ui->sceneEightLabel->setText("Perfect! Now, let's go add the ingredients.");
            }
        }
    });

    connect(ui->sceneEightContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(8);
    });

    // scene 9

    ui->sceneNineContinue->hide();

    formatText(ui->sceneNineLabel, font);

    QSize ingSize(150, 150);

    ui->bowl_4->setScene(createScene("bowl with chicken 3.png", QSize(250, 250)));
    ui->garlicGingerPaste->setScene(createScene("ginger and garlic paste.png", ingSize));
    ui->spiceMixture->setScene(createScene("spice mixture.png", ingSize));
    ui->dicedIngredients->setScene(createScene("chopped ing 3.png", ingSize));
    ui->tomatoBowl->setScene(createScene("tomato bowl.png", ingSize));

    ui->bowl_4->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->garlicGingerPaste, 310, -42, true);
    settingPositionAndTransparentOfitem(ui->spiceMixture, 325, 130, true);
    settingPositionAndTransparentOfitem(ui->dicedIngredients, -165, 75, true);
    settingPositionAndTransparentOfitem(ui->tomatoBowl, -153, -66, true);

    connectFollowDrag(ui->garlicGingerPaste, 420, 335, 10, 10);
    connectFollowDrag(ui->spiceMixture, 420, 335, 10, 10);
    connectFollowDrag(ui->dicedIngredients, 420, 335, 10, 10);
    connectFollowDrag(ui->tomatoBowl, 420, 335, 10, 10);

    connect(ui->garlicGingerPaste, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_4, x, y)){
            ui->garlicGingerPaste->hide();
        }
    });

    connect(ui->spiceMixture, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_4, x, y)){
            ui->spiceMixture->hide();
        }
    });

    connect(ui->dicedIngredients, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_4, x, y)){
            ui->dicedIngredients->hide();
        }
    });

    connect(ui->tomatoBowl, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->bowl_4, x, y)){
            ui->tomatoBowl->hide();
            ui->bowl_4->setScene(createScene("bowl of ing.png", QSize(250, 250)));
            ui->sceneNineLabel->setText("Perfect! Press continue to prepare the oil.");
            ui->sceneNineContinue->show();
        }
    });

    connect(ui->sceneNineContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(9);
    });

    // scene 10 for level 4

    ui->sceneTenContinue->hide();

    ui->sceneTenInstr->setText("Pour oil into the pan.");

    formatText(ui->sceneTenInstr, font);
    formatText(ui->sceneTenInfoBox, font);

    makeEducationalText(
        ui->oil,ui->sceneTenInfoBox,
        "<p> Mainly obtained via the extensive land border with India in modern times, it is deeply tied to Newari culture. Mustard oil was made in the villages of Nepal and has been passed down for centuries. </p>"
        );

    ui->stoveHeat->hide();

    ui->stove->setScene(createScene("oven closed.png", QSize(400, 400)));
    ui->pan->setScene(createScene("pan.png", QSize(250, 250)));
    ui->oil->setScene(createScene("oil full.png", QSize(250, 250)));

    ui->pan->setStyleSheet("background: transparent");
    ui->stove->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->oil, 268, 206, true);

    connectFollowDrag(ui->oil, 420, 335, 10, 10);

    connect(ui->oil, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->pan, x, y)){
            ui->oil->hide();
            ui->pan->setScene(createScene("pan with oil.png", QSize(200,200)));
            ui->stoveHeat->show();
            ui->sceneTenInstr->setText("Now turn the heat to high and wait for the oil to start smoking.");
        }
    });

    connect(ui->stoveHeat, &QSlider::valueChanged, this, [this](int value) {
        if(value == ui->stoveHeat->maximum()){
            ui->stoveHeat->hide();
            ui->sceneTenInstr->setText("Hit continue to go to the next level.");
            ui->sceneTenContinue->show();
        }
    });

    connect(ui->sceneTenContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(10);
    });

    // scene 11

    ui->sceneElevenContinue->hide();

    ui->sceneElevenInstr->setText("Pour the hot oil over the rest of the ingridents.");

    formatText(ui->sceneElevenInstr, font);

    ui->panAndOil->setScene(createScene("pan with oil.png", QSize(200, 200)));
    ui->combinedIng->setScene(createScene("bowl of ing.png", QSize(250, 250)));

    ui->combinedIng->setStyleSheet("background: transparent");

    settingPositionAndTransparentOfitem(ui->panAndOil, 268, 206, true);

    connectFollowDrag(ui->oil, 420, 335, 10, 10);

    connect(ui->panAndOil, &DragItem::releasePosition, this, [this](int x, int y){
        if(isInside(ui->combinedIng, x, y)){
            ui->panAndOil->hide();
            ui->sceneElevenContinue->show();
        }
    });

    connect(ui->sceneElevenContinue, &QPushButton::clicked, this, [this](){
        ui->levelFourScenes->setCurrentIndex(11);
    });

    // scene 12

    ui->sceneTwelveLabel->setText("You have completed the dish!.");
    ui->sceneTweleveInfo->setText("This dish is usually eaten during festivals and special occasions and is usually accompanied by many other dishes.");

    formatText(ui->sceneTwelveLabel, font);
    formatText(ui->sceneTweleveInfo, font);

    ui->choila->setScene(createScene("Newari Chicken Choila.jpg", QSize(250, 250)));

    connect(ui->sceneTwelveContinue, &QPushButton::clicked, this, [this](){emit goBackToMenu();});
}

///@brief deconstructor for level 4
LevelFour::~LevelFour()
{
    delete ui;
}

///@brief create image object
///@param filename: image to be used
///@param size of image
QGraphicsScene* LevelFour::createScene(QString fileName, QSize sceneSize){
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
bool LevelFour::isInside(QWidget *target, int x, int y) const
{
    // widget rect in parent coordinates
    QRect targetRect(target->pos(), target->size());
    return targetRect.contains(QPoint(x, y));
}

///@brief redraw image to have it follow the mouse as it drags
///@param *item: image (QGraphicsView) to be dragged
///@param offsetX: offset for x so the image follows right below mouse
///@param offsetY: offset for y so the image follows right below mouse
void LevelFour::connectFollowDrag(DragItem *item,int offsetX,int offsetY,int rectW,int rectH)
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
void LevelFour::createBackground(QGraphicsView* backgroundView, QString backgroundFileName){
    backgroundView->setScene(createScene(backgroundFileName, QSize(800, 600)));
    backgroundView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    backgroundView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

///@brief This method is used to format the text of each label in the level
/// @param label: The label that will be displayed
/// @param font: The formatting of the text
void LevelFour::formatText(QLabel* label, QFont font){
    label->setFont(font);
    label->setWordWrap(true);
    label->setStyleSheet("color: white;");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

///@brief create text for educational background for an ingredient
void LevelFour::makeEducationalText(DragItem *item, QLabel *label, const QString &info)
{
    item->setInfoText(info);
    connect(item, &DragItem::displayNewInfo,
            this, [label](const QString &text) {
                label->setText(text);
            });
}

///@brief This method sets up the postion of the item in the scene and sets the items background to be transparent if needed
void LevelFour::settingPositionAndTransparentOfitem(DragItem* item, int x, int y, bool isTransparent) {
    if(isTransparent) {
        item->setStyleSheet("background: transparent");
    }
    item->setSceneRect(x, y, 10, 10);
}
