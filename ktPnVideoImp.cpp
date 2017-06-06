#include <iostream>
//~ #include <vector>
#include <boost/filesystem.hpp>

#include <FL/names.h>
#include "ktPnVideoImp.h"

using std::cout;
using namespace boost::filesystem;

txtFI::txtFI(int X,int Y,int W,int H,const char *L):Fl_File_Input(X,Y,W,H,L){}

int txtFI::handle(int event){
  int rc= Fl_File_Input::handle(event);

  switch(event){
    case FL_RELEASE:
    case FL_UNFOCUS:
      //~ printf("label=%s changed=%d\n",label(),changed());
      if(changed() && size()>0){
        Fl_Char last= index(size()-1);
        if(last!='/'){
          std::string corr= value();
          corr+='/';
          value(corr.c_str());
        }
        //~ printf("last char(%d)=%c\n",size(),last);
        std::string lbl= label();
        if(lbl=="SRC"){
          ((ktPnVideoImp *)parent())->setSrcPath(value());
        }
        if(lbl=="DST"){
          ((ktPnVideoImp *)parent())->setDstPath(value());
        }
      }
      break;
    default:
      //~ printf("txtFI - %s (%d)\n", fl_eventnames[event], event);
      break;

  }
  return rc;
}

ktPnVideoImp::ktPnVideoImp(int sx,int sy,int sw,int sh): Fl_Scroll(sx,sy,sw,sh,"ktPnVideoImp") {
  int txt_w= 300,txt_h= 30;
  //~ int f_size= 15;
  int bt_dir_w= 30;
  int dx= 10,dy= 30;

  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  Fl_File_Icon *icon= Fl_File_Icon::find(".",Fl_File_Icon::DIRECTORY);

  srcDir= new txtFI(sx+dx,sy+dy,txt_w,txt_h,"SRC");
    srcDir->align(FL_ALIGN_TOP);
    //~ srcDir->textsize(f_size);
    srcDir->value(srcPath);
  choseSrcDir= new Fl_Button(srcDir->x()+srcDir->w()+dx,sy+dy,bt_dir_w,txt_h);
    choseSrcDir->labelcolor(FL_YELLOW);
    icon->label(choseSrcDir);
    choseSrcDir->callback(choseSrcDir_cb,this);
  dstDir= new txtFI(sx+dx+txt_w+dx+bt_dir_w+3*dx,sy+dy,txt_w,txt_h,"DST");
    dstDir->align(FL_ALIGN_TOP);
    //~ dstDir->textsize(f_size);
    dstDir->value(dstPath);
  choseDstDir= new Fl_Button(dstDir->x()+txt_w+dx,sy+dy,bt_dir_w,txt_h);
    choseDstDir->labelcolor(FL_YELLOW);
    icon->label(choseDstDir);
    choseDstDir->callback(choseDstDir_cb,this);



  //~ fb= new Fl_File_Browser(sx+20,sy+20,300,300,"fb");
  //~ fb->load("../box1");
  //~ fb->set_visible_focus();

  end();
}

void ktPnVideoImp::loadDir(){
  if(exists(srcPath) && is_directory(srcPath)){
    printf("dir= %s\n",srcPath);
    std::vector<std::string> v;
    for(auto&& x : directory_iterator(srcPath)){
      v.push_back(x.path().filename().string());
    }
    std::sort(v.begin(), v.end());
    for(auto&& x : v){cout << "    " << x << '\n';}

  } else {
    printf("dir not exists ==> %s\n",srcPath);
  }

}

void ktPnVideoImp::setSrcPath(const char *p){
  srcPath= p;
  loadDir();
  //~ srcDir->value(srcPath);
}

void ktPnVideoImp::setDstPath(const char *p){
  dstPath= p;
  //~ loadDir();
  //~ srcDir->value(srcPath);
}

const char* ktPnVideoImp::getSrcPath(){
  return srcPath;
}

const char* ktPnVideoImp::getDstPath(){
  return dstPath;
}

void ktPnVideoImp::choseSrcDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  const char *p= frm->getSrcPath();
  char *d= fl_dir_chooser("src dir",p,0);
  if(d){
    //~ printf("d= %s\n",d);
    frm->srcDir->value(d);
    frm->srcDir->set_changed();
    frm->srcDir->handle(FL_UNFOCUS);
    //~ frm->setSrcPath(d);
  }
}

void ktPnVideoImp::choseDstDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  const char *p= frm->getDstPath();
  char *d= fl_dir_chooser("dst dir",p,0);
  if(d){
    //~ printf("d= %s\n",d);
    frm->dstDir->value(d);
    frm->dstDir->set_changed();
    frm->dstDir->handle(FL_UNFOCUS);
    //~ frm->setSrcPath(d);
  }
}
