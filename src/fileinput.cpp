#include "fileinput.h"
#include "helpers.h"

#include <QString>
#include <iostream>

#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#endif

using namespace std;

string get_start(size_t end, string path) { return path.erase(end).c_str(); }

string get_end(size_t start, string path) {
  return path.erase(0, start).c_str();
}

void FileInput::auto_complete() {
  string path = text().toStdString();
  size_t p_slash = path.rfind("/") + 1;

  QString *q_path;
  if (get_start(p_slash, path) == "")
    q_path = new QString(".");
  else
    q_path = new QString(path.c_str());

  string search_word = get_end(p_slash, path);

  // Clear previous search
  int count = 0;
  for (count = 0; count < AUTO_COMPLETE_MAX; count++)
    complete_list[count] = "";

  // Clear query path if its not a directory or file
  if (!directory_exists(q_path)) {
    free(q_path);
    q_path = new QString(get_start(p_slash, path).c_str());
  }

  count = 0;
  if (directory_exists(q_path)) {
    for (const auto &entry :
         filesystem::directory_iterator(q_path->toStdString())) {
      string entry_str = entry.path();

      size_t e_slash = entry_str.rfind("/") + 1;
      QString *entry_end = new QString(get_end(e_slash, entry_str).c_str());

      if (entry_end->startsWith(search_word.c_str())) {
        if (entry_end->endsWith(".md")) {
          if (count < AUTO_COMPLETE_MAX) {
            complete_list[count] = entry.path().string();
          }
          count++;
        } else if (entry.is_directory()) {
          if (count < AUTO_COMPLETE_MAX) {
            complete_list[count] = entry.path().string() + "/";
          }
          count++;
        }
      }
      free(entry_end);
    }
  }
  free(q_path);

  if (count == 1)
    setText(complete_list[0].c_str());
}
