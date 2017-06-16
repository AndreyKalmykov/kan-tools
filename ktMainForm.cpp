#include "ktMainForm.h"

int ktMainForm_Tile::handle(int e){
  if (e == FL_RELEASE){
    //~ printf("ktMainForm_Tile - %s (%d)\n", fl_eventnames[e], e);
    //~ printf("par= %s\n",parent()->label());
    ((ktMainForm *)parent())->checkMenuOpen();
  }
  return Fl_Tile::handle(e);
};

ktMainForm::ktMainForm(int sW,int sH,std::string app_dir):
    Fl_Double_Window(sW,sH,"main form"){
  int buf_size= 1000; char c_buf[buf_size];
  appDir= app_dir;
  appPref= new Fl_Preferences(appDir.c_str(),"kan.home","kTools");

  appIcon= new Fl_PNG_Image((appDir+f_mainIcon).c_str());
  icon(appIcon);
  refreshIcon= new Fl_PNG_Image((appDir+f_refreshIcon).c_str());
  //~ refreshIcon->w(35); refreshIcon->h(35);
  appPref->get("appTitle",c_buf,appTitle.c_str(),buf_size);
  //~ appTitle= std::string(c_buf);
  appTitle= c_buf;
  label(appTitle.c_str());
  hotspot(0,0,0);
  resizable(this);
  callback(mainForm_cb);

  pnBar= new ktPnBar(0,0,w(),30,this);
  tl= new ktMainForm_Tile(0,0+pnBar->h(),w(),h()-pnBar->h(),"tl");
  mn_w= (int)(tl->w()*0.25), mn_h= tl->h();
  tl->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    r= new Fl_Box(tl->x()+dx,tl->y()+dy,tl->w()-2*dx,tl->h()-2*dy,"rBox");
    tl->resizable(r);
    pnMenu= new ktPnMenu(tl->x(),tl->y(),mn_w,mn_h,this);
    pnWrk= new ktPnWrk(tl->x()+pnMenu->w(),tl->y(),tl->w()-pnMenu->w(),tl->h());
  tl->end();

  end();

  pnVideoImp= new ktPnVideoImp(tl->x()+pnMenu->w(),tl->y(),tl->w()-pnMenu->w(),tl->h()
                  ,this);

  menuShow();
  //~ printf("tl->children=%d\n",tl->children());
};

//~ ktMainForm::~ktMainForm(){}

int ktMainForm::handle(int e){
    //~ if (e!=FL_MOVE) printf("ktMainForm - %s (%d)\n", fl_eventnames[e], e);

  return Fl_Window::handle(e);
}

void ktMainForm::mainForm_cb(Fl_Widget *o){
  ktMainForm *mf= (ktMainForm *)o;
  mf->savePref();
  //~ printf("mf_cb label=%s\n",mf->label());
  switch(fl_choice("Are you sure you want to quit?","Yes","No",0)){
  case 0: exit(0); break;
  case 1: return; break;
  }
}

std::string ktMainForm::dirChooser(std::string txt,std::string dir){
  std::string rc= "";
  Fl_Native_File_Chooser fch;
  fch.title(txt.c_str());
  fch.directory(dir.c_str());
  fch.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
  // Show
  switch (fch.show()) {
    case -1: fprintf(stderr, "ERROR: %s\n", fch.errmsg()); break;	// ERROR
    case  1: break;		// CANCEL
    default: 								// PICKED DIR
      if (fch.filename()) {rc= fch.filename();}
      break;
  }
  return rc;
}

void ktMainForm::savePref(){
  appPref->set("appTitle",appTitle.c_str());
  if(pnVideoImp){pnVideoImp->savePref();}
  appPref->flush();
  printf("savePref\n");
}

void ktMainForm::doPnVideoImp(){
  if(!pnVideoImp) {return;}
  tl->remove(2);
  tl->add(pnVideoImp);
  redraw();
}

void ktMainForm::doPnDefault(){
  if(!pnWrk) {return;}
  tl->remove(2);
  tl->add(pnWrk);
  redraw();
}

void ktMainForm::checkMenuOpen(){
  if (pnMenu->w() <= dx) {
    pnBar->set_btnMenuState(0);
  }else {
    pnBar->set_btnMenuState(1);
  }
}

void ktMainForm::menuShow(){
  tl->init_sizes();
  if (pnBar->get_btnMenuState()) {
    tl->position(dx,0,mn_w,0);
  } else {
    tl->position(pnMenu->w(),0,dx,0);
  }
}

