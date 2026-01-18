#ifndef PRSETTINGUP_H
#define PRSETTINGUP_H

#include <QWidget>
#include <QString>

#include "../../../Core/AIModelManager/AIModelManager.h"

struct UserChoices {
    QString gender;
    QString aim;
    QString age;
    QString height;
    QString weight;
    QString format;
    QString frequency;
    QString eatingType;
};

class QStackedWidget;
class QPushButton;
class StepPage;

class PrSettingUp : public QWidget
{
    Q_OBJECT
public:
    explicit PrSettingUp(QWidget *parent = nullptr);

private:
    AIModelManager* aiManager;
    QStackedWidget* m_stack;
    QPushButton* m_next;
    UserChoices m_userChoices;
};

#endif // PRSETTINGUP_H
