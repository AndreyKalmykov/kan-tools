#include <iostream>
#include <FL/names.h>

#include "ktPnMenu.h"
#include "ktMainForm.h"

itButton::itButton(int X,int Y,int W,int H,const char *l,ktPnMenu *m,MenuItems it_def):
    Fl_Radio_Light_Button(X,Y,W,H,l){
  mn= m;
  value(0);
  it_name= it_def;
  //~ when(FL_WHEN_CHANGED);
  callback(mn->menu_cb);
  //~ set_changed();
}


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
    bt1= new itButton(0,0,0,bt_h,"bt1",this);
    bt2= new itButton(0,0,0,bt_h,"bt2",this);
    itVideo= new itButton(0,0,0,bt_h,"Видео",this);
      //~ itVideo->callback(itVideo_cb,this);
    grVideo= new Fl_Group(0,0,mn_w,bt_h*3+dy,"sm30");
    grVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      mnVideo= new Fl_Pack(0+dx,0,grVideo->w()-dx,grVideo->h(),"mnVideo");
      mnVideo->type(Fl_Pack::VERTICAL);
      mnVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      mnVideo->box(FL_DOWN_FRAME);
      mnVideo->spacing(0);
        itImpVideo= new itButton(0,0,0,bt_h,"Импорт видео",this,IT_VIDEOIMP);
        bt32= new itButton(0,0,0,bt_h,"bt32",this);
        bt33= new itButton(0,0,0,bt_h,"bt33",this);
      mnVideo->end();
    grVideo->end();
    //~ grVideo->hide();
    bt4= new itButton(0,0,0,bt_h,"bt4",this);
    bt5= new itButton(0,0,0,bt_h,"bt5",this);
    bt5->do_callback();
  mn->end();
  end();

  //~ printf("when=%d\n",mn->when());

};

void ktPnMenu::resize(int X, int Y, int W, int H){
  if (W >= mn_w) {
    mn->resize(mn->x(),mn->y(),W-2*dx,mn->h());
  }
  return Fl_Scroll::resize(X,Y,W,H);
}

int ktPnMenu::handle(int e){
  //~ if (e!=FL_MOVE && e!=FL_NO_EVENT && e!=FL_ENTER && e!=FL_LEAVE)
    //~ printf("ktPnMenu - %s (%d)\n", fl_eventnames[e], e);
    //~ printf("mn->value - (%d)\n", mn->value());

  //~ redraw();

  return Fl_Group::handle(e);
}

void ktPnMenu::draw(){
  //~ if(itVideo->value() == 0) {grVideo->hide();}
  //~ else {grVideo->show();}

  return Fl_Scroll::draw();
}

/*
void ktPnMenu::itVideo_cb(Fl_Widget *b,void *f){
  ktPnMenu *frm= (ktPnMenu *)f;
  if(frm->itVideo->value() == 0) {frm->grVideo->hide();}
  else {frm->grVideo->show();}

  frm->redraw();
  //~ frm->draw();

  //~ frm->mf->doPnVideoImp();
}
*/

void ktPnMenu::menu_cb(Fl_Widget *o){
  //~ Fl_Scroll *frm= (Fl_Scroll *)o;
  //~ printf("menu_cb grp=%s\n",grp->label());
  itButton *b= (itButton *)o;

  printf("menu_cb b=%s\n",b->label());
  MenuItems menu_it= IT_DEFAULT;
  if(b->mn->itVideo->value() != 0) {
    b->mn->grVideo->show();
    printf("itImpVideo->value()=%d\n",b->mn->itImpVideo->value());
    if(b->mn->itImpVideo->value() != 0) {menu_it= b->mn->itImpVideo->it_name;}
  } else { b->mn->grVideo->hide();}

  b->mn->redraw();
  printf("curr_it=%d menu_it=%d\n",b->mn->curr_item,menu_it);
  if(menu_it != b->mn->curr_item){
    b->mn->curr_item= menu_it;
    switch(menu_it){
    case IT_VIDEOIMP: {b->mn->mf->doPnVideoImp(); break;}
    default: {b->mn->mf->doPnDefault(); break;}
    }
  }
}

