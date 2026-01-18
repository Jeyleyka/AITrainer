#ifndef STEPPAGE_H
#define STEPPAGE_H

#include <QWidget>

class StepPage : public QWidget
{
    Q_OBJECT
public:
    explicit StepPage(QWidget *parent = nullptr);

signals:
    void completed(const QString& choice);
};

#endif // STEPPAGE_H
