#pragma once

#include <QMainWindow>

class QTabWidget;
class QTreeView;
class QLabel;

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

private slots:
    void onNewFile();
    void onOpenFile();
    void onAbout();

private:
    void setupMenuBar();
    void setupCentralWidget();
    void setupDocks();
    void setupStatusBar();

    QTabWidget* m_tabs{nullptr};
    QTreeView* m_projectView{nullptr};
    QLabel* m_statusLabel{nullptr};
};
