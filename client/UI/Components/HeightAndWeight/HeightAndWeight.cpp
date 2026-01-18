#include "HeightAndWeight.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

HeightAndWeight::HeightAndWeight(QWidget* parent)
    : StepPage(parent)
{
    setupUI();
    connectSignals();
}

void HeightAndWeight::setupUI()
{
    setStyleSheet(R"(
        QWidget { background-color: #1c1c1c; color: #fff; font-family: Arial; }
        QSlider::groove:horizontal { height: 8px; background: #333; border-radius: 4px; }
        QSlider::handle:horizontal { width: 20px; background: #04aaff; border-radius: 10px; margin: -6px 0; }
        QPushButton { background-color: #04aaff; border-radius: 12px; color: #fff; font-weight: bold; }
        QPushButton:hover { background-color: #0487fb; }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20,20,20,20);
    mainLayout->setSpacing(30);

    QLabel* titleHeight = new QLabel("Height", this);
    titleHeight->setAlignment(Qt::AlignCenter);
    titleHeight->setStyleSheet("font-size: 18px; font-weight: 700;");

    m_heightLabel = new QLabel(QString::number(m_height) + " cm", this);
    m_heightLabel->setAlignment(Qt::AlignCenter);
    m_heightLabel->setStyleSheet("font-size: 28px; font-weight: 800; color: #04aaff;");

    m_heightSlider = new QSlider(Qt::Horizontal, this);
    m_heightSlider->setRange(100, 220);
    m_heightSlider->setValue(m_height);

    m_heightMinusBtn = new QPushButton("-", this);
    m_heightPlusBtn = new QPushButton("+", this);
    m_heightMinusBtn->setFixedSize(30,30);
    m_heightPlusBtn->setFixedSize(30,30);

    QHBoxLayout* heightControl = new QHBoxLayout();
    heightControl->addWidget(m_heightMinusBtn);
    heightControl->addWidget(m_heightSlider);
    heightControl->addWidget(m_heightPlusBtn);

    mainLayout->addWidget(titleHeight);
    mainLayout->addWidget(m_heightLabel);
    mainLayout->addLayout(heightControl);

    QLabel* titleWeight = new QLabel("Weight", this);
    titleWeight->setAlignment(Qt::AlignCenter);
    titleWeight->setStyleSheet("font-size: 18px; font-weight: 700;");

    m_weightLabel = new QLabel(QString::number(m_weight) + " kg", this);
    m_weightLabel->setAlignment(Qt::AlignCenter);
    m_weightLabel->setStyleSheet("font-size: 28px; font-weight: 800; color: #04aaff;");

    m_weightSlider = new QSlider(Qt::Horizontal, this);
    m_weightSlider->setRange(30, 150);
    m_weightSlider->setValue(m_weight);

    m_weightMinusBtn = new QPushButton("-", this);
    m_weightPlusBtn = new QPushButton("+", this);
    m_weightMinusBtn->setFixedSize(30,30);
    m_weightPlusBtn->setFixedSize(30,30);

    QHBoxLayout* weightControl = new QHBoxLayout();
    weightControl->addWidget(m_weightMinusBtn);
    weightControl->addWidget(m_weightSlider);
    weightControl->addWidget(m_weightPlusBtn);

    mainLayout->addWidget(titleWeight);
    mainLayout->addWidget(m_weightLabel);
    mainLayout->addLayout(weightControl);
}

void HeightAndWeight::connectSignals()
{
    connect(m_heightSlider, &QSlider::valueChanged, this, [this](int val){
        m_height = val;
        m_heightLabel->setText(QString::number(val) + " cm");
        m_hw.height = val;
        emit completed(m_hw);
    });

    connect(m_heightMinusBtn, &QPushButton::clicked, this, [this](){
        if (m_height > m_heightSlider->minimum()) {
            m_heightSlider->blockSignals(true);
            m_heightSlider->setValue(m_height - 1);
            m_heightSlider->blockSignals(false);
            m_height = m_heightSlider->value();
            m_heightLabel->setText(QString::number(m_height) + " cm");
            m_hw.height = m_height;
            emit completed(m_hw);
        }
    });

    connect(m_heightPlusBtn, &QPushButton::clicked, this, [this](){
        if (m_height < m_heightSlider->maximum()) {
            m_heightSlider->blockSignals(true);
            m_heightSlider->setValue(m_height + 1);
            m_heightSlider->blockSignals(false);
            m_height = m_heightSlider->value();
            m_heightLabel->setText(QString::number(m_height) + " cm");
            m_hw.height = m_height;
            emit completed(m_hw);
        }
    });

    connect(m_weightSlider, &QSlider::valueChanged, this, [this](int val){
        m_weight = val;
        m_weightLabel->setText(QString::number(val) + " kg");
        m_hw.weight = val;
        emit completed(m_hw);
    });

    connect(m_weightMinusBtn, &QPushButton::clicked, this, [this](){
        if (m_weight > m_weightSlider->minimum()) {
            m_weightSlider->blockSignals(true);
            m_weightSlider->setValue(m_weight - 1);
            m_weightSlider->blockSignals(false);
            m_weight = m_weightSlider->value();
            m_weightLabel->setText(QString::number(m_weight) + " kg");
            m_hw.weight = m_weight;
            emit completed(m_hw);
        }
    });

    connect(m_weightPlusBtn, &QPushButton::clicked, this, [this](){
        if (m_weight < m_weightSlider->maximum()) {
            m_weightSlider->blockSignals(true);
            m_weightSlider->setValue(m_weight + 1);
            m_weightSlider->blockSignals(false);
            m_weight = m_weightSlider->value();
            m_weightLabel->setText(QString::number(m_weight) + " kg");
            m_hw.weight = m_weight;
            emit completed(m_hw);
        }
    });
}
