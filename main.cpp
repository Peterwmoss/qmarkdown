#include "helpers.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QString>
#include <string>

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QString file;
  std::string path;

  if (argc == 2) {
    file = argv[1];
    std::string s(argv[1]);
    path = fix_path(&s);
  } else {
    path = ".";
    file = ":/help.md";
  }

  MainWindow window(path, &file);
  window.show();

  return app.exec();
}
