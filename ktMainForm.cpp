#include <iostream>

#include "ktMainForm.h"

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
ktMainForm::~ktMainForm(){};

void ktMainForm::menuShow(){
  std::cout << "resizable= " << tl.resizable()->label() << " childrens= " << tl.children() << std::endl;
  tl.init_sizes();
  if (pnBar.get_btnMenuState()) {
    tl.position(dx,0,(int)(tl.w()*0.3),0);
  //~ std::cout << "resizable = " << tl.resizable()->label() << std::endl;
  } else {
  std::cout << "pnMenu = " << pnMenu.x() << "*" << pnMenu.w() << std::endl;
  std::cout << "pnWrk = " << pnWrk.x() << "*" << pnWrk.w() << std::endl;
    tl.position(pnMenu.w(),0,dx,0);
  std::cout << "pnMenu = " << pnMenu.x() << "*" << pnMenu.w() << std::endl;
  std::cout << "pnWrk = " << pnWrk.x() << "*" << pnWrk.w() << std::endl;
  }
};
