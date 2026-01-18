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
        {"model", "mistral:latest"},
        {"stream", false},
        {"keep_alive", "10m"},
        {"prompt",
         R"([INST]
            Ты инициализируешься. И все последующие ответы давай только на русском языке. Ответ на любом другом языке является ошибкой
            Ответь словом "OK".
            [/INST])"},
        {"temperature", 0.0}
    };

    QNetworkRequest request(QUrl("http://127.0.0.1:11434/api/generate"));
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

    QUrl url("http://127.0.0.1:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Формируем JSON для запроса
    QJsonObject json;
    json["model"] = "mistral:7b-instruct-q4_K_M";
    json["prompt"] = prompt;
    json["stream"] = true;
    json["num_predict"] = 200;
    json["temperature"] = 0.7;
    json["top_p"] = 0.9;

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
