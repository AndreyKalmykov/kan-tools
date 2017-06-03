#include <FL/Fl.H>
//~ #include <FL/Fl_Window.H>

#include "ktPnVideoImp.h"

ktPnVideoImp::ktPnVideoImp(int x,int y,int w,int h): Fl_Scroll(x,y,w,h,"ktPnVideoImp") {
  resizable(NULL);
  box(FL_DOWN_BOX);
    align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  end();
}

ktPnVideoImp::~ktPnVideoImp(){}
