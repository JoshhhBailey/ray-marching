///  @file RayMarchNodeWidget.cpp
///  @brief Creates editable parameters widget for Ray March node

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

#include "RayMarchNodeWidget.h"

RayMarchNodeWidget::RayMarchNodeWidget()
{
    createWidgets();
    createLayouts();
}

void RayMarchNodeWidget::createWidgets()
{
    m_rayOriginLabel = new QLabel();
    m_rayOriginLabel->setText("Camera");
    m_rayOriginWidget = new Vec3Widget("Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_lightLabel = new QLabel();
    m_lightLabel->setText("Light");
    m_lightPositionWidget = new Vec3Widget("Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void RayMarchNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_rayOriginLabel);
    mainLayout->addRow(m_rayOriginWidget);
    mainLayout->addRow(m_lightLabel);
    mainLayout->addRow(m_lightPositionWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}