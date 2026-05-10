/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for starting page

#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    ///@brief constructor for starting page
    explicit StartPage(QWidget *parent = nullptr);
    ///@brief deconstructor for starting page
    ~StartPage();

public slots:
    ///@brief emits signal to start game when button is pressed
    void startGame();

signals:
    ///@brief signal to be emitted to show levels menu
    void gameHasStart();

private:
    //private variable for starting page
    Ui::StartPage *ui;
};

#endif // STARTPAGE_H
