#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
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

  file->open(QIODevice::ReadOnly);

  QTextStream stream(file);
  m_content.setText(stream.readAll());
}

MainWindow::~MainWindow() { delete ui; }
