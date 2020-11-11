#ifndef HELPERS_HEADER
#define HELPERS_HEADER

#include <QString>
#include <string>

const std::string QRC_FILE("images.rcc");

QString get_file(QString path);
QString get_path(QString path, QString argument);
bool file_exists(QString *path);
bool directory_exists(QString *path);

#endif
