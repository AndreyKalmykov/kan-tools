#include <FL/Fl.H>
#include "ktMainForm.h"

int main(int argc, char **argv) {
  ktMainForm mf{800,450}; //= new ktMainForm();

  mf.show(argc, argv);

  return Fl::run();
}
