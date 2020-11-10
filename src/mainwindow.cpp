#include "mainwindow.h"
#include "document.h"
#include "helpers.h"
#include "preview.h"
#include "resgen.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QResource>
#include <QShortcut>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>
#include <qnamespace.h>
#include <string>

MainWindow::MainWindow(std::string colorscheme, std::string path, QString *file,
                       QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  m_current_path = path;

  m_file = new QFile(*file);

  m_channel = new QWebChannel(this);
  m_channel->registerObject(QStringLiteral("content"), &m_content);

  m_page = new Preview(this);
  m_page->setWebChannel(m_channel);

  m_ui->Preview->setPage(m_page);
  m_ui->Preview->setContextMenuPolicy(Qt::NoContextMenu);
  m_ui->Preview->setUrl(QUrl(colorscheme.c_str()));

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
  if (!m_current_path.empty())
    res_gen(m_current_path);
  else
    res_gen(".");

  QString qpath = (m_current_path + QRC_FILE).c_str();

  if (file_exists(&qpath)) {
    QResource::registerResource(qpath);
    system(("rm -f " + QRC_FILE).c_str());
  }
}

bool MainWindow::setFile(QString path) {
  if (file_exists(&path)) {
    std::string std_string(path.toStdString());
    m_current_path = fix_path(&std_string);
    m_file->setFileName(path);
    loadFile();
    return true;
  } else {
    m_ui->StatusBar->show();
    m_ui->StatusBar->showMessage("File not found");
    return false;
  }
}

void fileEnter(Ui::MainWindow *ui) {
  ui->Preview->setFocus();
  ui->Input->hide();
  ui->Input->setText("");
}

void MainWindow::setupShortcuts() {
  // Q to close
  m_shortcuts[0] = new QShortcut(Qt::Key_Q, this, SLOT(close()));

  // 0 to reset zoom
  m_shortcuts[1] = new QShortcut(Qt::Key_0, m_ui->Preview,
                                 [this]() { this->m_page->resetZoom(); });

  // Vim keys to move
  m_shortcuts[2] = new QShortcut(Qt::Key_J, m_ui->Preview,
                                 [this]() { this->m_page->scrollDown(); });
  m_shortcuts[3] = new QShortcut(Qt::Key_K, m_ui->Preview,
                                 [this]() { this->m_page->scrollUp(); });
  m_shortcuts[4] = new QShortcut(Qt::Key_H, m_ui->Preview,
                                 [this]() { this->m_page->scrollLeft(); });
  m_shortcuts[5] = new QShortcut(Qt::Key_L, m_ui->Preview,
                                 [this]() { this->m_page->scrollRight(); });

  m_shortcuts[6] = new QShortcut(Qt::Key_G, m_ui->Preview,
                                 [this]() { this->m_page->scrollTop(); });
  m_shortcuts[7] =
      new QShortcut(QKeySequence(Qt::Modifier::SHIFT + Qt::Key_G),
                    m_ui->Preview, [this]() { this->m_page->scrollBottom(); });

  // o to open new file
  m_shortcuts[8] = new QShortcut(Qt::Key_O, m_ui->Preview, [this]() {
    this->m_ui->Input->show();
    this->m_ui->Input->setFocus();
  });
  // Escape to close file input
  m_shortcuts[9] = new QShortcut(Qt::Key_Escape, m_ui->Preview, [this]() {
    if (this->m_ui->StatusBar->isVisible())
      this->m_ui->StatusBar->hide();
    else if (this->m_ui->Input->isVisible())
      fileEnter(this->m_ui);
  });
  // Open file from input
  m_shortcuts[10] = new QShortcut(Qt::Key_Return, m_ui->Preview, [this]() {
    if (setFile(this->m_ui->Input->text()))
      fileEnter(this->m_ui);
  });

  // Tab complete
  m_shortcuts[11] = new QShortcut(Qt::Key_Tab, m_ui->Input, [this]() {
    this->m_ui->Input->auto_complete();
  });
}

MainWindow::~MainWindow() {
  // Shortcuts
  int i = 0;
  while (i < NUM_SHORTCUTS)
    delete m_shortcuts[i++];

  // UI
  delete m_ui;
  delete m_page;

  // Backend
  delete m_channel;
  delete m_file;
  delete m_reload;

  // Cleanup
  system(("rm -f " + QRC_FILE).c_str());
}
