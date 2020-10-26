#include "mainwindow.h"
#include "document.h"
#include "preview.h"
#include "qnamespace.h"
#include "qsslsocket.h"
#include "qwebchannel.h"
#include "qwebengineview.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLineEdit>
#include <QShortcut>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>

MainWindow::MainWindow(QString *file, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  m_file = new QFile(*file);

  channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), &m_content);

  page = new Preview(this);
  page->setWebChannel(channel);

  ui->Preview->setPage(page);
  ui->Preview->setContextMenuPolicy(Qt::NoContextMenu);
  ui->Preview->setUrl(QUrl("qrc:/index.html"));

  loadFile();

  // Reload file every 1 second
  QTimer reload(this);
  connect(&reload, &QTimer::timeout, this, [this]() { this->loadFile(); });
  reload.start(1000);

  setupShortcuts();
}

MainWindow::~MainWindow() {
  // Shortcuts
  delete q;
  delete o;
  delete h;
  delete j;
  delete k;
  delete l;
  delete zero;
  delete ret;

  // UI
  delete ui;
  delete page;

  // Backend
  delete channel;
  delete m_file;
}

void fileEnter(Ui::MainWindow *ui) {
  ui->Preview->setFocus();
  ui->FileInput->hide();
  ui->FileInput->setText("");
}

void MainWindow::setupShortcuts() {
  // Q to close
  q = new QShortcut(Qt::Key_Q, this, SLOT(close()));

  // 0 to reset zoom
  zero = new QShortcut(Qt::Key_0, ui->Preview,
                       [this]() { this->page->resetZoom(); });

  // Vim keys to move
  j = new QShortcut(Qt::Key_J, ui->Preview,
                    [this]() { this->page->scrollDown(); });
  k = new QShortcut(Qt::Key_K, ui->Preview,
                    [this]() { this->page->scrollUp(); });
  h = new QShortcut(Qt::Key_H, ui->Preview,
                    [this]() { this->page->scrollLeft(); });
  l = new QShortcut(Qt::Key_L, ui->Preview,
                    [this]() { this->page->scrollRight(); });

  // o to open new file
  o = new QShortcut(Qt::Key_O, ui->Preview, [this]() {
    this->ui->FileInput->show();
    this->ui->FileInput->setFocus();
  });
  // Escape to close file input
  esc = new QShortcut(Qt::Key_Escape, ui->Preview, [this]() {
    if (this->ui->StatusBar->isVisible())
      this->ui->StatusBar->hide();
    else if (this->ui->FileInput->isVisible())
      fileEnter(this->ui);
  });

  // Open file
  ret = new QShortcut(Qt::Key_Return, ui->Preview, [this]() {
    if (setFile(this->ui->FileInput->text()))
      fileEnter(this->ui);
  });
}

void MainWindow::loadFile() {
  m_file->open(QIODevice::ReadOnly);
  QTextStream stream(m_file);
  m_content.setText(stream.readAll());
  m_file->close();
}

bool fileExists(QString *path) {
  path->replace("~", QDir::homePath());
  QFileInfo check_file(*path);
  if (check_file.exists() && check_file.isFile())
    return true;
  else
    return false;
}

bool MainWindow::setFile(QString path) {
  if (fileExists(&path)) {
    m_file->setFileName(path);
    loadFile();
    return true;
  } else {
    ui->StatusBar->show();
    ui->StatusBar->showMessage("File not found");
    return false;
  }
}
