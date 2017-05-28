#include <iostream>

#include <FL/names.h>

#include "ktMainForm.h"

int ktMainForm_Tile::handle(int e){
  if (e == FL_RELEASE){
    //~ printf("ktMainForm_Tile - %s (%d)\n", fl_eventnames[e], e);
    //~ printf("par= %s\n",parent()->label());
    ((ktMainForm *)parent())->checkMenuOpen();
  }
  return Fl_Tile::handle(e);
};

ktMainForm::ktMainForm(int sW,int sH):Fl_Window(sW,sH,"main form"){
  label("kan Tools");
  hotspot(0,0,0);
  resizable(this);

  tl.resizable(r);
  tl.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  begin();
  end();

  menuShow();
  //~ std::cout << "...constructor ktMainForm" << std::endl;
};

ktMainForm::~ktMainForm(){}

void ktMainForm::checkMenuOpen(){
  if (pnMenu.w() <= dx) {
    pnBar.set_btnMenuState(0);
  }else {
    pnBar.set_btnMenuState(1);
  }
}

void ktMainForm::menuShow(){
  //~ std::cout << "resizable= " << tl.resizable()->label() << " childrens= " << tl.children() << std::endl;
  //~ printf("menuShow()\n");
  tl.init_sizes();
  if (pnBar.get_btnMenuState()) {
    tl.position(dx,0,(int)(tl.w()*0.3),0);
  } else {
    tl.position(pnMenu.w(),0,dx,0);
  }
}
///*
int ktMainForm::handle(int e){
    //~ if (e!=FL_MOVE) printf("ktMainForm - %s (%d)\n", fl_eventnames[e], e);
    return Fl_Window::handle(e);
}
//*/
