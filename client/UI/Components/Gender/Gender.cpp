#include "Gender.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QList>
#include <QVBoxLayout>
#include <QLabel>

Gender::Gender(QWidget *parent)
    : StepPage{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Gender", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* man = new ClickableWidget(":/icons/young-boy.png", "man");
    ClickableWidget* woman = new ClickableWidget(":/icons/woman.png", "woman");

    cards << man << woman;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(man);
    cardsLayout->addWidget(woman);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
