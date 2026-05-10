/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for level selection menu

#ifndef LEVELSMENU_H
#define LEVELSMENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QSize>
#include <QString>

using std::string;

namespace Ui {
class LevelsMenu;
}
///@brief This class will create and handle the logic for Levels Menu of the educational app
class LevelsMenu : public QWidget
{
    Q_OBJECT

public:
    ///@brief constructor of Levels Menu of the educational app
    explicit LevelsMenu(QWidget *parent = nullptr);
    ///@brief destructor of Levels Menu of the educational app
    ~LevelsMenu();

signals:
    ///@brief signal emitted when user chooses Level One
    void openLevelOne();
    ///@brief signal emitted when user chooses Level Two
    void openLevelTwo();
    ///@brief signal emitted when user chooses Level Three
    void openLevelThree();
    ///@brief signal emitted when user chooses Level Four
    void openLevelFour();

public slots:
    ///@brief slot that receives and handles the signal when level is picked
    void levelSelected(int x, int y);


private:
    ///@brief create image object
    ///@param filename: image to be used
    ///@param size of image
    QGraphicsScene* createScene(QString fileName, QSize sceneSize);

    // all priavte varibles used for the level menu
    Ui::LevelsMenu *ui;
    int levelNum = 0;
    std::vector<QString> listOfKitchenAppliances = {"pot", "fryer", "oven", "grill"};
    bool potLocked = false;
    bool airFryerLocked = true;
    bool ovenLocked = true;
    bool grillLocked = true;
};

#endif // LEVELSMENU_H
