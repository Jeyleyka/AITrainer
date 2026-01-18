#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QWidget>

class ClickableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClickableWidget(const QString& filePath, const QString& text,  QWidget *parent = nullptr);

    void setActive(bool value);
    QString getChoice();

    bool isActive() const;


signals:
    void clicked(const QString& returnValue);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QString text_m;

    bool active = false;

    void updateStyle();
};


#endif // CLICKABLEWIDGET_H
