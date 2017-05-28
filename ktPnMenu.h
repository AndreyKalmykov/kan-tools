#ifndef KT_PANEL_MENU
#define KT_PANEL_MENU

#include <FL/Fl_Group.H>

class ktPnMenu: public Fl_Group {
public:
  ktPnMenu(int x,int y,int w, int h);
  ~ktPnMenu();
  int handle(int e);
};

#endif


