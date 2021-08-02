#include "SphereNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

SphereNodeWidget::SphereNodeWidget()
{
    setTitle("Properties:");
    createWidgets();
    createLayouts();
}

void SphereNodeWidget::createWidgets()
{
    m_positionWidget = new Vec3Widget("Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_radiusWidget = new QDoubleSpinBox();
    m_radiusWidget->setRange(0.0, 9999.0);
    m_radiusWidget->setValue(1.0);
}

void SphereNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_positionWidget);
    mainLayout->addRow("Radius:", m_radiusWidget);
    setLayout(mainLayout);
}