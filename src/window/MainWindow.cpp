#include "include/MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("PureC-OS-IDE"));
    resize(1280, 800);
}
