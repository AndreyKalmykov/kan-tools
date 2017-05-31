#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "ktMainForm.h"
#include "ktPnBar.h"

ktPnBar::ktPnBar(int x,int y,int w, int h): Fl_Group(x,y,w,h,"ktPnBar") {
  resizable(NULL);
  box(FL_UP_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  btnMenu.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
  btnMenu.callback(btnMenu_cb);
  btnMenu.value(1);

  begin();
  end();
};
ktPnBar::~ktPnBar(){};

void ktPnBar::btnMenu_cb(Fl_Widget *butt){
  //~ Fl_Button *b= (Fl_Button *) butt;
  ((ktMainForm *)Fl::first_window())->menuShow();
};

int ktPnBar::get_btnMenuState(){
  return (int)btnMenu.value();
}

void ktPnBar::set_btnMenuState(int s){
  btnMenu.value(s);
}
