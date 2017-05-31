#include "ktPnWrk.h"

ktPnWrk::ktPnWrk(int x,int y,int w, int h): Fl_Scroll(x,y,w,h,"ktPnWrk") {
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  begin();
  end();
};
ktPnWrk::~ktPnWrk(){};
