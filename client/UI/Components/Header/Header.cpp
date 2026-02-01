#include "Header.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>
#include <QTextCursor>
#include <QDebug>
#include <QThread>
#include <QDebug>

Header::Header(QWidget* parent)
    : QWidget(parent)
{
    this->aiManager = new AIModelManager();

    aiManager->checkHealth();

    if (aiManager->isBackendAvailable())
        aiManager->warmUpModel();
    else
        qDebug() << "Server unavailable";

    QVBoxLayout* layout = new QVBoxLayout(this);

    input = new QLineEdit();
    sendButton = new QPushButton("Send");
    output = new QTextEdit();
    output->setReadOnly(true);

    layout->addWidget(input);
    layout->addWidget(sendButton);
    layout->addWidget(output);

    setLayout(layout);

    connect(this->aiManager, &AIModelManager::promptProcessed, this, [this]() {
        input->clear();
        output->clear();
        output->moveCursor(QTextCursor::End);
    });

    connect(this->aiManager, &AIModelManager::chunkReceived, this, [this](const QString& text) {
        output->insertPlainText(text);
    });

    connect(this->sendButton, &QPushButton::clicked, this, [this] {
        this->aiManager->sendPrompt(this->input->text());
    });

    connect(this->aiManager, &AIModelManager::warmUpFinished, this, [] {
        qDebug() << "warmUp is finsihed\n";
    });
}
