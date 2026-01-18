#include "Aim.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QVBoxLayout>
#include <QLabel>

Aim::Aim(QWidget *parent)
    : StepPage{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Aim", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* loseWeigh = new ClickableWidget(":/icons/weight.png", "loose weight");
    ClickableWidget* gainMuscle = new ClickableWidget(":/icons/muscle.png", "gain muscle");
    ClickableWidget* keepingFit = new ClickableWidget(":/icons/better-health.png", "keeping fit");

    cards << loseWeigh << gainMuscle << keepingFit;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(loseWeigh);
    cardsLayout->addWidget(gainMuscle);
    cardsLayout->addWidget(keepingFit);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
