#include "ClickableWidget.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ClickableWidget::ClickableWidget(const QString& filePath, const QString& text, QWidget* parent)
    : QWidget(parent), text_m(text)
{
    setFixedSize(400, 250);
    setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout* containerLayout = new QVBoxLayout(this);
    containerLayout->setAlignment(Qt::AlignCenter);
    containerLayout->setContentsMargins(0, 50, 0, 20);
    containerLayout->setSpacing(15);

    QPushButton* btnIcon = new QPushButton(this);
    btnIcon->setIcon(QIcon(filePath));
    btnIcon->setIconSize(QSize(120, 120));
    btnIcon->setFixedSize(120,120);
    btnIcon->setStyleSheet("border: none; background-color: transparent");
    btnIcon->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QLabel* title = new QLabel(text, this);
    title->setStyleSheet("font-size: 19px; font-weight: 700; color: #fff; border: none; background-color: transparent;");
    title->setAlignment(Qt::AlignHCenter);
    title->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    containerLayout->addWidget(btnIcon, Qt::AlignHCenter);
    containerLayout->addWidget(title);

    updateStyle();
}

void ClickableWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        active = !active;
        updateStyle();
        emit clicked(text_m);
    }
}

void ClickableWidget::setActive(bool value)
{
    active = value;
    updateStyle();
}

QString ClickableWidget::getChoice() {
    return text_m;
}

bool ClickableWidget::isActive() const
{
    return active;
}

void ClickableWidget::updateStyle()
{
    if (active) {
        setStyleSheet(R"(
            background-color: #505050;
            border: 2px solid #00FF7F;
            border-radius: 12px;
        )");
    } else {
        setStyleSheet(R"(
            QWidget {
                border: 1px solid gray;
                border-radius: 12px;
            }
            QWidget:hover {
            background-color: #2E2E2E;
            border-radius: 12px;
            }
        )");
    }
}
