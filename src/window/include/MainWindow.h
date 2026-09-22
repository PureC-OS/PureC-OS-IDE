#pragma once

#include <QMainWindow>

class CodeEditor;

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

    [[nodiscard]] CodeEditor* editor() const noexcept { return m_editor; }

private:
    CodeEditor* m_editor{nullptr};
};
