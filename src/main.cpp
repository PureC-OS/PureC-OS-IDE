#include <QApplication>

#include "window/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("PureC-OS-IDE"));
    app.setOrganizationName(QStringLiteral("PureC"));

    MainWindow window;
    window.show();

    return app.exec();
}
