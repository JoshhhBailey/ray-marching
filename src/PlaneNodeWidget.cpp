///  @file PlaneNodeWidget.cpp
///  @brief Creates editable parameters widget for Plane node

#include <QtWidgets/QFormLayout>

#include "PlaneNodeWidget.h"

PlaneNodeWidget::PlaneNodeWidget()
{
    createWidgets();
    createLayouts();
}

void PlaneNodeWidget::createWidgets()
{
    m_idWidget = new QSpinBox();
    m_idWidget->setRange(0, 9999);
    m_idWidget->setValue(0);
    m_yPosWidget = new QDoubleSpinBox();
    m_yPosWidget->setRange(-9999.0, 9999.0);
    m_yPosWidget->setValue(0.0);
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void PlaneNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("ID:", m_idWidget);
    mainLayout->addRow("Y Position:", m_yPosWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}