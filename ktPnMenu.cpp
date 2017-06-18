#include "ktPnMenu.h"
#include "ktMainForm.h"

itButton::itButton(int X,int Y,int W,int H,const char *l,ktPnMenu *m,MenuItems it_def):
    Fl_Radio_Light_Button(X,Y,W,H,l){
  mn= m;
  value(0);
  it_name= it_def;
  callback(mn->menu_cb);
}

ktPnMenu::ktPnMenu(int sx,int sy,int sw,int sh,ktMainForm *o):Fl_Scroll(sx,sy,sw,sh,"ktPnMenu") {
  mf= o;
  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

  mn= new Fl_Pack(x()+dx,y()+dy,mn_w,h()+dy,"mn");
    mn->type(Fl_Pack::VERTICAL);
    mn->box(FL_DOWN_FRAME);
    //~ mn->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    mn->labeltype(FL_NO_LABEL);
    mn->spacing(5);
    bt1= new itButton(0,0,0,bt_h,"bt1",this);
    bt2= new itButton(0,0,0,bt_h,"bt2",this);
    itVideo= new itButton(0,0,0,bt_h,"Видео",this);
    grVideo= new Fl_Group(0,0,mn_w,bt_h*3+dy,"sm30");
    //~ grVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      grVideo->labeltype(FL_NO_LABEL);
      mnVideo= new Fl_Pack(0+dx,0,grVideo->w()-dx,grVideo->h(),"mnVideo");
      mnVideo->type(Fl_Pack::VERTICAL);
      //~ mnVideo->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
      mnVideo->labeltype(FL_NO_LABEL);
      mnVideo->box(FL_DOWN_FRAME);
      mnVideo->spacing(0);
        itImpVideo= new itButton(0,0,0,bt_h,"Импорт видео",this,IT_VIDEOIMP);
        itProxyVideo= new itButton(0,0,0,bt_h,"Прокси видео",this,IT_VIDEOPROXY);
        bt33= new itButton(0,0,0,bt_h,"bt33",this);
      mnVideo->end();
    grVideo->end();
    grVideo->hide();
    bt4= new itButton(0,0,0,bt_h,"bt4",this);
    bt5= new itButton(0,0,0,bt_h,"bt5",this);

  mn->end();
  end();

    itVideo->value(1);
    itVideo->do_callback();

};

void ktPnMenu::resize(int X, int Y, int W, int H){
  if (W >= mn_w) {
    mn->resize(mn->x(),mn->y(),W-2*dx,mn->h());
  }
  return Fl_Scroll::resize(X,Y,W,H);
}

void ktPnMenu::menu_cb(Fl_Widget *o){
  itButton *b= (itButton *)o;
  MenuItems menu_it= IT_DEFAULT;
  if(b->mn->itVideo->value() != 0) {
    b->mn->grVideo->show();
    if(b->mn->itImpVideo->value() != 0) {menu_it= b->mn->itImpVideo->it_name;}
    if(b->mn->itProxyVideo->value() != 0) {menu_it= b->mn->itProxyVideo->it_name;}
  } else { b->mn->grVideo->hide();}
  b->mn->redraw();
  if(menu_it != b->mn->curr_item){
    b->mn->curr_item= menu_it;
    switch(menu_it){
    case IT_VIDEOIMP: {b->mn->mf->doPnVideoImp(); break;}
    case IT_VIDEOPROXY: {b->mn->mf->doPnVideoProxy(); break;}
    default: {b->mn->mf->doPnDefault(); break;}
    }
  }
}

