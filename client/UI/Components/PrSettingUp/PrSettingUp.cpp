#include "PrSettingUp.h"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "../HeightAndWeight/HeightAndWeight.h"
#include "../Gender/Gender.h"
#include "../Aim/Aim.h"
#include "../Age/Age.h"
#include "../TrainingFormat/TrainingFormat.h"
#include "../TrainingFrequency/TrainingFrequency.h"
#include "../EatingType/EatingType.h"
#include <QString>

PrSettingUp::PrSettingUp(QWidget *parent)
    : QWidget{parent}
{
    setStyleSheet("background-color: #000");
    setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    aiManager = new AIModelManager();

    aiManager->warmUpModel();

    QStackedWidget* stack = new QStackedWidget(this);

    Gender* gender = new Gender(this);
    Aim* aim = new Aim(this);
    Age* age = new Age(this);
    HeightAndWeight* hAndW = new HeightAndWeight(this);
    TrainingFormat* format = new TrainingFormat(this);
    TrainingFrequency* frequency = new TrainingFrequency(this);
    EatingType* eType = new EatingType(this);

    stack->addWidget(gender);
    stack->addWidget(aim);
    stack->addWidget(age);
    stack->addWidget(hAndW);
    stack->addWidget(format);
    stack->addWidget(frequency);
    stack->addWidget(eType);

    stack->setCurrentIndex(0);

    m_next = new QPushButton("next", this);
    m_next->setStyleSheet("QPushButton{border-radius: 10px; background-color: #01417a; color: #fff; font-size: 16px; font-weight: 600}"
                        "QPushButton:hover {background-color: #0487fb}");
    m_next->setFixedSize(150, 35);
    m_next->hide();

    for (int i = 0; i < stack->count(); ++i) {
        StepPage* page = qobject_cast<StepPage*>(stack->widget(i));

        if (!page) continue;

        connect(page, &StepPage::completed, this, [page, this](const QString& choice) {
            if (qobject_cast<Gender*>(page)) {
                m_userChoices.gender = choice;
            } else if (qobject_cast<Aim*>(page)) {
                m_userChoices.aim = choice;
            } else if (qobject_cast<Age*>(page)) {
                m_userChoices.age = choice;
            } else if (qobject_cast<TrainingFormat*>(page)) {
                m_userChoices.format = choice;
            } else if (qobject_cast<TrainingFrequency*>(page)) {
                m_userChoices.frequency = choice;
            } else if (qobject_cast<EatingType*>(page)) {
                m_userChoices.eatingType = choice;
            }

            m_next->setVisible(true);
        });

        connect(hAndW, &HeightAndWeight::completed, this, [this](const HeightWeight& hw){
            m_userChoices.height = QString::number(hw.height);
            m_userChoices.weight = QString::number(hw.weight);

            m_next->setVisible(true);
        });
    }

    connect(m_next, &QPushButton::clicked, this, [stack, this] {
        int index = stack->currentIndex();

        if (index + 1 < stack->count())
            stack->setCurrentIndex(index + 1);

        m_next->hide();

        qDebug() << m_userChoices.gender << m_userChoices.aim << m_userChoices.age << m_userChoices.height << m_userChoices.weight <<
            m_userChoices.format << m_userChoices.frequency << m_userChoices.eatingType;
    });

    QString promptTemplate = R"(
Ты – персональный фитнес-тренер и диетолог. Твоя задача – на основе данных пользователя составить индивидуальный план тренировок и рассчитать необходимое количество калорий в день. Ответ должен быть максимально точным, понятным и структурированным.

Данные пользователя:
- Пол: %1
- Цель: %2
- Возраст: %3 лет
- Рост: %4 см
- Вес: %5 кг
- Формат тренировок: %6
- Желаемая частота тренировок: %7 раз в неделю
- Тип питания: %8

Твоя задача:
1. Рассчитать суточную норму калорий (учитывая цель: похудение, поддержание веса или набор массы).
2. Составить план тренировок на неделю с подробным описанием каждого дня: упражнения, подходы, повторения, время кардио.
3. Дать рекомендации по питанию (например, распределение белков, жиров и углеводов), чтобы поддерживать цель пользователя.
4. Ответ выдавай в структурированном виде, легко читаемом:
   - Сначала — суточная калорийность и макронутриенты.
   - Затем — план тренировок по дням.
   - В конце — дополнительные советы и рекомендации.

Обязательные условия:
- Ответ давай на русском языке.
- Используй конкретные числа и рекомендации, не расплывчато.
- План тренировок должен соответствовать указанной частоте и формату тренировок.
)";

    QString userPrompt = promptTemplate.arg(
        m_userChoices.gender,
        m_userChoices.aim,
        m_userChoices.age,
        m_userChoices.height,
        m_userChoices.weight,
        m_userChoices.format,
        m_userChoices.frequency,
        m_userChoices.eatingType
        );

    aiManager->sendPrompt(userPrompt);

    connect(this->aiManager, &AIModelManager::chunkReceived, this, [this](const QString& text) {
        qDebug() << text;
    });

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(stack);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(m_next, 0, Qt::AlignHCenter);
    mainLayout->addStretch();
}
