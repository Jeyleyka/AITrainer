#ifndef AIMODELMANAGER_H
#define AIMODELMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <thread>
#include <atomic>

class AIModelManager : public QObject
{
    Q_OBJECT
public:
    explicit AIModelManager(QObject *parent = nullptr);

    void sendPrompt(const QString& prompt);
    void warmUpModel();

signals:
    void chunkReceived(const QString& text);
    void promptProcessed();
    void warmUpFinished();
    void finished();

private slots:

    void handleReplyReadyRead();
    void handleReplyFinished();

private:
    QNetworkAccessManager* manager;

    QNetworkReply* currentReply;

    std::thread worker;
    std::atomic<bool> stop;
};

#endif // AIMODELMANAGER_H
