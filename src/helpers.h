#ifndef HELPERS_HEADER
#define HELPERS_HEADER

#include <QString>
#include <string>

const std::string QRC_FILE(".images.rcc");

std::string fix_path(std::string *path);
bool file_exists(QString *path);
bool directory_exists(QString *path);

#endif
