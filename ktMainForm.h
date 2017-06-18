#ifndef ktMainForm_h
#define ktMainForm_h

#include <iostream>
#include <string>
#include <libgen.h>

#include <FL/Fl.H>
#include <FL/Fl_Preferences.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/names.h>

#include "ktPnBar.h"
#include "ktPnMenu.h"
#include "ktPnWrk.h"
#include "ktPnVideoImp.h"
#include "ktPnVideoProxy.h"

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
  ktPnVideoProxy *pnVideoProxy;

public:
  std::string appDir;
  std::string appTitle= "kan Tools";

  Fl_Preferences *appPref;
  Fl_PNG_Image *appIcon;
  Fl_PNG_Image *refreshIcon;

  ktMainForm(int sW,int sH,std::string app_dir);
  //~ ~ktMainForm();
  int handle(int e);

  static void mainForm_cb(Fl_Widget *o);
  void savePref();
  void menuShow();
  void checkMenuOpen();
  std::string dirChooser(std::string txt,std::string dir);
  void doPnVideoImp();
  void doPnVideoProxy();
  void doPnDefault();
};

#endif
