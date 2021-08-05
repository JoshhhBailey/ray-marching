#include "SphereNode.h"

#include <ngl/Vec3.h>

#include <iostream>

SphereNode::SphereNode()
{
    m_variableName = "sphere";
    QString shaderCode = "float " + m_variableName + " = sdSphere(_p, vec3(0, 0, 0), 1.0);\n";
    QString functionCall = " = sdSphere(_p, vec3(0, 0, 0), 1.0);\n";

    m_sphereData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_sphereData->setFunctionCall(functionCall);

    m_sphereWidget = new SphereNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_codeEditor->hide();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void SphereNode::createConnections()
{
  connect(m_sphereWidget->getPositionWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->getPositionWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->getPositionWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->getRadiusWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString SphereNode::caption() const
{
    return QString("Sphere");
}

QString SphereNode::name() const
{
    return QString("Sphere");
}

unsigned int SphereNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 0;
            break;
        }
        case PortType::Out:
        {
            result = 1;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

NodeDataType SphereNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> SphereNode::outData(PortIndex)
{
    return m_sphereData;
}

QWidget* SphereNode::embeddedWidget()
{
    return m_sphereWidget;
}

QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_sphereData)
  {
    modelJson["shaderCode"] = m_sphereData->getShaderCode();
    modelJson["variableName"] = m_sphereData->getVariableName();
    modelJson["xPos"] = m_sphereWidget->getPositionWidget()->getVec3().m_x;
    modelJson["yPos"] = m_sphereWidget->getPositionWidget()->getVec3().m_y;
    modelJson["zPos"] = m_sphereWidget->getPositionWidget()->getVec3().m_z;
    modelJson["radius"] = m_sphereWidget->getRadiusWidget()->value();
  }

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue r  = _p["radius"];

  m_sphereData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_sphereData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_sphereData->setVariableName(variableName);
  }

  if (!xp.isUndefined() && !yp.isUndefined() && !zp.isUndefined())
  {
    ngl::Vec3 position = ngl::Vec3(xp.toDouble(), yp.toDouble(), zp.toDouble());
    m_sphereWidget->getPositionWidget()->setVec3(position);
  }

  if (!r.isUndefined())
  {
    m_sphereWidget->getRadiusWidget()->setValue(r.toDouble());
  }
}

void SphereNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_sphereWidget->getPositionWidget()->getVec3();
  int x = pos.m_x;
  int y = pos.m_y;
  int z = pos.m_z;

  // Convert to string
  QString position = QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z);
  QString radius = QString::number(m_sphereWidget->getRadiusWidget()->value());

  // Update node data
  QString shaderCode = "float " + m_variableName + " = sdSphere(_p, vec3(" + position + "), " + radius + ");\n";
  m_sphereData->setShaderCode(shaderCode);

  QString functionCall = " = sdSphere(_p, vec3(" + position + "), " + radius + ");\n";
  m_sphereData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void SphereNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}