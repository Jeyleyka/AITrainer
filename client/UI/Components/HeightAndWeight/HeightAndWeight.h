#ifndef HEIGHTANDWEIGHT_H
#define HEIGHTANDWEIGHT_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QLabel>

#include "../StepPage/StepPage.h"
#include "../HeightWeight.h"

class HeightAndWeight : public StepPage
{
    Q_OBJECT
public:
    explicit HeightAndWeight(QWidget* parent = nullptr);

signals:
    void completed(const HeightWeight& hw);

private:
    void setupUI();
    void connectSignals();

    // --- height
    QSlider* m_heightSlider;
    QPushButton* m_heightMinusBtn;
    QPushButton* m_heightPlusBtn;
    QLabel* m_heightLabel;
    int m_height = 180;

    // --- weight
    QSlider* m_weightSlider;
    QPushButton* m_weightMinusBtn;
    QPushButton* m_weightPlusBtn;
    QLabel* m_weightLabel;
    int m_weight = 70;

    HeightWeight m_hw; // структура хранит текущие значения
};

#endif // HEIGHTANDWEIGHT_H
