#include "helpers.h"

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <regex>
#include <string>

std::string fix_path(std::string *path) {
  std::regex e(R"((.*/)*(.*md))");
  return regex_replace(*path, e, "$1");
}

bool fileExists(QString *path) {
  path->replace("~", QDir::homePath());
  QFileInfo check_file(*path);
  if (check_file.exists() && check_file.isFile())
    return true;
  else
    return false;
}
