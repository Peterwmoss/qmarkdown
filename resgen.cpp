#include "resgen.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

void read_directory(ofstream *outfile, int depth, string path) {
  for (const auto &entry : filesystem::directory_iterator(path)) {
    if (entry.is_directory() && depth < 2) {
      read_directory(outfile, depth + 1, entry.path());
    }
    if (entry.path().string().ends_with(".png"))
      *outfile << "<file>" << path << "</file>" << endl;
  }
}

void res_gen(string path) {
  ofstream outfile("images.qrc");

  cout << "Generating images.qrc based on all images in current directory"
       << endl;

  outfile << "<!DOCTYPE RCC><RCC version='1.0'>" << endl;
  outfile << "<qresource>" << endl;

  read_directory(&outfile, 0, path);

  outfile << "</qresource>" << endl;
  outfile << "</RCC>" << endl;

  outfile.close();

  cout << "Compiling to images.rcc" << endl;
  system("rcc -binary images.qrc -o images.rcc");

  cout << "Removing images.qrc" << endl;
  system("rm -f images.qrc");
}
