#ifndef KT_PANEL_WRK
#define KT_PANEL_WRK

//~ #include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>

class ktPnWrk: public Fl_Scroll {
public:
  ktPnWrk(int x,int y,int w, int h);
  ~ktPnWrk();
};

#endif


