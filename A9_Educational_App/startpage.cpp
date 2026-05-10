/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief source file for starting page of game

#include "startpage.h"
#include "ui_startpage.h"

#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QFont>

///@brief constructor for starting page
StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);

    QGraphicsScene *sceneFlags = new QGraphicsScene(this);

    // Flags image
    QPixmap pixmapFlags("Untitled design.jpg");
    QSize newSize(800, 600);
    QPixmap scaledPixmapFlags = pixmapFlags.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *itemFlags = new QGraphicsPixmapItem(scaledPixmapFlags);
    sceneFlags->addItem(itemFlags);
    ui->flags->setScene(sceneFlags);

    QFont font;
    font.setFamily("SimSun");
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);

    ui->startButton->setFont(font);

    connect(ui->startButton, &QPushButton::clicked, this, &StartPage::startGame);
}

//@brief emits signal to start game when button is pressed
void StartPage::startGame(){
    emit gameHasStart();
}

///@brief deconstructor for starting page
StartPage::~StartPage()
{
    delete ui;
}
