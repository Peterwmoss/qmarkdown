#include "helpers.h"
#include "mainwindow.h"

#include <QApplication>
#include <QString>

using namespace std;

int die(const char *message) {
  printf("Error: %s\n", message);
  printf("Usage: Usage `qmarkdown <file>.md`\n");

  exit(1);
}

bool parse_file(char *arg, QString *file) {
  *file = arg;
  if (file_exists(file)) {
    return true;
  }
  return false;
}

bool parse_color_short(QString *color) {
  if (*color == "l") {
    *color = "qrc:/index-light.html";
    return true;
  }
  if (*color == "d") {
    *color = "qrc:/index-dark.html";
    return true;
  }
  return false;
}

bool parse_color_long(QString *color) {
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

bool parse_arguments(QString *color, QString *file, char *color_argument,
                     char *file_argument) {
  if (color_argument[0] == '-') {
    if (color_argument[1] == '-')
      *color = color_argument + 2;
    else
      *color = color_argument + 1;
    if (!parse_color_long(color) && !parse_color_short(color))
      return false;
    if (!parse_file(file_argument, file))
      return false;
    return true;
  }
  return false;
}

void load_args(int argc, char *argv[], QString *file, QString *color) {
  // Only file as argument
  if (argc == 2 && argv[1][0] != '-') {
    *color = "qrc:/index-light.html";
    if (!parse_file(argv[1], file))
      die("File not found");
    return;
  }

  // File and colorscheme
  if (argc == 3) {
    if (!parse_arguments(color, file, argv[1], argv[2]))
      if (!parse_arguments(color, file, argv[2], argv[1]))
        die("Could not parse arguments");
    return;
  }
  die("Please pass valid arguments");
}

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QString file;
  QString color;
  load_args(argc, argv, &file, &color);

  MainWindow window(&color, &file);
  window.show();

  return app.exec();
}
