/// @author Siesia Makaafi, Kennedy Zhang, Carson Kawabata, Priyasna Shrestha
/// @class CS3505
/// @name A9: Educational App
/// @brief header file for main window

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///@brief constructor for main window
    MainWindow(QWidget *parent = nullptr);
    ///@brief destructor for main window
    ~MainWindow();

private:
    // private variable for main window
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
