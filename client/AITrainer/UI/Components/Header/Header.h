#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QTimer>

#include "../../../Core/AIModelManager/AIModelManager.h"

class Header : public QWidget
{
    Q_OBJECT
public:
    Header(QWidget* parent = nullptr);

private slots:

private:
    AIModelManager* aiManager;

    QLineEdit* input;
    QPushButton* sendButton;
    QTextEdit* output;

    QTimer* timer;
};

#endif // HEADER_H
