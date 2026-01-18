#include "EatingType.h"

#include "../ClickableWidget/ClickableWidget.h"
#include <QVBoxLayout>
#include <QLabel>

EatingType::EatingType(QWidget* parent)
    :   StepPage(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Eating type", this);
    title->setStyleSheet("font-size: 16px; font-weight: 600; color: #fff");
    title->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* cardsLayout = new QHBoxLayout();

    QList<ClickableWidget*> cards;

    ClickableWidget* normal = new ClickableWidget(":/icons/steak.png", "Normal");
    ClickableWidget* vegetarian = new ClickableWidget(":/icons/vegan.png", "vegetarian");
    ClickableWidget* halal = new ClickableWidget(":/icons/halal.png", "Halal");

    cards << normal << vegetarian << halal;

    for (auto card : cards) {
        connect(card, &ClickableWidget::clicked, this, [=]() {
            for (auto c : cards)
                c->setActive(c == card);

            emit completed(card->getChoice());
        });
    }

    cardsLayout->addWidget(normal);
    cardsLayout->addWidget(vegetarian);
    cardsLayout->addWidget(halal);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    cardsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(cardsLayout);
}
