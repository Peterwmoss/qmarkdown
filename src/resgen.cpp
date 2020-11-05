#include "resgen.h"
#include "helpers.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

bool read_directory(ofstream *outfile, int depth, string path) {
  int status = false;
  for (const auto &entry : filesystem::directory_iterator(path)) {
    if (entry.is_directory() && depth < 2)
      read_directory(outfile, depth + 1, entry.path());
    const string e_path = entry.path().string();
    const string image_types[] = {".png", ".jpg", ".jpeg", ".gif"};
    for (string type : image_types) {
      const size_t p_length = e_path.size();
      const size_t t_length = type.size();
      if (p_length >= t_length) {
        if (e_path.compare(p_length - t_length, t_length, type) == 0) {
          status = true;
          *outfile << "<file>" << e_path << "</file>" << endl;
        }
      }
    }
  }
  return status;
}

void res_gen(string path) {
  ofstream outfile("images.qrc");

  outfile << "<!DOCTYPE RCC><RCC version='1.0'>" << endl;
  outfile << "<qresource>" << endl;

  bool image_exists = read_directory(&outfile, 0, path);

  outfile << "</qresource>" << endl;
  outfile << "</RCC>" << endl;

  outfile.close();

  // Clean up
  if (image_exists)
    system(("rcc -binary images.qrc -o " + QRC_FILE).c_str());
  system("rm -f images.qrc");
}
