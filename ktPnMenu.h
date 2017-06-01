#ifndef KT_PANEL_MENU
#define KT_PANEL_MENU

#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Radio_Light_Button.H>


class ktMainForm;

class ktPnMenu: public Fl_Scroll {
  ktMainForm *mf;
  int dx= 10, dy= 10;
  int mn_w=w()-2*dx, bt_h= 40;

  Fl_Pack *mn;
  Fl_Radio_Light_Button *bt1;
  Fl_Radio_Light_Button *bt2;
  Fl_Radio_Light_Button *bt4;
  Fl_Radio_Light_Button *bt5;

  Fl_Radio_Light_Button *itVideo;
  Fl_Group *grVideo;
  Fl_Pack *mnVideo;
  Fl_Radio_Light_Button *itImpVideo;
  Fl_Radio_Light_Button *bt32;
  Fl_Radio_Light_Button *bt33;

public:
  ktPnMenu(int sx,int sy,int sw, int sh, ktMainForm *o);
  ~ktPnMenu();
  int handle(int e);
  void resize(int X, int Y, int W, int H);
  static void itVideo_cb(Fl_Widget *b, void *f);
  void draw();
};

#endif


