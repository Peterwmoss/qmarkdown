#include "mainwindow.h"
#include "document.h"
#include "helpers.h"
#include "preview.h"
#include "resgen.h"
#include "ui_mainwindow.h"
#include <qnamespace.h>

#if __has_include(<filesystem>)
#include <filesystem>
#define FILESYSTEM filesystem
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#define FILESYSTEM std::experimental::filesystem
#endif

#include <QFile>
#include <QResource>
#include <QShortcut>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>

using namespace std;

MainWindow::MainWindow(QString *colorscheme, QString *file, QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  // Change working directory to enable image loading
  m_current_path = get_path(*file);
  FILESYSTEM::current_path(m_current_path.toStdString());

  m_file = new QFile(get_file(*file));

  m_channel = new QWebChannel(this);
  m_channel->registerObject(QStringLiteral("content"), &m_content);

  m_page = new Preview(this);
  m_page->setWebChannel(m_channel);

  m_ui->Preview->setPage(m_page);
  m_ui->Preview->setContextMenuPolicy(Qt::NoContextMenu);
  m_ui->Preview->setUrl(QUrl(*colorscheme));

  loadImages();
  loadFile();

  // Reload file every 1 second
  m_reload = new QTimer(this);
  connect(m_reload, &QTimer::timeout, this, &MainWindow::reloadFile);
  m_reload->start(1000);

  setupShortcuts();
}

void MainWindow::reloadFile() {
  if (m_current_text != m_content.getText()) {
    m_current_text = m_content.getText();
    loadImages();
  }
  loadFile();
}

void MainWindow::loadFile() {
  m_file->open(QIODevice::ReadOnly);
  QTextStream stream(m_file);
  QString file_text(stream.readAll());
  m_content.setText(file_text);
  m_file->close();
}

void MainWindow::loadImages() {
  res_gen();

  QString qpath = m_current_path + QRC_FILE.c_str();

  if (file_exists(&qpath)) {
    QResource::registerResource(qpath);
    system(("rm -f " + QRC_FILE).c_str());
  }
}

bool MainWindow::setFile(QString path) {
  if (file_exists(&path)) {
    m_current_path = get_path(path);
    FILESYSTEM::current_path(m_current_path.toStdString());
    m_file->setFileName(get_file(path));
    loadFile();
    loadImages();
    return true;
  }

  m_ui->StatusBar->show();
  m_ui->StatusBar->showMessage("File not found");
  return false;
}

void fileEnter(Ui::MainWindow *ui) {
  ui->Preview->setFocus();
  ui->Input->hide();
  ui->Input->setText("");
}

// Pre-lambda QT5 support
void MainWindow::resetZoom() { this->m_page->resetZoom(); }

void MainWindow::scrollDown() { this->m_page->scrollDown(); }
void MainWindow::scrollUp() { this->m_page->scrollUp(); }
void MainWindow::scrollLeft() { this->m_page->scrollLeft(); }
void MainWindow::scrollRight() { this->m_page->scrollRight(); }
void MainWindow::scrollTop() { this->m_page->scrollTop(); }
void MainWindow::scrollBottom() { this->m_page->scrollBottom(); }

void MainWindow::openFileInput() {
    m_ui->Input->show();
    m_ui->Input->setFocus();
}
void MainWindow::closeFileInput() {
    if (m_ui->StatusBar->isVisible())
      m_ui->StatusBar->hide();
    else if (m_ui->Input->isVisible())
      fileEnter(m_ui);
}

void MainWindow::openFile() {
    if (setFile(m_ui->Input->text())) 
      fileEnter(m_ui);
}

void MainWindow::autoComplete() { m_ui->Input->auto_complete(); }

void MainWindow::setupShortcuts() {
  // Q to close
  m_shortcuts[0] = new QShortcut(Qt::Key_Q, this, SLOT(close()));

  // 0 to reset zoom
  m_shortcuts[1] = new QShortcut(Qt::Key_0, this, SLOT(resetZoom()));

  // Vim keys to move
  m_shortcuts[2] = new QShortcut(Qt::Key_J, this, SLOT(scrollDown()));
  m_shortcuts[3] = new QShortcut(Qt::Key_K, this, SLOT(scrollUp()));
  m_shortcuts[4] = new QShortcut(Qt::Key_H, this, SLOT(scrollLeft()));
  m_shortcuts[5] = new QShortcut(Qt::Key_L, this, SLOT(scrollRight()));

  m_shortcuts[6] = new QShortcut(Qt::Key_G, this, SLOT(scrollTop()));
  m_shortcuts[7] = new QShortcut(QKeySequence(Qt::Modifier::SHIFT + Qt::Key_G), this, SLOT(scrollBottom()));

  m_shortcuts[8] = new QShortcut(Qt::Key_O, this, SLOT(openFileInput()));
  m_shortcuts[9] = new QShortcut(Qt::Key_Escape, this, SLOT(closeFileInput()));

  m_shortcuts[10] = new QShortcut(Qt::Key_Return, this, SLOT(openFile()));
  m_shortcuts[11] = new QShortcut(Qt::Key_Tab, this, SLOT(autoComplete()));
}

MainWindow::~MainWindow() {
  // Shortcuts
  int i = 0;
  while (i < NUM_SHORTCUTS)
    delete m_shortcuts[i++];

  // UI
  delete m_ui->Input;
  delete m_ui->Preview;
  delete m_ui->StatusBar;
  delete m_ui;

  // Backend
  delete m_page;
  delete m_channel;
  delete m_file;
  delete m_reload;

  // Cleanup
  system(("rm -f " + QRC_FILE).c_str());
}
