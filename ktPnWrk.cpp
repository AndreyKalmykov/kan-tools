#include <FL/Fl.H>

#include "ktPnWrk.h"

ktPnWrk::ktPnWrk(int sx,int sy,int sw,int sh): Fl_Group(sx,sy,sw,sh,"ktPnWrk") {
  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  cl= new Fl_Clock(FL_ROUND_CLOCK,x()+w()-cl_w-dx,y()+dy,cl_w,cl_h,"часы");

  end();
}

ktPnWrk::~ktPnWrk(){}
