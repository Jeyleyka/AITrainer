#include "Age.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QVBoxLayout>
#include <QLabel>

Age::Age(QWidget *parent)
    : StepPage{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Age", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* upTo18 = new ClickableWidget(":/icons/children.png", "up to 18");
    ClickableWidget* middle = new ClickableWidget(":/icons/middle.png", "18-30");
    ClickableWidget* adult = new ClickableWidget(":/icons/adult.png", "31-45");
    ClickableWidget* elder = new ClickableWidget(":/icons/elder.png", "46+");

    cards << upTo18 << middle << adult << elder;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(upTo18);
    cardsLayout->addWidget(middle);
    cardsLayout->addWidget(adult);
    cardsLayout->addWidget(elder);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
