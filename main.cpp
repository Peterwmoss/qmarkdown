#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <cstdio>

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QFile file;
  if (argc == 2) {
    file.setFileName(argv[1]);
  } else
    file.setFileName(":/help.md");

  MainWindow window(&file);
  window.show();

  return app.exec();
}
