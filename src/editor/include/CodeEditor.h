#pragma once

#include <QPlainTextEdit>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class CppHighlighter;

class CodeEditor final : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit CodeEditor(QWidget* parent = nullptr);
    ~CodeEditor() override = default;

    CodeEditor(const CodeEditor&) = delete;
    CodeEditor& operator=(const CodeEditor&) = delete;
    CodeEditor(CodeEditor&&) = delete;
    CodeEditor& operator=(CodeEditor&&) = delete;

    [[nodiscard]] int lineNumberAreaWidth() const;
    void lineNumberAreaPaintEvent(QPaintEvent* event);

    bool openFile(const QString& path);
    bool saveFile(const QString& path);

    [[nodiscard]] QString currentPath() const noexcept { return m_currentPath; }

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);

private:
    QWidget* m_lineNumberArea{nullptr};
    CppHighlighter* m_highlighter{nullptr};
    QString m_currentPath;
};
