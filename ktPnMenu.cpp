#include <iostream>
#include <FL/names.h>

#include "ktPnMenu.h"

ktPnMenu::ktPnMenu(int x,int y,int w, int h): Fl_Group(x,y,w,h,"ktPnMenu") {
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  begin();
  end();
};

ktPnMenu::~ktPnMenu(){};

///*
int ktPnMenu::handle(int e){
    //~ if (e!=FL_MOVE) printf("ktPnMenu - %s (%d)\n", fl_eventnames[e], e);
    return Fl_Group::handle(e);
}
//*/
