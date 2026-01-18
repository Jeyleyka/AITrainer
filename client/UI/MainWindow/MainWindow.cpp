#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->showMaximized();
    QWidget* central = new QWidget(this);
    // central->setStyleSheet("background-color: #000");
    QVBoxLayout* layout = new QVBoxLayout(central);

    this->header = new Header(this);
    layout->addWidget(this->header);

    // gender = new Gender(this);
    // layout->addWidget(gender);
    layout->addStretch();

    navbar = new NavBar(this);
    layout->addWidget(this->navbar);

    layout->addStretch();
    central->setLayout(layout);
    setCentralWidget(central);
}

MainWindow::~MainWindow() {}
