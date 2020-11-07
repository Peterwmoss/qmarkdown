#include "mainwindow.h"
#include "document.h"
#include "helpers.h"
#include "preview.h"
#include "resgen.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QLineEdit>
#include <QResource>
#include <QShortcut>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>
#include <string>

MainWindow::MainWindow(std::string path, QString *file, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  current_path = path;

  m_file = new QFile(*file);

  channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), &m_content);

  page = new Preview(this);
  page->setWebChannel(channel);

  ui->Preview->setPage(page);
  ui->Preview->setContextMenuPolicy(Qt::NoContextMenu);
  ui->Preview->setUrl(QUrl("qrc:/index.html"));

  loadImages();
  loadFile();

  // Reload file every 1 second
  reload = new QTimer(this);
  connect(reload, &QTimer::timeout, this, &MainWindow::reloadFile);
  reload->start(1000);

  setupShortcuts();
}

void MainWindow::reloadFile() {
  if (current_text != m_content.getText()) {
    current_text = m_content.getText();
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
  if (!current_path.empty())
    res_gen(current_path);
  else
    res_gen(".");

  QString qpath = (current_path + QRC_FILE).c_str();

  if (file_exists(&qpath)) {
    QResource::registerResource(qpath);
    system(("rm -f " + QRC_FILE).c_str());
  }
}

bool MainWindow::setFile(QString path) {
  if (file_exists(&path)) {
    std::string std_string(path.toStdString());
    current_path = fix_path(&std_string);
    m_file->setFileName(path);
    loadFile();
    return true;
  } else {
    ui->StatusBar->show();
    ui->StatusBar->showMessage("File not found");
    return false;
  }
}

void fileEnter(Ui::MainWindow *ui) {
  ui->Preview->setFocus();
  ui->FileInput->hide();
  ui->FileInput->setText("");
}

void MainWindow::setupShortcuts() {
  // Q to close
  shortcuts[0] = new QShortcut(Qt::Key_Q, this, SLOT(close()));

  // 0 to reset zoom
  shortcuts[1] = new QShortcut(Qt::Key_0, ui->Preview,
                               [this]() { this->page->resetZoom(); });

  // Vim keys to move
  shortcuts[2] = new QShortcut(Qt::Key_J, ui->Preview,
                               [this]() { this->page->scrollDown(); });
  shortcuts[3] = new QShortcut(Qt::Key_K, ui->Preview,
                               [this]() { this->page->scrollUp(); });
  shortcuts[4] = new QShortcut(Qt::Key_H, ui->Preview,
                               [this]() { this->page->scrollLeft(); });
  shortcuts[5] = new QShortcut(Qt::Key_L, ui->Preview,
                               [this]() { this->page->scrollRight(); });

  shortcuts[6] = new QShortcut(Qt::Key_G, ui->Preview,
                               [this]() { this->page->scrollTop(); });
  shortcuts[7] =
      new QShortcut(QKeySequence(Qt::Key_Shift + Qt::Key_G), ui->Preview,
                    [this]() { this->page->scrollBottom(); });

  // o to open new file
  shortcuts[8] = new QShortcut(Qt::Key_O, ui->Preview, [this]() {
    this->ui->FileInput->show();
    this->ui->FileInput->setFocus();
  });
  // Escape to close file input
  shortcuts[9] = new QShortcut(Qt::Key_Escape, ui->Preview, [this]() {
    if (this->ui->StatusBar->isVisible())
      this->ui->StatusBar->hide();
    else if (this->ui->FileInput->isVisible())
      fileEnter(this->ui);
  });

  // Open file
  shortcuts[10] = new QShortcut(Qt::Key_Return, ui->Preview, [this]() {
    if (setFile(this->ui->FileInput->text()))
      fileEnter(this->ui);
  });
}

MainWindow::~MainWindow() {
  // Shortcuts
  int i = 0;
  while (i < NUM_SHORTCUTS)
    delete shortcuts[i++];

  // UI
  delete ui;
  delete page;

  // Backend
  delete channel;
  delete m_file;
  delete reload;

  // Cleanup
  system(("rm -f " + QRC_FILE).c_str());
}
