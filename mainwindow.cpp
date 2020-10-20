#include "mainwindow.h"
#include "document.h"
#include "qwebchannel.h"
#include "qwebengineview.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QWebChannel>
#include <QWebEnginePage>

MainWindow::MainWindow(QFile *file, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

  QWebEnginePage *page = new QWebEnginePage(this);
  ui->preview->setPage(page);

  QWebChannel *channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), &m_content);
  page->setWebChannel(channel);

  ui->preview->setUrl(QUrl("qrc:/index.html"));

  loadFile(file);

  QTimer *reload = new QTimer(this);
  connect(reload, &QTimer::timeout, this, [=]() { this->loadFile(file); });
  reload->start(1000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile(QFile *file) {
  file->open(QIODevice::ReadOnly);
  QTextStream stream(file);
  m_content.setText(stream.readAll());
  file->close();
}
