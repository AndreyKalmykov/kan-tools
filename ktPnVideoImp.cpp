#include "ktPnVideoImp.h"
#include "ktMainForm.h"

using std::cout;
using namespace boost::filesystem;

impRow::impRow(int n,std::string s,std::string d,uintmax_t sz,time_t t,int dst_ok) {
  npp= n;
  srcName= s;
  dstName= d;
  f_size= sz;
  dt= t;
  ok= dst_ok;
}

impTable::impTable(int X,int Y,int W,int H,const char *l) : Fl_Table(X,Y,W,H,l) {
}

void impTable::draw_cell(TableContext context,int R,int C,int X,int Y,int W,int H) {
    static char s[40];
    //~ sprintf(s, "%d/%d", R, C);              // text for each cell
    switch (context) {
    case CONTEXT_STARTPAGE:             // Fl_Table telling us it's starting to draw page
      fl_font(FL_HELVETICA,16);
      return;
    case CONTEXT_ROW_HEADER:            // Fl_Table telling us to draw row/col headers
      fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX,X,Y,W,H,color());
      fl_color(FL_BLACK);
      //~ fl_draw(colNames[C].c_str(),X, Y, W, H, FL_ALIGN_CENTER);
      fl_pop_clip();
      break;
    case CONTEXT_COL_HEADER:
      fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX,X,Y,W,H,color());
      fl_color(FL_BLACK);
      fl_draw(colNames[C].c_str(),X, Y, W, H, FL_ALIGN_CENTER);
      fl_pop_clip();
      return;

    case CONTEXT_CELL:                  // Fl_Table telling us to draw cells
      fl_push_clip(X,Y,W,H);
      // BG COLOR
      fl_color(is_selected(R,C) ? selection_color() : FL_WHITE);
      fl_rectf(X,Y,W,H);

      // TEXT
      fl_color(FL_BLACK);
      switch(C){
      case C_NPP:
        fl_draw(std::to_string(impRows[R].npp).c_str(), X, Y, W, H, FL_ALIGN_CENTER);
        break;
      case C_SRC:
        fl_draw(path(impRows[R].srcName).filename().c_str(), X, Y, W, H, FL_ALIGN_CENTER);
        break;
      case C_DST:
        fl_draw(path(impRows[R].dstName).filename().c_str(), X, Y, W, H, FL_ALIGN_CENTER);
        break;
      case C_SIZE:
        sprintf(s,"%6.2f",impRows[R].f_size/1024.0/1024.0);
        fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
        break;
      case C_DATE:
        strftime(s,40,"%y%m%e %T",localtime(&impRows[R].dt));
        fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
        break;
      case C_OK:
        //~ strftime(s,40,"%y%m%e %T",localtime(&impRows[R].dt));
        fl_draw(std::to_string(impRows[R].ok).c_str(), X, Y, W, H, FL_ALIGN_CENTER);
        break;
      }

      // BORDER
      fl_color(FL_LIGHT2);
      fl_rect(X, Y, W, H);
      fl_pop_clip();
      return;

    default:
        return;
    }
    //NOTREACHED
}

txtFI::txtFI(int X,int Y,int W,int H,const char *L):Fl_File_Input(X,Y,W,H,L){}

ktPnVideoImp::ktPnVideoImp(int sx,int sy,int sw,int sh,ktMainForm *o):
    Fl_Scroll(sx,sy,sw,sh,"ktPnVideoImp") {
  mf= o;
  int dx= 10,dy= 30;
  int txt_w= 300,txt_h= 30;
  int bt_dir_w= 30,bt_ref_w= 30,bt_ref_h= 30;
  refreshImg= mf->refreshIcon->copy(bt_ref_w-5,bt_ref_h-5);

  //~ int f_size= 15;

  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  Fl_File_Icon *ic_dir= Fl_File_Icon::find(".",Fl_File_Icon::DIRECTORY);
  //~ Fl_File_Icon *ic_ref= Fl_File_Icon::find(".",Fl_File_Icon::LINK);

  srcDir= new txtFI(sx+dx,sy+dy,txt_w,txt_h,"SRC");
    srcDir->align(FL_ALIGN_TOP);
    //~ srcDir->textsize(f_size);
    srcDir->value("/home/kan/wrk/kan-tools/box1");
  choseSrcDir= new Fl_Button(srcDir->x()+srcDir->w()+dx,sy+dy,bt_dir_w,txt_h);
    choseSrcDir->labelcolor(FL_YELLOW);
    ic_dir->label(choseSrcDir);
    choseSrcDir->callback(choseSrcDir_cb,this);
  dstDir= new txtFI(sx+dx+txt_w+dx+bt_dir_w+3*dx,sy+dy,txt_w,txt_h,"DST");
    dstDir->align(FL_ALIGN_TOP);
    //~ dstDir->textsize(f_size);
    dstDir->value("/home/kan/wrk/kan-tools/box2");
  choseDstDir= new Fl_Button(dstDir->x()+txt_w+dx,sy+dy,bt_dir_w,txt_h);
    choseDstDir->labelcolor(FL_YELLOW);
    ic_dir->label(choseDstDir);
    //~ choseDstDir->callback(choseDstDir_cb,this);
  tblRefresh= new Fl_Button(sx+dx,srcDir->y()+txt_h+1*dy,bt_ref_w,txt_h);
    tblRefresh->labelcolor(FL_YELLOW);
    tblRefresh->image(refreshImg);
    tblRefresh->callback(tblRefresh_cb,this);
  impTbl= new impTable(sx+dx,tblRefresh->y()+tblRefresh->h(),sw-2*dx,sh-2*dy-txt_h-2*dy,"Выполняем импорт");
    impTbl->cols(C_END); impTbl->col_header(1); impTbl->col_resize(1); impTbl->col_header_height(txt_h);
    impTbl->row_header(1); impTbl->row_resize(0); impTbl->row_header_width(txt_h/2);
    impTbl->col_width(C_NPP,20);
    impTbl->col_width(C_SRC,100);
    impTbl->col_width(C_DST,200);
    impTbl->col_width(C_SIZE,80);
    impTbl->col_width(C_DATE,200);

  end();
}

void ktPnVideoImp::tblRefresh_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  frm->loadDir();
}

int ktPnVideoImp::checkDstFile(std::string f_name,std::uintmax_t f_size){
  int rc= 0;
  if(exists(f_name)) {
    rc= 1;
  }
  return rc;
}

void ktPnVideoImp::loadDir(){
  std::string srcPath= getSrcPath();
  if(srcPath.empty()) {
    printf("srcDir не заполнен\n");
    return;
  }
  srcPath.erase(srcPath.find_last_not_of(" ")+1);
  if(srcPath.back() != '/') {
    srcPath.append("/"); setSrcPath(srcPath.c_str());
  }
  std::string dstPath= getDstPath();
  if(dstPath.empty()) {
    printf("dstDir не заполнен\n");
    return;
  }
  dstPath.erase(dstPath.find_last_not_of(" ")+1);
  if(dstPath.back() != '/') {
    dstPath.append("/"); setDstPath(dstPath.c_str());
  }
  //~ printf("last= <%lu> str=<%s>\n",dstPath.find_last_not_of(" "),dstPath.c_str());

  std::vector<std::string> v;
  //~ return;
///*
  time_t dt;
  static char s[40];
  std::string dst_name= ""; //"yymmdd-hhmm-00000.MTS";

  if(exists(srcPath) && is_directory(srcPath)){
    printf("dir= %s\n",srcPath.c_str());
    for(auto&& x : directory_iterator(srcPath)){
      if(x.path().extension() != ".MTS") {continue;}
      if(!status_known) {continue;}
      if(!is_regular_file(status(x))) {continue;}
      if(is_symlink(status(x))) {continue;}
      if(is_symlink(symlink_status(x))) {continue;}
        //~ printf("f= %s file_type=%d\n",x.path().filename().c_str(),status(x).type());
      //~ v.push_back(x.path().filename().string());
      v.push_back(x.path().string());
    }
    std::sort(v.begin(), v.end()); // Сортировка
    printf("impTbl-> rows=%d cols=%d\n",impTbl->rows(),impTbl->cols());
    impTbl->impRows.clear(); impTbl->rows(0);
    for(auto&& x : v){
      dt= last_write_time(x);
      strftime(s,21,"%y%m%e-%H%M-",localtime(&dt));
      dst_name= dstPath+s+path(x).filename().string();
      impTbl->rows(impTbl->rows()+1);
      impTbl->impRows.push_back(impRow{
              impTbl->rows(),x,dst_name,
              file_size(x),dt,checkDstFile(dst_name,file_size(x))
              });
      printf("src=%s\ndst=%s\n",x.c_str(),dst_name.c_str());
    }
    printf("impTbl-> rows=%d cols=%d\n",impTbl->rows(),impTbl->cols());

  } else {
    printf("dir not exists ==> %s\n",srcPath.c_str());
  }
//*/
}

void ktPnVideoImp::setSrcPath(const char *p){
  srcDir->value(p);
}

void ktPnVideoImp::setDstPath(const char *p){
  dstDir->value(p);
}

const char* ktPnVideoImp::getSrcPath(){
  return srcDir->value();
}

const char* ktPnVideoImp::getDstPath(){
  return dstDir->value();
}

void ktPnVideoImp::choseSrcDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  const char *p= frm->getSrcPath();
  char *d= fl_dir_chooser("src dir",p,0);
  if(d){
    frm->setSrcPath(d);
  }
}

void ktPnVideoImp::choseDstDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  const char *p= frm->getDstPath();
  char *d= fl_dir_chooser("dst dir",p,0);
  if(d){
    frm->setDstPath(d);
  }
}
