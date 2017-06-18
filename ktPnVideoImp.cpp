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
    switch (context) {
    case CONTEXT_STARTPAGE:             // Fl_Table telling us it's starting to draw page
      fl_font(FL_HELVETICA,16);
      return;
    case CONTEXT_ROW_HEADER:            // Fl_Table telling us to draw row/col headers
      fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX,X,Y,W,H,color());
      fl_color(FL_BLACK);
      fl_pop_clip();
      break;
    case CONTEXT_COL_HEADER:
      fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX,X,Y,W,H,color());
      fl_color(FL_BLACK);
      fl_draw(colNames[C].c_str(),X,Y,W,H,FL_ALIGN_CENTER);
      fl_pop_clip();
      return;

    case CONTEXT_CELL:                  // Fl_Table telling us to draw cells
      fl_push_clip(X,Y,W,H);
      // BG COLOR
      fl_color(is_selected(R,C) ? selection_color() : (impRows[R].ok ? FL_WHITE:FL_YELLOW));
      fl_rectf(X,Y,W,H);

      // TEXT
      fl_color(FL_BLACK);
      switch(C){
      case C_IMP_NPP:
        fl_draw(std::to_string(impRows[R].npp).c_str(),X,Y,W,H,FL_ALIGN_CENTER);
        break;
      case C_IMP_SRC:
        fl_draw(path(impRows[R].srcName).filename().c_str(),X,Y,W,H,FL_ALIGN_CENTER);
        break;
      case C_IMP_DST:
        fl_draw(path(impRows[R].dstName).filename().c_str(),X,Y,W,H,FL_ALIGN_CENTER);
        break;
      case C_IMP_SIZE:
        sprintf(s,"%6.2f",impRows[R].f_size/1024.0/1024.0);
        fl_draw(s,X,Y,W,H,FL_ALIGN_CENTER);
        break;
      case C_IMP_DATE:
        strftime(s,40,"%y%m%e %T",localtime(&impRows[R].dt));
        fl_draw(s,X,Y,W,H,FL_ALIGN_CENTER);
        break;
      case C_IMP_OK:
        //~ strftime(s,40,"%y%m%e %T",localtime(&impRows[R].dt));
        fl_draw(std::to_string(impRows[R].ok).c_str(),X,Y,W,H,FL_ALIGN_CENTER);
        break;
      }

      // BORDER
      fl_color(FL_LIGHT2);
      fl_rect(X,Y,W,H);
      fl_pop_clip();
      return;

    default:
      return;
    }
    //NOTREACHED
}

ktPnVideoImp::ktPnVideoImp(int sx,int sy,int sw,int sh,ktMainForm *o):
    Fl_Scroll(sx,sy,sw,sh,"ktPnVideoImp") {
  mf= o;
  viPref= new Fl_Preferences(mf->appPref,"VideoImport");

  int buf_size= 1000; char c_buf[buf_size];

  int dx= 10,dy= 30;
  int txt_w= 300,txt_h= 30;
  int bt_dir_w= 30,bt_ref_w= 30,bt_ref_h= 30;
  int bt_do_imp_w= 150,bt_do_imp_h= 30;
  refreshImg= mf->refreshIcon->copy(bt_ref_w-5,bt_ref_h-5);

  resizable(NULL);
  box(FL_DOWN_BOX);
  align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  Fl_File_Icon *ic_dir= Fl_File_Icon::find(".",Fl_File_Icon::DIRECTORY);

  srcDir= new Fl_File_Input(sx+dx,sy+dy,txt_w,txt_h,"SRC");
    srcDir->align(FL_ALIGN_TOP);
    viPref->get("srcPath",c_buf,"",buf_size);
    srcDir->value(c_buf);
  btnSelSrcDir= new Fl_Button(srcDir->x()+srcDir->w()+dx,sy+dy,bt_dir_w,txt_h);
    btnSelSrcDir->labelcolor(FL_YELLOW);
    ic_dir->label(btnSelSrcDir);
    btnSelSrcDir->callback(btnSelSrcDir_cb,this);
  dstDir= new Fl_File_Input(sx+dx+txt_w+dx+bt_dir_w+3*dx,sy+dy,txt_w,txt_h,"DST");
    dstDir->align(FL_ALIGN_TOP);
    viPref->get("dstPath",c_buf,"",buf_size);
    dstDir->value(c_buf);
  btnSelDstDir= new Fl_Button(dstDir->x()+txt_w+dx,sy+dy,bt_dir_w,txt_h);
    btnSelDstDir->labelcolor(FL_YELLOW);
    ic_dir->label(btnSelDstDir);
    btnSelDstDir->callback(btnSelDstDir_cb,this);
  btnTblRefresh= new Fl_Button(sx+dx,srcDir->y()+txt_h+1*dy,bt_ref_w,bt_ref_h);
    btnTblRefresh->labelcolor(FL_YELLOW);
    btnTblRefresh->image(refreshImg);
    btnTblRefresh->callback(btnTblRefresh_cb,this);
  btnDoImport= new Fl_Button(sx+sw-dx-bt_do_imp_w,srcDir->y()+txt_h+1*dy,bt_do_imp_w,bt_do_imp_h,"Выполнить импорт");
    btnDoImport->callback(btnDoImport_cb,this);
  impTbl= new impTable(sx+dx,btnTblRefresh->y()+btnTblRefresh->h(),sw-2*dx,sh-2*dy-txt_h-3*dy,"Список для импорта");
    impTbl->cols(C_IMP_END); impTbl->col_header(1); impTbl->col_resize(1); impTbl->col_header_height(txt_h);
    impTbl->row_header(1); impTbl->row_resize(0); impTbl->row_header_width(txt_h/2);
    impTbl->col_width(C_IMP_NPP,20);
    impTbl->col_width(C_IMP_SRC,100);
    impTbl->col_width(C_IMP_DST,200);
    impTbl->col_width(C_IMP_SIZE,80);
    impTbl->col_width(C_IMP_DATE,200);

  end();

}

void ktPnVideoImp::btnTblRefresh_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  frm->loadDir();
}

void ktPnVideoImp::btnDoImport_cb(Fl_Widget *b,void *o){
  b->deactivate();                        // prevent button from being pressed again
  Fl::check();                               // give fltk some cpu to gray out button
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  frm->doImport();
  b->activate();                          // reactivate button
  frm->redraw();                               // tell window to redraw now that progress removed
}

void ktPnVideoImp::savePref(){
  viPref->set("srcPath",getSrcPath().c_str());
  viPref->set("dstPath",getDstPath().c_str());
}
int ktPnVideoImp::getNumsImp(){
  int f_num= 0;
  for(size_t i= 0; i<impTbl->impRows.size();i++){
    if(impTbl->impRows[i].ok != 0) continue;
    f_num++;
  }
  return f_num;
}

void ktPnVideoImp::doImport(){
  static char s[40];
  const std::time_t ct= std::time(0);
  int r1,r2,c1,c2;
  int f_nums= getNumsImp(),cf_num= 0;
  int prg_h= 30;
    begin();                                // add progress bar to it..
    Fl_Progress *progress = new Fl_Progress(impTbl->x(),impTbl->y()+impTbl->h(),impTbl->w(),prg_h);
    progress->minimum(0);                      // set progress range to be 0.0 ~ 1.0
    progress->maximum(f_nums);
    progress->color(0x88888800);               // background color
    progress->selection_color(0x4444ff00);     // progress bar color
    progress->labelcolor(FL_WHITE);            // percent text color
    end();                                  // end adding to window

  for(int i= 0; i<(int)impTbl->impRows.size();i++){
    if(impTbl->impRows[i].ok != 0) continue;
    impTbl->visible_cells(r1,r2,c1,c2);
    if(i<r1+3 || i>r2-3){
      impTbl->top_row(i-2>=0?i-2:0);
    }
    std::string src_name= impTbl->impRows[i].srcName;
    std::string dst_name= impTbl->impRows[i].dstName;
    std::uintmax_t src_size= impTbl->impRows[i].f_size;
    std::time_t src_dt= impTbl->impRows[i].dt;
    strftime(s,21,"/%y%m%e-%H%M",localtime(&ct));
    std::string ln_dir= path(dst_name).remove_filename().string()+s;
    std::string ln_name= ln_dir+"/"+path(dst_name).filename().string();
    std::string f_link= "../"+path(dst_name).filename().string();
    //~ printf("%s<>%s\n",f_link.c_str(),ln_name.c_str());
    if(!exists(path(dst_name).remove_filename())){
      printf("Ошибка!!! рет такого: dir=<%s>\n",path(dst_name).remove_filename().c_str());
      break;
    }
    if(!exists(ln_dir)) create_directory(ln_dir);
    printf("%s -> %s\n",src_name.c_str(),dst_name.c_str());

        progress->value(++cf_num);              // update progress bar with 0.0 ~ 1.0 value
        progress->label((std::to_string(cf_num)+"/"+std::to_string(f_nums)).c_str());              // update progress bar's label
        Fl::check();                           // give fltk some cpu to update the screen

    copy_file(path(src_name),path(dst_name),copy_option::overwrite_if_exists);
    last_write_time(dst_name,src_dt);
    permissions(dst_name, remove_perms|owner_exe|group_exe|others_exe);
    impTbl->impRows[i].ok= checkDstFile(dst_name,src_size);
    create_symlink(f_link,ln_name);
    impTbl->redraw();
    Fl::check();
  }
    remove(progress);                       // remove progress bar from window
    delete(progress);                          // deallocate it
    redraw();                               // tell window to redraw now that progress removed

}

int ktPnVideoImp::checkDstFile(std::string f_name,std::uintmax_t f_size){
  int rc= 0;
  if(exists(f_name)) {
    if(file_size(f_name)==f_size)
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

  std::vector<std::string> v;
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
}

void ktPnVideoImp::setSrcPath(std::string str){
  srcDir->value(str.c_str());
}

void ktPnVideoImp::setDstPath(std::string str){
  dstDir->value(str.c_str());
}

std::string ktPnVideoImp::getSrcPath(){
  return std::string(srcDir->value());
}

std::string ktPnVideoImp::getDstPath(){
  return std::string(dstDir->value());
}

void ktPnVideoImp::btnSelSrcDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  std::string p= frm->getSrcPath();
  std::string d= frm->mf->dirChooser(std::string("src dir"),p);
  if(!d.empty()) frm->setSrcPath(d.c_str());
}

void ktPnVideoImp::btnSelDstDir_cb(Fl_Widget *b,void *o){
  ktPnVideoImp *frm= (ktPnVideoImp *)o;
  std::string p= frm->getDstPath();
  std::string d= frm->mf->dirChooser(std::string("dst dir"),p);
  if(!d.empty()) frm->setDstPath(d.c_str());
}
