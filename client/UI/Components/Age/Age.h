#ifndef AGE_H
#define AGE_H

#include "../StepPage/StepPage.h"

class Age : public StepPage
{
    Q_OBJECT
public:
    explicit Age(QWidget *parent = nullptr);
};

#endif // AGE_H
