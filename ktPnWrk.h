#ifndef ktPnWrk_h
#define ktPnWrk_h

//~ #include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Clock.H>

class ktPnWrk: public Fl_Scroll {
  int cl_w= 100,cl_h= 100;
  int dx= 10,dy= dx;
  Fl_Clock *cl;
public:
  ktPnWrk(int x,int y,int w, int h);
  ~ktPnWrk();
};

#endif


