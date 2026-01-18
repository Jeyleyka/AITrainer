#include "NavBar.h"
#include <QString>
#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>
#include <QPixmap>

NavBar::NavBar(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground, true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(100);
    setAutoFillBackground(true);
    setStyleSheet("background-color: #0D0D0D;");


    QHBoxLayout* containerLayout = new QHBoxLayout();
    containerLayout->setContentsMargins(20, 10, 20, 10);
    containerLayout->setSpacing(30);

    QWidget *line = new QWidget(this);
    line->setFixedHeight(1);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setStyleSheet("background-color: #808080;");

    NavBarItem* timer = new NavBarItem(":/icons/timer.png", ":/icons/timer-hover.png", "Classic", this);
    NavBarItem* discover = new NavBarItem(":/icons/compass-icon.png", ":/icons/discover-hover.png", "Discover", this);
    NavBarItem* personal = new NavBarItem(":/icons/to-do-list.png", ":/icons/personal-hover.png", "Personal", this);
    NavBarItem* daily = new NavBarItem(":/icons/calendar.png", ":/icons/calendar-hover.png", "Daily", this);
    NavBarItem* me = new NavBarItem(":/icons/user.png", ":/icons/user-hover.png",  "Me", this);

    containerLayout->addStretch();
    containerLayout->addWidget(timer);
    containerLayout->addWidget(discover);
    containerLayout->addWidget(personal);
    containerLayout->addWidget(daily);
    containerLayout->addWidget(me);
    containerLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch(0);

    mainLayout->addWidget(line);
    mainLayout->addLayout(containerLayout);

}
