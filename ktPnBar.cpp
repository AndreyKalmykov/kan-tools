#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "ktPnBar.h"
#include "ktMainForm.h"

ktPnBar::ktPnBar(int sx,int sy,int sw,int sh,ktMainForm *o): Fl_Group(sx,sy,sw,sh,"ktPnBar") {
  mf= o;
  resizable(NULL);
  box(FL_UP_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  btnMenu= new Fl_Light_Button(2,2,h()-4,h()-4,"");
    btnMenu->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
    btnMenu->callback(btnMenu_cb,this);
    btnMenu->value(1);

  end();
};
ktPnBar::~ktPnBar(){};

void ktPnBar::btnMenu_cb(Fl_Widget *butt,void *o){
  ktPnBar *frm= (ktPnBar *)o;
  frm->mf->menuShow();
};

int ktPnBar::get_btnMenuState(){
  return (int)btnMenu->value();
}

void ktPnBar::set_btnMenuState(int s){
  btnMenu->value(s);
}
