#include "helpers.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QResource>
#include <QString>
#include <cstdio>
#include <string>

int die(const char *message) {
  printf("Error: %s\n", message);
  printf("Usage: Usage `qmarkdown <file>.md`\n");

  exit(1);
}

bool parse_file(char *arg, QString *file, std::string path) {
  *file = arg;
  if (file_exists(file)) {
    std::string s(arg);
    path = fix_path(&s);
    return true;
  }
  return false;
}

bool parse_color(std::string color) {
  std::string light = "light";
  std::string dark = "dark";

  if (color == light) {
    color = ":/index-light.html";
    return true;
  }
  if (color == dark) {
    color = ":/index-dark.html";
    return true;
  }
  return false;
}

void load_args(int argc, char *argv[], QString *file, std::string path,
               std::string color) {
  // Only file as argument
  if (argc == 2) {
    if (parse_file(argv[1], file, path))
      return;
    die("File not found");
  }

  // File and colorscheme
  if (argc == 3) {
    // colorscheme first, file second
    if (argv[1][0] == '-') {
      color = argv[1] + 1;
      if (!parse_color(color))
        die("Colorscheme not found. Valid colorschemes are: 'light' 'dark'");
      if (!parse_file(argv[2], file, path))
        die("File not found");
      return;
    }

    // file first, colorscheme second
    if (argv[2][0] == '-') {
      color = argv[2] + 1;
      if (!parse_color(color))
        die("Colorscheme not found. Valid colorschemes are: 'light' 'dark'");
      if (!parse_file(argv[1], file, path))
        die("File not found");
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
  std::string path;
  std::string color;

  load_args(argc, argv, &file, path, color);

  MainWindow window(color, path, &file);
  window.show();

  return app.exec();
}
