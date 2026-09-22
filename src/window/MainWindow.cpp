#include "include/MainWindow.h"

#include <QAction>
#include <QDockWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QTabWidget>
#include <QTreeView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("PureC-OS-IDE"));
    resize(1280, 800);

    setupMenuBar();
    setupCentralWidget();
    setupDocks();
    setupStatusBar();
}

void MainWindow::setupMenuBar()
{
    auto* fileMenu = menuBar()->addMenu(tr("&File"));

    auto* newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::onNewFile);
    fileMenu->addAction(newAct);

    auto* openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::onOpenFile);
    fileMenu->addAction(openAct);

    fileMenu->addSeparator();

    auto* quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    connect(quitAct, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(quitAct);

    auto* helpMenu = menuBar()->addMenu(tr("&Help"));
    auto* aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(aboutAct);
}

void MainWindow::setupCentralWidget()
{
    m_tabs = new QTabWidget(this);
    m_tabs->setTabsClosable(true);
    m_tabs->setMovable(true);
    connect(m_tabs, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget* w = m_tabs->widget(index);
        m_tabs->removeTab(index);
        delete w;
    });


    setCentralWidget(m_tabs);
}

void MainWindow::setupDocks()
{
    auto* dock = new QDockWidget(tr("Project"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_projectView = new QTreeView(dock);
    // Model will be attached later (QFileSystemModel).
    // Placeholder keeps layout stable for now.
    dock->setWidget(m_projectView);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel(tr("Ready"), this);
    statusBar()->addPermanentWidget(m_statusLabel, 1);
    statusBar()->showMessage(tr("PureC-OS-IDE initialized"), 3000);
}

void MainWindow::onNewFile()
{
    auto* editor = new QPlainTextEdit(this);
    editor->setPlaceholderText(tr("New file — start typing..."));
    const int index = m_tabs->addTab(editor, tr("Untitled"));
    m_tabs->setCurrentIndex(index);
}

void MainWindow::onOpenFile()
{
    const QString path = QFileDialog::getOpenFileName(
        this, tr("Open File"), QString(), tr("All Files (*)"));
    if (path.isEmpty()) {
        return;
    }

    auto* editor = new QPlainTextEdit(this);
    // Content loading comes next (editor module).
    editor->setPlaceholderText(path);
    const int index = m_tabs->addTab(editor, QFileInfo(path).fileName());
    m_tabs->setCurrentIndex(index);
    m_statusLabel->setText(path);
}

void MainWindow::onAbout()
{
    QMessageBox::about(
        this, tr("About PureC-OS-IDE"),
        tr("PureC-OS-IDE — IDE for low-level development.\nBase window (Qt6 + C++20)."));
}
