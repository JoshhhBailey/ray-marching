#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include "ShaderCodeData.h"
#include "CapsuleNodeWidget.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class CapsuleNode : public NodeDataModel
{
  Q_OBJECT

public:
  CapsuleNode();
  virtual ~CapsuleNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  ConnectionPolicy portOutConnectionPolicy(PortIndex) const override { return ConnectionPolicy::One; }
  void setInData(std::shared_ptr<NodeData>, int) override { }
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;

public slots:
  void updateNode();
  void inspectCodeButtonClicked();

private:
  std::shared_ptr<ShaderCodeData> m_capsuleData;
  CapsuleNodeWidget *m_capsuleWidget;

  QString m_variableName;

  CodeEditor *m_codeEditor;
  SyntaxHighlighter *m_syntaxHighlighter;
};
