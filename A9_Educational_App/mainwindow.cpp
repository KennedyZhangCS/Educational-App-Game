/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief source file for handling which ui window shows using a QStackedWidget

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelsmenu.h"
#include "startpage.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"

#include <QGraphicsPixmapItem>
#include <QStackedWidget>
#include <QFont>
#include <QVBoxLayout>

///@brief constructor for main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->startPage, &StartPage::gameHasStart, this, [this](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->levelOne, &LevelOne::goBackToMenu, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->levelTwo, &LevelTwo::goBackToMenu, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->levelThree, &LevelThree::goBackToMenu, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->levelFour, &LevelFour::goBackToMenu, this, [this](){ui->stackedWidget->setCurrentIndex(1);});

    connect(ui->levelsMenu, &LevelsMenu::openLevelOne, this, [this](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->levelsMenu, &LevelsMenu::openLevelTwo, this, [this](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->levelsMenu, &LevelsMenu::openLevelThree, this, [this](){
        ui->stackedWidget->setCurrentIndex(4);
    });
    connect(ui->levelsMenu, &LevelsMenu::openLevelFour, this, [this](){
        ui->stackedWidget->setCurrentIndex(5);
    });
    setFixedSize(800, 600);
}

///@brief destructor for main window
MainWindow::~MainWindow()
{
    delete ui;
}
