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
  int dx = 5, dy = dx; // border width of resizable() - see below

  ktPnBar *pnBar;

  ktMainForm_Tile *tl;
  Fl_Box *r;

  int mn_w= 0, mn_h= 0;
  ktPnMenu *pnMenu;
  ktPnWrk *pnWrk;

public:
  ktMainForm(int sW,int sH);
  ~ktMainForm();
  void menuShow();
  void checkMenuOpen();
  int handle(int e);
};

#endif
