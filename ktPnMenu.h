#ifndef ktPnMenu_h
#define ktPnMenu_h

#include <iostream>

#include <FL/names.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Radio_Light_Button.H>


class ktMainForm;
class ktPnMenu;
enum MenuItems {IT_EMPTY=0,IT_DEFAULT,IT_VIDEOIMP,IT_VIDEOPROXY};

class itButton: public Fl_Radio_Light_Button {
public:
  ktPnMenu *mn;
  MenuItems it_name= IT_DEFAULT;

  itButton(int X,int Y,int W,int H,const char *l,ktPnMenu *m,MenuItems it_def=IT_DEFAULT);
  //~ Fl_Radio_Light_Button(int X,int Y,int W,int H,const char *l=0);
  ~itButton(){};
};

class ktPnMenu: public Fl_Scroll {
  ktMainForm *mf;
  int dx= 10, dy= 10;
  int mn_w=w()-2*dx, bt_h= 30;

  MenuItems curr_item= IT_EMPTY;

  Fl_Pack *mn;
  itButton *bt1;
  itButton *bt2;
  itButton *bt4;
  itButton *bt5;

  itButton *itVideo;
  Fl_Group *grVideo;
  Fl_Pack *mnVideo;
  itButton *itImpVideo;
  itButton *itProxyVideo;
  itButton *bt33;

public:
  ktPnMenu(int sx,int sy,int sw, int sh, ktMainForm *o);
  void resize(int X, int Y, int W, int H);
  static void menu_cb(Fl_Widget *o);
};

#endif


