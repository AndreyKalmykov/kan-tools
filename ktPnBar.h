#ifndef KT_PANEL_BAR
#define KT_PANEL_BAR

#include <FL/Fl_Group.H>
//~ #include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Light_Button.H>

class ktMainForm;

class ktPnBar: public Fl_Group {
  ktMainForm *mf;
  Fl_Light_Button *btnMenu;
public:
  ktPnBar(int sx,int sy,int sw,int sh,ktMainForm *o);
  ~ktPnBar();
  static void btnMenu_cb(Fl_Widget *butt,void *o);
  int get_btnMenuState();
  void set_btnMenuState(int s);

};

#endif


