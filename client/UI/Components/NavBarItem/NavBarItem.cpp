#include "NavBarItem.h"

NavBarItem::NavBarItem(const QString& filePath, const QString& hoverPath, const QString& string, QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QPushButton *btn = new QPushButton();
    btn->setFixedSize(QSize(52,52));
    btn->setStyleSheet(QString(R"(
        QPushButton {
            border: none;
            background: transparent;
            image: url(%1)
        }
        QPushButton:hover {
            image: url(%2);
        }
    )").arg(filePath, hoverPath));

    QLabel* label = new QLabel(string);
    label->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500");
    label->setAlignment(Qt::AlignHCenter);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch(0);

    mainLayout->addWidget(btn);
    mainLayout->addWidget(label);
}
