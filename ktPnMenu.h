#ifndef KT_PANEL_MENU
#define KT_PANEL_MENU

#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Radio_Light_Button.H>


class ktMainForm;

class ktPnMenu: public Fl_Scroll {
public:
  ktMainForm &mf;
  int dx= 10, dy= 10;
  int mn_w=w()-2*dx, bt_h= 40;

  //~ Fl_Pack mn{x()+dx,y()+dy,mn_w,h()-2*dy,"mn"};
  Fl_Pack mn{x()+dx,y()+dy,mn_w,h()+dy,"mn"};
  Fl_Radio_Light_Button bt1{0,0,0,bt_h,"bt1"};
  Fl_Radio_Light_Button bt2{0,0,0,bt_h,"bt2"};
  Fl_Radio_Light_Button btVideo{0,0,0,bt_h,"Видео"};
  Fl_Radio_Light_Button bt4{0,0,0,bt_h,"bt4"};
  Fl_Radio_Light_Button bt5{0,0,0,bt_h,"bt5"};

  Fl_Group sm30{0,0,mn_w,bt_h*3+dy,"sm30"};
  //~ Fl_Pack mn30{x()+dx,y()+dy,mn_w-3*dx,h(),"mn30"};
  Fl_Pack mn30{0+dx,0,sm30.w()-dx,sm30.h(),"mn30"};
  Fl_Radio_Light_Button btImpVideo{0,0,0,bt_h,"Импорт видео"};
  Fl_Radio_Light_Button bt32{0,0,0,bt_h,"bt32"};
  Fl_Radio_Light_Button bt33{0,0,0,bt_h,"bt33"};

  ktPnMenu(int x,int y,int w, int h, ktMainForm &o);
  ~ktPnMenu();
  int handle(int e);
  void resize(int X, int Y, int W, int H);
  static void btVideo_cb(Fl_Widget *b, void *f);
  void draw();
};

#endif


