#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Transformation.h>
#include <ngl/Text.h>

// this must be included after NGL includes else we get a clash with gl libs
#include <QtWidgets/QOpenGLWidget>
#include <QElapsedTimer>

#include "ScreenQuad.h"
#include "WindowParams.h"

#include <memory>

class NGLScene : public QOpenGLWidget
{
  public:
    NGLScene();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;
    bool compileShaderCode(QString _shaderCode, bool _GLSL);
    std::vector<GLchar> getShaderErrorMessage() { return m_shaderErrorMessage; }

    float getCompilationTime() { return (m_compilationTime.elapsed() / 1000.0f); }
    qint64 pauseTime();
    void unpauseTime(qint64 _pausedTime);

    float getNodesCompilationTime() { return (m_nodesCompilationTime.elapsed() / 1000.0f); }
    qint64 pauseNodesTime();
    void unpauseNodesTime(qint64 _pausedTime);

private:
    void keyPressEvent(QKeyEvent *_event) override;
    void mouseMoveEvent(QMouseEvent * _event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void timerEvent(QTimerEvent *_event) override;

    void buildShaders();
    void updateUniforms();
    void resetUniforms();

    WinParams m_win;
    std::unique_ptr<ScreenQuad> m_screenQuad;

    // Shader buffers
    std::string m_currentShader = "ShaderProgram_A";
    std::string m_nextShader = "ShaderProgram_B";
    std::string m_nextFragment = "Fragment_B";

    std::vector<GLchar> m_shaderErrorMessage;

    // Compilation timer
    QElapsedTimer m_compilationTime;
    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;

    QElapsedTimer m_nodesCompilationTime;
    bool m_nodesPauseTime = false;
    qint64 m_nodesPausedTime = 0;
};

#endif