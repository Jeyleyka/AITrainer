#ifndef NAVBARITEM_H
#define NAVBARITEM_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class NavBarItem : public QWidget
{
    Q_OBJECT
public:
    explicit NavBarItem(const QString& filePath, const QString& hoverPath, const QString& string, QWidget *parent = nullptr);

signals:
};

#endif // NAVBARITEM_H
