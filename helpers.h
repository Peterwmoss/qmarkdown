#ifndef HELPERS_HEADER
#define HELPERS_HEADER

#include <QString>
#include <string>

const std::string QRC_FILE(".images.rcc");

std::string fix_path(std::string *path);
bool fileExists(QString *path);

#endif
