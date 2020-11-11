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
    // colorscheme first, file second
    if (argv[1][0] == '-') {
      *color = argv[1] + 1;
      if (!parse_file(argv[2], file))
        die("File not found");
      if (!parse_color(color))
        die("Colorscheme not found. Valid colorschemes are: 'light' 'dark'");
      return;
    }

    // file first, colorscheme second
    if (argv[2][0] == '-') {
      *color = argv[2] + 1;
      if (!parse_file(argv[1], file))
        die("File not found");
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

  QString file;
  QString color;
  load_args(argc, argv, &file, &color);

  MainWindow window(&color, &file);
  window.show();

  return app.exec();
}
