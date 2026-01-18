#ifndef GENDER_H
#define GENDER_H

#include "../StepPage/StepPage.h"

class Gender : public StepPage
{
    Q_OBJECT
public:
    explicit Gender(QWidget *parent = nullptr);
};

#endif // GENDER_H
