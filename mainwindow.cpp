#include "mainwindow.h"
#include "document.h"
#include "preview.h"
#include "qwebchannel.h"
#include "qwebengineview.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QShortcut>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>

MainWindow::MainWindow(QFile *file, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

  Preview *page = new Preview(this);
  ui->preview->setPage(page);

  QWebChannel *channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), &m_content);
  page->setWebChannel(channel);

  ui->preview->setUrl(QUrl("qrc:/index.html"));

  loadFile(file);

  // Reload file every 1 second
  QTimer *reload = new QTimer(this);
  connect(reload, &QTimer::timeout, this, [=]() { this->loadFile(file); });
  reload->start(1000);

  setupShortcuts(page);
}

void MainWindow::setupShortcuts(Preview *page) {
  // Q to close
  new QShortcut(Qt::Key_Q, this, SLOT(close()));

  // 0 to reset zoom
  new QShortcut(Qt::Key_0, ui->preview, [=]() { page->resetZoom(); });

  // Vim keys to move
  new QShortcut(Qt::Key_J, ui->preview, [=]() { page->scrollDown(); });
  new QShortcut(Qt::Key_K, ui->preview, [=]() { page->scrollUp(); });
  new QShortcut(Qt::Key_H, ui->preview, [=]() { page->scrollLeft(); });
  new QShortcut(Qt::Key_L, ui->preview, [=]() { page->scrollRight(); });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile(QFile *file) {
  file->open(QIODevice::ReadOnly);
  QTextStream stream(file);
  m_content.setText(stream.readAll());
  file->close();
}
