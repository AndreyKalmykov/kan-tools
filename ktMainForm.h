#ifndef ktMainForm_h
#define ktMainForm_h

#include <iostream>
#include <string>
#include <libgen.h>

#include <FL/Fl.H>
#include <FL/names.h>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Double_Window.H>
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

class ktMainForm: public Fl_Double_Window {
  int dx= 5,dy= dx;
  std::string f_mainIcon= "kTools.png";
  std::string f_refreshIcon= "kt-refresh.png";

  ktPnBar *pnBar= NULL;

  ktMainForm_Tile *tl;
  Fl_Box *r= NULL;

  int mn_w= 0, mn_h= 0;
  ktPnMenu *pnMenu= NULL;
  ktPnWrk *pnWrk= NULL;

  ktPnVideoImp *pnVideoImp;

public:
  std::string appDir;
  Fl_PNG_Image *appIcon;
  Fl_PNG_Image *refreshIcon;


  ktMainForm(int sW,int sH,std::string app_dir);
  ~ktMainForm();
  int handle(int e);

  void menuShow();
  void checkMenuOpen();
  void doPnVideoImp();
  void doPnDefault();
};

#endif
