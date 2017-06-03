#ifndef ktMainForm_h
#define ktMainForm_h

#include <FL/Fl_Window.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>

#include "ktPnBar.h"
#include "ktPnMenu.h"
#include "ktPnWrk.h"
#include "ktPnVideoImp.h"

class ktMainForm_Tile: public Fl_Tile{

public:
  int handle(int e);
  ktMainForm_Tile(int X,int Y,int W,int H,const char *L=0):Fl_Tile(X,Y,W,H,L){};
};

class ktMainForm: public Fl_Window {
  int dx = 5, dy = dx; // border width of resizable() - see below

  ktPnBar *pnBar= NULL;

  ktMainForm_Tile *tl;
  Fl_Box *r= NULL;

  int mn_w= 0, mn_h= 0;
  ktPnMenu *pnMenu= NULL;
  ktPnWrk *pnWrk= NULL;

  ktPnVideoImp *pnVideoImp;

public:
  ktMainForm(int sW,int sH);
  ~ktMainForm();
  int handle(int e);

  void menuShow();
  void checkMenuOpen();
  void doPnVideoImp();
  void doPnDefault();
};

#endif
