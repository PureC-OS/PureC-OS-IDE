#include "include/MainWindow.h"

#include "editor/include/CodeEditor.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_editor(new CodeEditor(this))
{
    setWindowTitle(QStringLiteral("PureC-OS-IDE"));
    resize(1280, 800);

    setCentralWidget(m_editor);
}
