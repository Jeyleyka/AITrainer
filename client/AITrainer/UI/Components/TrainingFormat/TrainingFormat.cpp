#include "TrainingFormat.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QList>
#include <QVBoxLayout>
#include <QLabel>

TrainingFormat::TrainingFormat(QWidget* parent)
    : StepPage(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Format of training", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* home = new ClickableWidget(":/icons/house.png", "at home");
    ClickableWidget* gym = new ClickableWidget(":/icons/gym.png", "at the gym");

    cards << home << gym;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(home);
    cardsLayout->addWidget(gym);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
