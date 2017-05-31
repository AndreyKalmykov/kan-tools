#include <iostream>
#include <FL/names.h>

#include "ktPnMenu.h"
#include "ktMainForm.h"

ktPnMenu::ktPnMenu(int x,int y,int w, int h,ktMainForm &o):
    Fl_Scroll(x,y,w,h,"ktPnMenu"),mf{o} {
  printf("pnMenu-Constr mf=%s\n",mf.label());
  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  mn30.type(Fl_Pack::VERTICAL);
  mn30.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  mn30.box(FL_DOWN_FRAME);
  mn30.spacing(0);
  mn30.begin();
    //~ mn30.box(FL_DOWN_FRAME);
    mn30.add(btImpVideo);
    mn30.add(bt32);
    mn30.add(bt33);
    mn30.end();
  mn30.redraw();
  //~ mn30.init_sizes();

  sm30.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  //~ sm30.box(FL_DOWN_FRAME);
  //~ sm30.resizable(NULL);
  sm30.begin();
    sm30.add(mn30);
  sm30.end();
  //~ sm30.resize(sm30.x(),sm30.y(),sm30.w(),mn30.h());
  sm30.redraw();

  mn.type(Fl_Pack::VERTICAL);
  mn.align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  mn.spacing(5);
  mn.box(FL_DOWN_FRAME);
  mn.begin();
    mn.add(bt1);
    mn.add(bt2);
    mn.add(btVideo);
    mn.add(sm30);
    mn.add(bt4);
    mn.add(bt5);
    mn.end();
  mn.redraw();
  //~ bt3.value(0);
  //~ bt3.when(bt3.when()||FL_WHEN_CHANGED||FL_WHEN_NOT_CHANGED||FL_WHEN_RELEASE_ALWAYS);
  btVideo.callback(btVideo_cb,this);
  //~ if(bt3.value()==0) {sm30.hide();}

  //~ printf("\npnMenu.children=%d h()=%d\n",children(),this->h());
  //~ for(int i= children();i--;){printf("%d= %s\n",i,child(i)->label());}
  begin();
    add(mn);
  end();
  //~ printf("\nmn.children=%d h()=%d\n",mn.children(),mn.h());
  //~ for(int i= mn.children();i--;){printf("%d= %s\n",i,mn.child(i)->label());}
  //~ printf("\nmn30.children=%d h()=%d\n",mn30.children(),mn30.h());
  //~ for(int i= mn30.children();i--;){printf("%d= %s\n",i,mn30.child(i)->label());}
};

ktPnMenu::~ktPnMenu(){};

void ktPnMenu::draw(){
  if(btVideo.value() == 0) {sm30.hide();}
  else {sm30.show();}

  return Fl_Scroll::draw();
}

void ktPnMenu::resize(int X, int Y, int W, int H){
  if (W >= mn_w) {
    mn.resize(mn.x(),mn.y(),W-2*dx,mn.h());
  }
  return Fl_Scroll::resize(X,Y,W,H);
}

void ktPnMenu::btVideo_cb(Fl_Widget *b,void *f){
  ktPnMenu *frm= (ktPnMenu *)f;
  //~ frm->mn.resize(frm->mn.x(),frm->mn.y(),frm->mn.w(),frm->mn.h());

  //~ frm->damage(FL_DAMAGE_ALL);
  frm->redraw();

}

///*
int ktPnMenu::handle(int e){
    //~ if (e!=FL_MOVE) printf("ktPnMenu - %s (%d)\n", fl_eventnames[e], e);
    //~ damage(FL_DAMAGE_ALL);
    redraw();
    return Fl_Group::handle(e);
}
//*/
