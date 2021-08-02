#pragma once

#include <ngl/Vec3.h>

#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

class Vec3Widget : public QWidget
{
public:
    Vec3Widget(QString _label = QString("Vec3"), ngl::Vec3 _vec3 = {0.0f, 0.0f, 0.0f});
    
    ngl::Vec3 getVec3() const { return ngl::Vec3(m_xField->value(),
                                                 m_yField->value(),
                                                 m_zField->value()); }

    void setVec3(ngl::Vec3 _vec3) { m_xField->setValue(_vec3.m_x);
                                    m_yField->setValue(_vec3.m_y);
                                    m_zField->setValue(_vec3.m_z); }
    
    QLabel *m_label;
    QDoubleSpinBox *m_xField;
    QDoubleSpinBox *m_yField;
    QDoubleSpinBox *m_zField;

private:
    void createWidgets();
    void createLayouts();
};