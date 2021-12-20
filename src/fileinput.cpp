#include "fileinput.h"
#include "helpers.h"

#include <QString>

#if __has_include(<filesystem>)
#include <filesystem>
#define FILESYSTEM filesystem
#define IS_DIRECTORY(p) p.is_directory()
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#define FILESYSTEM std::experimental::filesystem
#define IS_DIRECTORY(p) FILESYSTEM::is_directory(p.symlink_status())
#endif

using namespace std;

string remove_end(size_t index, string text) {
  if (text.empty()) {
    return "";
  }
  return text.erase(index);
}

string remove_start(size_t index, string text) {
  if (text.empty()) {
    return "";
  }
  return text.erase(0, index);
}

size_t get_search_index(string text) {
  // Get the index of the first character after the slash
  return text.rfind("/") + 1;
}

QString *get_path_from_text(size_t search_start_index, string text) {
  string trimmed = remove_end(search_start_index, text);
  if (trimmed == "") {
    return new QString(".");
  }

  return new QString(trimmed.c_str());
}

void FileInput::reset_complete_list() {
  for (int count = 0; count < AUTO_COMPLETE_MAX; count++) {
    m_complete_list[count] = "";
  }
}

void FileInput::fetch_suggestions() {
  reset_complete_list();

  // Convert the current text to a std::string since QString isn't doesn't provide the needed functionality
  string text = this->text().toStdString();
  size_t search_start_index = get_search_index(text);

  string search_word = remove_start(search_start_index, text);

  QString *path = get_path_from_text(search_start_index, text);

  if (!directory_exists(path)) {
    free(path);
    return;
  }

  int index = 0;
  auto it = FILESYSTEM::recursive_directory_iterator(path->toStdString(), FILESYSTEM::directory_options::skip_permission_denied);
  for (; it != FILESYSTEM::recursive_directory_iterator() && index < AUTO_COMPLETE_MAX; ++it) {
    // We only want to look one layer down
    if (it.depth() > 0) {
      continue;
    }

    const auto entry = *it;
    string entry_path = entry.path();

    size_t entry_search_start_index = get_search_index(entry_path);
    QString *search_result = new QString(remove_start(entry_search_start_index, entry_path).c_str());

    if (!search_result->startsWith(search_word.c_str())) {
      delete search_result;
      continue;
    }

    // If search result is either a markdown file or directory, we will add it to the list
    if (search_result->endsWith(".md")) {
      m_complete_list[index] = entry.path();
      index++;
    } else if (IS_DIRECTORY(entry)) {
      m_complete_list[index] = entry.path().string() + "/";
      index++;
    }

    delete search_result;
  }
  size = index;

  free(path);
}

void FileInput::update_suggestion() {
  if (text() == "" || isModified() || current_index >= AUTO_COMPLETE_MAX) {
    fetch_suggestions();
    current_index = 0;
  }

  string suggestion = m_complete_list[current_index];
  if (suggestion == "") {
    return;
  }

  setText(suggestion.c_str());
}

void FileInput::next_suggestion() {
  if (current_index < 0) {
    current_index = 0;
  } else {
    current_index = (current_index + 1) % size;
  }
  update_suggestion();
}

void FileInput::prev_suggestion() {
  if (current_index <= 0) {
    current_index = size - 1;
  } else {
    current_index = (current_index - 1) % size;
  }
  update_suggestion();
}
