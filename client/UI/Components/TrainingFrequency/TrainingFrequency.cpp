#include "TrainingFrequency.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QVBoxLayout>
#include <QLabel>

TrainingFrequency::TrainingFrequency(QWidget* parent)
    : StepPage(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Training frequency per week", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* two = new ClickableWidget(":/icons/2.png", "2 times");
    ClickableWidget* three = new ClickableWidget(":/icons/3.png", "3 times");
    ClickableWidget* fourFive = new ClickableWidget(":/icons/puzzle.png", "4-5 times");

    cards << two << three << fourFive;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(two);
    cardsLayout->addWidget(three);
    cardsLayout->addWidget(fourFive);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
