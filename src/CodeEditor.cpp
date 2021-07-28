// The following code is adapted from:
// Qt., 2021. Qt Documentation - Code Editor Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
// Accessed [17 June 2021]

#include "CodeEditor.h"

#include <QPainter>
#include <QTextBlock>

CodeEditor::CodeEditor() : QPlainTextEdit()
{
    m_lineNumberArea = new LineNumberArea(this);

    // Text edit settings
    updateFont();
    setLineWrapMode(QPlainTextEdit::NoWrap);

    // Stretch text editor to bottom of window
    QSizePolicy policy = sizePolicy();
    policy.setVerticalStretch(1);
    setSizePolicy(policy);

    reset();

    // Initialise line number area width and highlight first line
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);

    updateLineNumberAreaWidth();
}

void CodeEditor::reset()
{
    // Default code when app launches
    const char code[] =
    "// Shader Inputs:\n"
    "// in vec2         iUV;        Normalized pixel coordinates (from 0 to 1)\n"
    "// uniform float   iTime;      Shader playback time (in seconds)\n"
    "// uniform vec2    iMouse      Mouse pixel coordinates (if LMB down);\n"
    "\n"
    "void main()\n"
    "{\n"
    "   // Time varying pixel colour\n"
	"   vec3 colour = 0.5 + 0.5 * cos(iTime + iUV.xyx + vec3(0, 2, 4));\n"
    "\n"
	"   // Output to screen\n"
	"   fragColour = vec4(colour, 1.0);\n"
    "}";

    setPlainText(code);
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;                     // Maximum line number digits
    int max = qMax(1, blockCount());    // Maximum line number

    // For everyone power of 10, increment digits
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &_rect, int _dy)
{
    // Scroll line numbers
    if (_dy)
    {
        m_lineNumberArea->scroll(0, _dy);
    }
    else
    {
        m_lineNumberArea->update(0, _rect.y(), m_lineNumberArea->width(), _rect.height());
    }

    if (_rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth();
    }
}

void CodeEditor::resizeEvent(QResizeEvent *_e)
{
    // When editor changes size, resize line number area
    QPlainTextEdit::resizeEvent(_e);

    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *_event)
{
    // Paint margin background
    QPainter painter(m_lineNumberArea);
    painter.fillRect(_event->rect(), Qt::lightGray);

    // Loop visible lines and paint line numbers
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= _event->rect().bottom())
    {
        if (block.isVisible() && bottom >= _event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(), Qt::AlignCenter, number);
        }
        
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::updateFont()
{
    QFont font(m_fontName, m_fontSize);
    setFont(font);
    setTabStopDistance(m_fontSize * 2);
}

void CodeEditor::setFontSize(int _size)
{
    m_fontSize = _size;
    updateFont();
}