#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include "NGLScene.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

class ShaderCodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    ShaderCodeWidget(NGLScene *_scene);
    CodeEditor* getCodeEditor() { return m_codeEditor; }
    
    QString getBoilerPlateCode() { return m_boilerPlateCode; }

public slots:
    void compileButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);

    CodeEditor *m_codeEditor;
    SyntaxHighlighter *m_syntaxHighlighter;
    QLabel *m_fontSizeLabel;
    QSpinBox *m_fontSize;
    QPushButton *m_compileButton;
    QLabel *m_outputLabel;
    QLabel *m_compilationLabel;

    NGLScene *m_scene;

    QString m_boilerPlateCode =
    "#version 410 core"
    "\n"
    "layout (location = 0) out vec4 fragColour;\n"
    "\n"
    "in vec2 iUV;\n"
    "uniform float iTime;\n"
    "uniform vec2 iMouse;\n"
    "\n";
};