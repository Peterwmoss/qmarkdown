#include "mainwindow.h"
#include "qstringliteral.h"

#include <QApplication>
#include <QDir>
#include <QString>
#include <regex>
#include <string>

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QString file;
  std::string path;

  if (argc == 2) {
    file = argv[1];
    std::regex e(R"((.*/)*(.*md))");
    path = regex_replace(argv[1], e, "$1");
  } else {
    path = ".";
    file = ":/help.md";
  }

  MainWindow window(path, &file);
  window.show();

  return app.exec();
}
