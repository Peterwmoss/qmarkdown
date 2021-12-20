#include "helpers.h"
#include "mainwindow.h"

#include <QApplication>
#include <QString>

using namespace std;

int die(const char *message) {
  printf("Error: %s\n", message);
  printf("Usage: Usage `qmarkdown [colorscheme] <file>.md`\n");

  exit(1);
}

bool parse_file(char *arg, QString *file) {
  *file = arg;
  if (file_exists(file)) {
    return true;
  }
  return false;
}

bool parse_color(QString *index_file, QString *color_scheme) {
  if (*color_scheme == "l" || *color_scheme == "light") {
    *index_file = ":/index-light.html";
    return true;
  }
  if (*color_scheme == "d" || *color_scheme == "dark") {
    *index_file = ":/index-dark.html";
    return true;
  }
  return false;
}

bool parse_arguments(QString *index_file, QString *file, char *color_argument,
                     char *file_argument) {
  QString *color_scheme = new QString();
  if (color_argument[0] == '-') {
    if (color_argument[1] == '-')
      *color_scheme = color_argument + 2;
    else
      *color_scheme = color_argument + 1;
    if (!parse_color(index_file, color_scheme))
      return false;
    if (!parse_file(file_argument, file))
      return false;
    return true;
  }
  return false;
}

void load_args(int argc, char *argv[], QString *file, QString *index_file) {
  // Only file as argument
  if (argc == 2 && argv[1][0] != '-') {
    *index_file = ":/index-light.html";
    if (!parse_file(argv[1], file))
      die("File not found");
    return;
  }

  // File and colorscheme
  if (argc == 3) {
    if (!parse_arguments(index_file, file, argv[1], argv[2]))
      if (!parse_arguments(index_file, file, argv[2], argv[1]))
        die("Could not parse arguments");
    return;
  }
  die("Please pass valid arguments");
}

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("qMarkdown");
  QApplication app(argc, argv);

  QString file;
  QString index_file;
  load_args(argc, argv, &file, &index_file);

  MainWindow window(&index_file, &file);
  window.show();

  return app.exec();
}
