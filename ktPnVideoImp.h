#ifndef ktPnVideoImp_h
#define ktPnVideoImp_h

//~ #include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
//~ #include <FL/Fl_File_Browser.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_File_Chooser.H>

class txtFI: public Fl_File_Input {
public:
  txtFI(int X,	int Y,int W,int H,const char *L= 0);
  ~txtFI(){};
  int handle(int event);
};

class ktPnVideoImp: public Fl_Scroll {
  const char *srcPath= "/home/kan/wrk/kan-tools/box1/";
  Fl_Button *choseSrcDir;
  const char *dstPath= "/home/kan/wrk/kan-tools/box2/";
  Fl_Button *choseDstDir;
  //~ Fl_File_Browser *fb;
public:
  txtFI *srcDir;
  txtFI *dstDir;

  ktPnVideoImp(int sx,int sy,int sw,int sh);
  ~ktPnVideoImp(){};
  void loadDir();
  void setSrcPath(const char *p);
  const char* getSrcPath();
  static void choseSrcDir_cb(Fl_Widget *b,void *o);
  void setDstPath(const char *p);
  const char* getDstPath();
  static void choseDstDir_cb(Fl_Widget *b,void *o);
};

#endif


