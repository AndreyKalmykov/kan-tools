#include "ktMainForm.h"

int main(int argc, char **argv) {
  std::string cDir= (std::string)dirname(argv[0])+"/";
  //~ std::string icFileName= (std::string)dirname(argv[0])+(std::string)"/kTools.png";

  Fl::scheme(NULL);
  Fl_File_Icon::load_system_icons();

  ktMainForm *mf= new ktMainForm(1024,576,cDir); //= new ktMainForm();
  //~ Fl_PNG_Image appIcon{icFileName.c_str()};
  //~ mf->icon(&appIcon);

  mf->show(argc, argv);

  return Fl::run();
}
