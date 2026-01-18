#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Components/Header/Header.h"
#include "../Components/NavBar/NavBar.h"
// #include "../Components/Gender/Gender.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Header* header;
    NavBar* navbar;
    // Gender* gender;

    QVBoxLayout* layout;
};
#endif // MAINWINDOW_H
