#include <iostream>
#include <FL/names.h>

#include "ktPnMenu.h"
#include "ktMainForm.h"

ktPnMenu::ktPnMenu(int sx,int sy,int sw,int sh,ktMainForm *o):Fl_Scroll(sx,sy,sw,sh,"ktPnMenu") {
  mf= o;
  //~ printf("pnMenu-Constr mf=%s\n",mf->label());
  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  mn= new Fl_Pack(x()+dx,y()+dy,mn_w,h()+dy,"mn");
  mn->type(Fl_Pack::VERTICAL);
  mn->box(FL_DOWN_FRAME);
  mn->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  mn->spacing(5);
    bt1= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt1");
    bt2= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt2");
    itVideo= new Fl_Radio_Light_Button(0,0,0,bt_h,"Видео");
      itVideo->callback(itVideo_cb,this);
    grVideo= new Fl_Group(0,0,mn_w,bt_h*3+dy,"sm30");
    grVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      mnVideo= new Fl_Pack(0+dx,0,grVideo->w()-dx,grVideo->h(),"mnVideo");
      mnVideo->type(Fl_Pack::VERTICAL);
      mnVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      mnVideo->box(FL_DOWN_FRAME);
      mnVideo->spacing(0);
        itImpVideo= new Fl_Radio_Light_Button(0,0,0,bt_h,"Импорт видео");
        bt32= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt32");
        bt33= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt33");
      mnVideo->end();
    grVideo->end();
    bt4= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt4");
    bt5= new Fl_Radio_Light_Button(0,0,0,bt_h,"bt5");
  mn->end();
  end();
};

ktPnMenu::~ktPnMenu(){};

void ktPnMenu::draw(){
  if(itVideo->value() == 0) {grVideo->hide();}
  else {grVideo->show();}

  return Fl_Scroll::draw();
}

void ktPnMenu::resize(int X, int Y, int W, int H){
  if (W >= mn_w) {
    mn->resize(mn->x(),mn->y(),W-2*dx,mn->h());
  }
  return Fl_Scroll::resize(X,Y,W,H);
}

void ktPnMenu::itVideo_cb(Fl_Widget *b,void *f){
  ktPnMenu *frm= (ktPnMenu *)f;
  frm->redraw();
}

int ktPnMenu::handle(int e){
    redraw();
    return Fl_Group::handle(e);
}
