#include <iostream>
#include <string>
#include <libgen.h>

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>

#include "ktMainForm.h"

int main(int argc, char **argv) {
  std::string imName= (std::string)dirname(argv[0])+(std::string)"/kTools.png";
  //~ imName += "/kTools.png";

  //~ std::cout << imName << std::endl;

  ktMainForm mf{800,450}; //= new ktMainForm();
  Fl_PNG_Image appIcon{imName.c_str()};
  mf.icon(&appIcon);

  mf.show(argc, argv);

  return Fl::run();
}
