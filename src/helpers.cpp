#include "helpers.h"

#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#endif

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <iostream>
#include <qregexp.h>
#include <string>

using namespace std;

QString get_file(QString path) {
  path.replace(QRegExp("(.*/)*"), "");
  return path;
}

QString get_path(QString argument) {
  QString path = filesystem::absolute(argument.toStdString()).c_str();
  path.replace(get_file(argument), "");
  if (path.isEmpty())
    path = "./";
  return path;
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
