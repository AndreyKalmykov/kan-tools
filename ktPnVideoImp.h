#ifndef ktPnVideoImp_h
#define ktPnVideoImp_h

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <FL/Fl_Scroll.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Table.H>
#include <FL/names.h>
#include <FL/fl_draw.H>

class ktMainForm;

enum TableCols {C_NPP=0,C_SRC,C_DST,C_END};

class impRow {
public:
  int npp= 0;
  std::string srcName;
  std::string dstName;
  impRow(int n,std::string s,std::string d);
};

class impTable: public Fl_Table {
  std::vector<std::string> colNames={
    "№","src name","dst name"
  };
public:
  std::vector<impRow> impRows;
  impTable(int X, int Y, int W, int H, const char *l=0);
  ~impTable(){};
  void draw_cell(TableContext context,int R=0,int C=0,int X=0,int Y=0,int W=0,int H=0);

};

class txtFI: public Fl_File_Input {
public:
  txtFI(int X,	int Y,int W,int H,const char *L= 0);
  ~txtFI(){};
};

class ktPnVideoImp: public Fl_Scroll {
  Fl_Image *refreshImg;
  Fl_Button *choseSrcDir;
  Fl_Button *choseDstDir;
  Fl_Button *tblRefresh;
  impTable *impTbl;
public:
  ktMainForm *mf;
  txtFI *srcDir;
  txtFI *dstDir;

  ktPnVideoImp(int sx,int sy,int sw,int sh,ktMainForm *o);
  ~ktPnVideoImp(){};
  void loadDir();
  void setSrcPath(const char *p);
  const char* getSrcPath();
  static void choseSrcDir_cb(Fl_Widget *b,void *o);
  void setDstPath(const char *p);
  const char* getDstPath();
  static void choseDstDir_cb(Fl_Widget *b,void *o);
  static void tblRefresh_cb(Fl_Widget *b,void *o);
};

#endif


