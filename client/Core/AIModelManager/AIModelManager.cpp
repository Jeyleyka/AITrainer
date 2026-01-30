#include "AIModelManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>
#include <QTextCursor>
#include <QDebug>

AIModelManager::AIModelManager(QObject *parent)
    : QObject{parent}
{
    this->manager = new QNetworkAccessManager(this);
}

void AIModelManager::warmUpModel()
{
    QJsonObject json{
        {"prompt",
         R"("Привет")"},
    };

    QNetworkRequest request(QUrl("http://0.0.0.0:8080/prompt"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    auto reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        emit warmUpFinished();
        qDebug() << "warmUp finished\n";
    });
}

void AIModelManager::sendPrompt(const QString& prompt) {
    if (prompt.isEmpty()) return;

    emit promptProcessed();

    QUrl url("http://localhost:8080/prompt");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Формируем JSON для запроса
    QJsonObject json;
    json["prompt"] = prompt;

    QJsonDocument doc(json);

    this->currentReply = manager->post(request, doc.toJson());
    connect(this->currentReply, &QNetworkReply::readyRead, this, &AIModelManager::handleReplyReadyRead);
    connect(this->currentReply, &QNetworkReply::finished, this, &AIModelManager::handleReplyFinished);
}

void AIModelManager::handleReplyReadyRead() {
    QByteArray chunk = this->currentReply->readAll();
    QList<QByteArray> lines = chunk.split('\n');

    for (const QByteArray& line : lines) {
        if (line.trimmed().isEmpty()) continue;

        QJsonDocument doc = QJsonDocument::fromJson(line);
        if (!doc.isObject()) continue;

        QJsonObject obj = doc.object();
        if (obj.contains("response")) {
            QString text = obj["response"].toString();
            emit chunkReceived(text);
        }

        if (obj.contains("done") && obj["done"].toBool()) {
            // Генерация завершена
            qDebug() << "Response finished.";
        }
    }
}

void AIModelManager::handleReplyFinished() {
    this->currentReply->deleteLater();
    emit finished();
}
