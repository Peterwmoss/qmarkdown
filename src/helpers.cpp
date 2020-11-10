#include "helpers.h"

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <regex>
#include <string>

QString get_file(QString *path) {
  std::regex e(R"((.*/)*(.*md))");
  return regex_replace(path->toStdString(), e, "$1").c_str();
}

bool file_exists(QString *path) {
  path->replace("~", QDir::homePath());
  QFileInfo check_file(*path);
  if (check_file.exists() && check_file.isFile())
    return true;
  else
    return false;
}

bool directory_exists(QString *path) {
  path->replace("~", QDir::homePath());
  QFileInfo check_file(*path);
  if (check_file.exists() && check_file.isDir())
    return true;
  else
    return false;
}
