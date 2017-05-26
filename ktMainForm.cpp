#include <iostream>

#include "ktMainForm.h"

ktMainForm::ktMainForm(int sW,int sH):Fl_Window(sW,sH,"main form"){
  hotspot(0,0,0);
  //~ resizable(this);
  resizable(tl);
  label("kan Tools");

  //~ icon("kan.png");

  tl.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  begin();
  end();

  menuShow();
  //~ std::cout << "...constructor ktMainForm" << std::endl;
};
ktMainForm::~ktMainForm(){};

void ktMainForm::menuShow(){
  if (pnBar.get_btnMenuState()) {
    tl.position(1,0,(int)(tl.w()*0.3),0);
  } else {
    tl.position(pnMenu.w(),0,1,0);
  }
};
