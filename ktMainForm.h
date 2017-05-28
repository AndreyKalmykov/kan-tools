#ifndef KT_MAIN_FORM
#define KT_MAIN_FORM

#include <FL/Fl_Window.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>

#include "ktPnBar.h"
#include "ktPnMenu.h"
#include "ktPnWrk.h"

class ktMainForm_Tile: public Fl_Tile{

public:
  int handle(int e);
  ktMainForm_Tile(int X,int Y,int W,int H,const char *L=0):Fl_Tile(X,Y,W,H,L){};
};

class ktMainForm: public Fl_Window {
  ktPnBar pnBar{0,0,w(),30};
  int dx = 5, dy = dx; // border width of resizable() - see below

  ktMainForm_Tile tl{x(),y()+pnBar.h(),w(),h()-pnBar.h(),"tl"};
  Fl_Box r{tl.x()+dx,tl.y()+dy,tl.w()-2*dx,tl.h()-2*dy,"rBox"};

  ktPnMenu pnMenu{tl.x(),tl.y(),(int)(tl.w()*0.3),tl.h()};
  ktPnWrk pnWrk{tl.x()+pnMenu.w(),tl.y(),tl.w()-pnMenu.w(),tl.h()};

public:
  ktMainForm(int sW,int sH);
  ~ktMainForm();
  void menuShow();
  void checkMenuOpen();
  int handle(int e);
};

#endif
