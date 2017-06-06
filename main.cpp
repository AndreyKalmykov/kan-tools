#include <iostream>
#include <string>
#include <libgen.h>

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>

#include "ktMainForm.h"

int main(int argc, char **argv) {
  std::string icFileName= (std::string)dirname(argv[0])+(std::string)"/kTools.png";

  Fl::scheme(NULL);
  Fl_File_Icon::load_system_icons();

  ktMainForm *mf= new ktMainForm(1024,576); //= new ktMainForm();
  Fl_PNG_Image appIcon{icFileName.c_str()};
  mf->icon(&appIcon);

  mf->show(argc, argv);

  return Fl::run();
}
