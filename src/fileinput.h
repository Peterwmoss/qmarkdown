#ifndef FILEINPUT_HEADER
#define FILEINPUT_HEADER

#include <qlineedit.h>
#include <qwidget.h>
#include <string>

#define AUTO_COMPLETE_MAX 128

class FileInput : public QLineEdit {
public:
  FileInput() {
    reset_complete_list();
    current_index = -1;
  }
  void next_suggestion();
  void prev_suggestion();

private:
  void reset_complete_list();
  void fetch_suggestions();
  void update_suggestion();
  int current_index;
  int size;
  std::string search_text;
  std::string m_complete_list[AUTO_COMPLETE_MAX];
};

#endif
