#include "helpers.h"
#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <iostream>
#include <qregexp.h>
#include <string>

using namespace std;

int die(const char *message) {
  printf("Error: %s\n", message);
  printf("Usage: Usage `qmarkdown <file>.md`\n");

  exit(1);
}

bool parse_color(QString *color) {
  if (*color == "light") {
    *color = "qrc:/index-light.html";
    return true;
  }
  if (*color == "dark") {
    *color = "qrc:/index-dark.html";
    return true;
  }
  return false;
}

void load_args(int argc, char *argv[], QString *color) {
  // Only file as argument
  if (argc == 2 && argv[1][0] != '-') {
    *color = "qrc:/index-light.html";
    return;
  }

  // File and colorscheme
  if (argc == 3) {
    // colorscheme first, file second
    if (argv[1][0] == '-') {
      *color = argv[1] + 1;
      if (!parse_color(color))
        die("Colorscheme not found. Valid colorschemes are: 'light' 'dark'");
      return;
    }

    // file first, colorscheme second
    if (argv[2][0] == '-') {
      *color = argv[2] + 1;
      if (!parse_color(color))
        die("Colorscheme not found. Valid colorschemes are: 'light' 'dark'");
      return;
    }
    die("Unknown arguments");
  }
  die("Please pass valid arguments");
}

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QString file = argv[1];
  QString color;
  load_args(argc, argv, &color);

  MainWindow window(&color, &file);
  window.show();

  return app.exec();
}
