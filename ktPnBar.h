#ifndef KT_PANEL_BAR
#define KT_PANEL_BAR

#include <FL/Fl_Group.H>
#include <FL/Fl_Toggle_Button.H>

class ktPnBar: public Fl_Group {
  Fl_Toggle_Button btnMenu{2,2,h()-4,h()-4,"---"};
public:
  ktPnBar(int x,int y,int w, int h);
  ~ktPnBar();
  static void btnMenu_cb(Fl_Widget *butt);
  int get_btnMenuState();
};

#endif


