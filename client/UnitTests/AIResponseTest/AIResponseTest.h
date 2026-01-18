#ifndef AIRESPONSETEST_H
#define AIRESPONSETEST_H

#include <QObject>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

#include "../../Core/AIModelManager/AIModelManager.h"

class AIResponseTest : public QObject
{
    Q_OBJECT

private slots:
    void warmUpTest();
};

#endif // AIRESPONSETEST_H
