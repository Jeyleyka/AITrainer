#include "AIResponseTest.h"

void AIResponseTest::warmUpTest() {
    AIModelManager manager;

    QSignalSpy warmUpSpy(&manager, &AIModelManager::warmUpFinished);

    manager.warmUpModel();

    manager.sendPrompt("Hello");

    QSignalSpy chunkSpy(&manager, &AIModelManager::chunkReceived);
    QSignalSpy finishedSpy(&manager, &AIModelManager::finished);

    QVERIFY(chunkSpy.wait(5000));
    QVERIFY(finishedSpy.wait(15000));
    QTRY_VERIFY_WITH_TIMEOUT(warmUpSpy.count() == 1, 15000);

}

QTEST_MAIN(AIResponseTest)
#include "AIResponseTest.moc"
