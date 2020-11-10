#include "resgen.h"
#include "helpers.h"

#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#endif

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

void read_directory(ofstream *outfile, int depth, string path, bool *status) {
  for (const auto &entry : filesystem::directory_iterator(path)) {
    if (entry.is_directory() && depth < 4)
      read_directory(outfile, depth + 1, entry.path(), status);
    const string e_path = entry.path().string();
    const string image_types[] = {".png", ".jpg", ".jpeg", ".gif"};
    for (string type : image_types) {
      const size_t p_length = e_path.size();
      const size_t t_length = type.size();
      if (p_length >= t_length) {
        if (e_path.compare(p_length - t_length, t_length, type) == 0) {
          *status = true;
          *outfile << "<file>" << e_path << "</file>" << endl;
        }
      }
    }
  }
}

void res_gen() {
  ofstream outfile("images.qrc");

  outfile << "<!DOCTYPE RCC><RCC version='1.0'>" << endl;
  outfile << "<qresource>" << endl;

  bool image_exists = false;
  read_directory(&outfile, 0, ".", &image_exists);

  outfile << "</qresource>" << endl;
  outfile << "</RCC>" << endl;

  outfile.close();

  // Clean up
  if (image_exists)
    system(("rcc -binary images.qrc -o " + QRC_FILE).c_str());
  system("rm -f images.qrc");
}
