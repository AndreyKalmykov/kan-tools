#ifndef KT_PANEL_BAR
#define KT_PANEL_BAR

#include <FL/Fl_Group.H>
//~ #include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Light_Button.H>

class ktPnBar: public Fl_Group {
  Fl_Light_Button btnMenu{2,2,h()-4,h()-4,""};
public:
  ktPnBar(int x,int y,int w, int h);
  ~ktPnBar();
  static void btnMenu_cb(Fl_Widget *butt);
  int get_btnMenuState();
  void set_btnMenuState(int s);

};

#endif


