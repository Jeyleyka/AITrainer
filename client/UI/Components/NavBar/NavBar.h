#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>

#include "../NavBarItem/NavBarItem.h"

class NavBar : public QWidget
{
    Q_OBJECT
public:
    explicit NavBar(QWidget *parent = nullptr);

signals:
};

#endif // NAVBAR_H
