#ifndef FILEINPUT_HEADER
#define FILEINPUT_HEADER

#include <qlineedit.h>
#include <qwidget.h>
#include <string>

#define AUTO_COMPLETE_MAX 1

class FileInput : public QLineEdit {
public:
  void auto_complete();

private:
  std::string complete_list[AUTO_COMPLETE_MAX];
};

#endif
