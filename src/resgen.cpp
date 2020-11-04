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
    if (entry.path().string().ends_with(".png")) {
      status = true;
      *outfile << "<file>" << entry.path().string() << "</file>" << endl;
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
